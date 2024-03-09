#include "mesh.h"

namespace rt
{

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<size_t> &indices, const std::shared_ptr<Material> &material) :
vertices(vertices), indices(indices), material(material)
{}

}        // namespace rt
