#include "mesh.h"

namespace rt
{
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned> &indices, std::shared_ptr<Material> material):
	vertices(vertices), indices(indices), material(std::move(material))
{}
}
