#pragma once

#include <vector>
#include <string>
#include <memory>

#include "common/math.h"

namespace rt
{
class Material;

struct Vertex
{
	Vector3f position;
	Vector3f normal;
	Vector2f tex_coords;
	Vector3f tangent;
	Vector3f bitangent;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<size_t> indices;
	std::shared_ptr<Material> material;

	Mesh(const std::vector<Vertex> &vertices, const std::vector<size_t> &indices, std::shared_ptr<Material> material);
};

}
