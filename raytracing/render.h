#pragma once

#include "ray.h"
#include "mesh.h"

namespace rt
{
inline bool RayIntersectsTriangle(const Ray &ray, const Vertex &v0, const Vertex &v1, const Vertex &v2, HitInfo &hit_info)
{
	constexpr float EPSILON = 0.0000001f;
	glm::vec3   edge1, edge2, h, s, q;
	float       a, f, u, v;
	edge1 = v1.position - v0.position;
	edge2 = v2.position - v0.position;
	h     = glm::cross(ray.direction, edge2);
	a     = glm::dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return false;        // This ray is parallel to this triangle.
	f = 1.0f / a;
	s = ray.origin - v0.position;
	u = f * glm::dot(s, h);
	if (u < 0.0 || u > 1.0)
		return false;
	q = glm::cross(s, edge1);
	v = f * glm::dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * glm::dot(edge2, q);
	if (t > EPSILON)
	{        // ray intersection
		hit_info.hit       = true;
		hit_info.distance  = t;
		hit_info.hit_point = ray.origin + ray.direction * t;
		//hit_info.normal    = glm::normalize(glm::cross(edge1, edge2));        // Assume non-deforming mesh
		glm::vec3 interpolated_normal = u * v0.normal + v * v1.normal + (1 - u - v) * v2.normal;
		hit_info.normal               = glm::normalize(interpolated_normal);
		return true;
	}
	else        // This means that there is a line intersection but not a ray intersection.
		return false;
}
}
