#include "scene.h"

#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "common/logging.h"

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

void Scene::process_node(const aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		process_mesh(mesh, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_node(node->mChildren[i], scene);
	}
}

void Scene::process_mesh(aiMesh *mesh, const aiScene *scene)
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
		vertex.tangent    = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
		vertex.bitangent  = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
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
		aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];
		// material                = material_library_.get_material(ai_material);
	}

	meshes_.push_back(std::make_shared<Mesh>(vertices, indices, material));
}
}        // namespace rt
