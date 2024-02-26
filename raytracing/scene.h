#pragma once

#include <string>
#include <vector>

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

namespace rt
{
class Scene
{
public:
	void parse_file(std::string filename);

private:
	std::vector<Mesh> meshes_;
};
}
