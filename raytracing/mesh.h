#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "common/math.h"

namespace rt
{
class Material;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<size_t> indices;
	std::shared_ptr<Material> material;

	Mesh(const std::vector<Vertex> &vertices, const std::vector<size_t> &indices, const std::shared_ptr<Material> &material);
};

}
