#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>

#include "mesh.h"
#include "material.h"

namespace rt
{
class Scene
{
public:
	void parse_file(const std::string &filename);

private:
	void process_node(const aiNode *node, const aiScene *scene);
	void process_mesh(aiMesh *mesh, const aiScene *scene);

private:
	std::vector<std::shared_ptr<Mesh>> meshes_;
	MaterialLibrary material_library_;
};
}
