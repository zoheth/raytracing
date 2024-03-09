#pragma once

#include <cmath>
#include <glm/glm.hpp>

#include "ray.h"

namespace rt
{
class Camera
{
  public:
	Camera(const glm::vec3 &position, const glm::vec3 &look_at, const glm::vec3 &up_vector,
	       float fov_y, float width, float height) :
	    position_(position),
	    fov_y_(fov_y),
	    aspect_ratio_(width / height),
	    near_plane_(0.1f),       
	    forward_(glm::normalize(look_at - position)),
	    right_(glm::normalize(glm::cross(forward_, up_vector))),
	    up_(glm::cross(right_, forward_)){}

	//Camera(const glm::vec3 &pos, const glm::vec3 &look_at, const glm::vec3 &up_vector,
	//       float fov_y, float aspect, float near_p) :
	//    position_(pos), fov_y_(fov_y), aspect_ratio_(aspect), near_plane_(near_p)
	//{
	//	forward_ = glm::normalize(look_at - pos);
	//	right_   = glm::normalize(glm::cross(forward_, up_vector));
	//	up_      = glm::cross(right_, forward_);
	//}

	glm::vec3 GetRayDirection(float pixel_x, float pixel_y, float image_width,
	                          float image_height) const
	{
		// Converts pixel coordinates to NDC (Normalized Device Coordinates)
		float ndc_x = (pixel_x + 0.5f) / image_width * 2.0f - 1.0f;
		float ndc_y = 1.0f - (pixel_y + 0.5f) / image_height * 2.0f;        // Flip Y-axis for image coordinates

		// Screen space coordinates calculation based on FOV and aspect ratio
		float tan_fov  = std::tan(glm::radians(fov_y_) / 2.0f);
		float screen_x = ndc_x * aspect_ratio_ * tan_fov;
		float screen_y = ndc_y * tan_fov;

		// Calculates ray direction in world space
		return glm::normalize(screen_x * right_ + screen_y * up_ + forward_);
	}

  private:
	glm::vec3 position_;
	glm::vec3 forward_;
	glm::vec3 up_;
	glm::vec3 right_;

	float fov_y_;
	float aspect_ratio_;
	float near_plane_;
};
}        // namespace rt