#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

namespace rt
{

class Material
{
  public:
	std::string name;
	glm::vec3   diffuse;                // Kd
	glm::vec3   specular;               // Ks
	float       transparency;           // Tr, 1 means fully transparent, 0 means opaque
	float       shininess;              // Ns
	float       optical_density;        // Ni
	std::string diffuse_texture;        // map_Kd

	Material() :
	    diffuse(glm::vec3(0.5f)), specular(glm::vec3(0.0f)), transparency(0.0f), shininess(0.0f), optical_density(1.0f)
	{}
};

class MaterialLibrary
{
  private:
	std::unordered_map<std::string, std::shared_ptr<Material>> materials;

  public:
	std::shared_ptr<Material> get_material(const std::string &name)
	{
		auto it = materials.find(name);
		if (it != materials.end())
		{
			return it->second;
		}
		return nullptr;
	}
};
}
