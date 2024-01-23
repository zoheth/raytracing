#include "scene.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

namespace rt
{
void Scene::parse_file(std::string filename)
{
	Assimp::Importer importer;
	const aiScene   *ai_scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);


}
}
