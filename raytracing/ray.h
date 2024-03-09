#pragma once

#include <glm/glm.hpp>

#include "material.h"

namespace rt
{
struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;
	float     time;
	float     t_min;
	float     t_max;

	Ray(const glm::vec3 &o, const glm::vec3 &d) :
	    origin(o), direction(glm::normalize(d))
	{}
};

struct HitInfo
{
	bool                      hit      = false;
	float                     distance = std::numeric_limits<float>::max();
	glm::vec3                 hit_point;
	glm::vec3                 normal;
	std::shared_ptr<Material> material;
};
}        // namespace rt