// raytracing.cpp : Defines the entry point for the application.
//

#include "raytracing.h"

#include "tinyxml2.h"

#include "common/rstd.h"
#include "gpu/util.h"
#include "scene.h"

std::unique_ptr<rt::Camera> camera;

void parse_xml(const std::string &filename)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError    result = doc.LoadFile(filename.c_str());

	if (result != tinyxml2::XML_SUCCESS)
	{
		LOGE("Error loading XML file");
		return;
	}

	glm::vec3 position;
	glm::vec3 look_at;
	glm::vec3 up_vector;
	float     fov_y;
	int       width;
	int       height;

	tinyxml2::XMLElement *p_camera = doc.FirstChildElement("camera");
	if (p_camera != nullptr)
	{
		p_camera->QueryIntAttribute("width", &width);
		p_camera->QueryIntAttribute("height", &height);
		p_camera->QueryFloatAttribute("fovy", &fov_y);

		tinyxml2::XMLElement *pEye = p_camera->FirstChildElement("eye");
		if (pEye != nullptr)
		{
			pEye->QueryFloatAttribute("x", &position.x);
			pEye->QueryFloatAttribute("y", &position.y);
			pEye->QueryFloatAttribute("z", &position.z);
		}

		tinyxml2::XMLElement *pLookat = p_camera->FirstChildElement("lookat");
		if (pLookat != nullptr)
		{
			pLookat->QueryFloatAttribute("x", &look_at.x);
			pLookat->QueryFloatAttribute("y", &look_at.y);
			pLookat->QueryFloatAttribute("z", &look_at.z);
		}

		tinyxml2::XMLElement *pUp = p_camera->FirstChildElement("up");
		if (pUp != nullptr)
		{
			pUp->QueryFloatAttribute("x", &up_vector.x);
			pUp->QueryFloatAttribute("y", &up_vector.y);
			pUp->QueryFloatAttribute("z", &up_vector.z);
		}
	}
	camera = std::make_unique<rt::Camera>(position, look_at, up_vector, fov_y, width, height);
}

int main()
{
	rt::gpu_init();

	rt::Scene scene;
	scene.parse_file("example-scenes-cg23\\cornell-box\\cornell-box.obj");
	parse_xml("example-scenes-cg23\\cornell-box\\cornell-box.xml");

	

}
