#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>

#include "camera.h"
#include "mesh.h"
#include "material.h"
#include "ray.h"

namespace rt
{

class Light
{
	
};

class Scene
{
public:
	void parse_file(const std::string &filename);

	void parse_xml(const std::string &filename);

	bool trace(const Ray &ray, HitInfo &hit_info);

private:
	void process_node(const aiNode *node, const aiScene *ai_scene);
	void process_mesh(aiMesh *mesh, const aiScene *ai_scene);
	std::shared_ptr<Material> process_materials(const aiMaterial *ai_material);

private:
	std::unique_ptr<Camera> camera_;

	std::vector<std::shared_ptr<Mesh>> meshes_;
	MaterialLibrary material_library_;

	std::vector<size_t> light_mesh_indices_;
};
}
