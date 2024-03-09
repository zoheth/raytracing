#include "scene.h"

#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "tinyxml2.h"

#include "common/logging.h"
#include "render.h"

namespace rt
{
void Scene::parse_file(const std::string &filename)
{
	Assimp::Importer importer;
	const aiScene   *ai_scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
	{
		LOGE("Assimp error: {}", importer.GetErrorString());
		return;
	}
	process_node(ai_scene->mRootNode, ai_scene);
}

void Scene::parse_xml(const std::string &filename)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError    result = doc.LoadFile(filename.c_str());

	if (result != tinyxml2::XML_SUCCESS)
	{
		LOGE("Error loading XML file");
		return;
	}

	glm::vec3 position;
	glm::vec3 look_at;
	glm::vec3 up_vector;
	float     fov_y;
	int     width;
	int     height;

	tinyxml2::XMLElement *p_camera = doc.FirstChildElement("camera");
	if (p_camera != nullptr)
	{
		p_camera->QueryIntAttribute("width", &width);
		p_camera->QueryIntAttribute("height", &height);
		p_camera->QueryFloatAttribute("fovy", &fov_y);

		tinyxml2::XMLElement *pEye = p_camera->FirstChildElement("eye");
		if (pEye != nullptr)
		{
			pEye->QueryFloatAttribute("x", &position.x);
			pEye->QueryFloatAttribute("y", &position.y);
			pEye->QueryFloatAttribute("z", &position.z);
		}

		tinyxml2::XMLElement *pLookat = p_camera->FirstChildElement("lookat");
		if (pLookat != nullptr)
		{
			pLookat->QueryFloatAttribute("x", &look_at.x);
			pLookat->QueryFloatAttribute("y", &look_at.y);
			pLookat->QueryFloatAttribute("z", &look_at.z);
		}

		tinyxml2::XMLElement *pUp = p_camera->FirstChildElement("up");
		if (pUp != nullptr)
		{
			pUp->QueryFloatAttribute("x", &up_vector.x);
			pUp->QueryFloatAttribute("y", &up_vector.y);
			pUp->QueryFloatAttribute("z", &up_vector.z);
		}
	}
	camera_ = std::make_unique<Camera>(position, look_at, up_vector, fov_y, width, height);
}

bool Scene::trace(const Ray &ray, HitInfo &hit_info)
{
	bool hit = false;
	for (const auto &mesh : meshes_)
	{
		for (size_t i = 0; i < mesh->indices.size(); i += 3)
		{
			Vertex &v0 = mesh->vertices[mesh->indices[i]];
			Vertex &v1 = mesh->vertices[mesh->indices[i + 1]];
			Vertex &v2 = mesh->vertices[mesh->indices[i + 2]];
			HitInfo temp_hit_info;
			if (RayIntersectsTriangle(ray, v0, v1, v2, temp_hit_info) && temp_hit_info.distance < hit_info.distance)
			{
				hit_info          = temp_hit_info;
				hit_info.material = mesh->material;
				hit               = true;
			}
		}
	}
	return hit;
}

void Scene::process_node(const aiNode *node, const aiScene *ai_scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = ai_scene->mMeshes[node->mMeshes[i]];
		process_mesh(mesh, ai_scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_node(node->mChildren[i], ai_scene);
	}
}

void Scene::process_mesh(aiMesh *mesh, const aiScene *ai_scene)
{
	std::vector<Vertex>       vertices;
	std::vector<size_t>       indices;
	std::shared_ptr<Material> material;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position   = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
		vertex.normal     = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
		vertex.tex_coords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
		vertices.push_back(vertex);
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *ai_material = ai_scene->mMaterials[mesh->mMaterialIndex];
		material                = process_materials(ai_material);
		if (material->name == "Light")
		{
			light_mesh_indices_.push_back(meshes_.size());
		}
	}

	meshes_.push_back(std::make_shared<Mesh>(vertices, indices, material));
}

std::shared_ptr<Material> Scene::process_materials(const aiMaterial *ai_mat)
{
	aiString name;
	ai_mat->Get(AI_MATKEY_NAME, name);

	if (auto material = material_library_.get_material(name.C_Str()))
	{
		return material;
	}

	auto mat  = std::make_shared<Material>();
	mat->name = name.C_Str();

	aiColor3D color(0.f, 0.f, 0.f);
	if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_COLOR_DIFFUSE, color))
	{
		mat->diffuse = glm::vec3(color.r, color.g, color.b);
	}
	if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_COLOR_SPECULAR, color))
	{
		mat->specular = glm::vec3(color.r, color.g, color.b);
	}
	float shininess;
	if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_SHININESS, shininess))
	{
		mat->shininess = shininess;
	}
	float transparency;
	if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_OPACITY, transparency))
	{
		mat->transparency = 1.0f - transparency;        // Assimp's opacity is the inverse of our transparency
	}
	float optical_density;
	if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_REFRACTI, optical_density))
	{
		mat->optical_density = optical_density;
	}
	aiString texture_path;
	if (AI_SUCCESS == ai_mat->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path))
	{
		mat->diffuse_texture = texture_path.C_Str();
	}

	return mat;
}
}        // namespace rt
