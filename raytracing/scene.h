#pragma once

#include <string>
#include <vector>
<<<<<<< HEAD

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

struct Mesh
{
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
};
=======
#include <assimp/scene.h>

#include "mesh.h"
#include "material.h"
>>>>>>> 83cf8f6c757898865dae92f0dc50a6e4d70a8e8b

namespace rt
{
class Scene
{
public:
<<<<<<< HEAD
	void parse_file(std::string filename);

private:
	std::vector<Mesh> meshes_;
=======
	void parse_file(const std::string &filename);

private:
	void process_node(const aiNode *node, const aiScene *scene);
	void process_mesh(aiMesh *mesh, const aiScene *scene);

private:
	std::vector<std::shared_ptr<Mesh>> meshes_;
	MaterialLibrary material_library_;
>>>>>>> 83cf8f6c757898865dae92f0dc50a6e4d70a8e8b
};
}
