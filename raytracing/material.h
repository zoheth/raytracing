#pragma once

#include <unordered_map>
#include <memory>
#include <string>

namespace rt
{

class Material
{
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
		else
		{
			auto material   = std::make_shared<Material>();
			materials[name] = material;
			return material;
		}
	}
};
}
