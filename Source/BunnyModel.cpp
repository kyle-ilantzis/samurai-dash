#include "BunnyModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;

const glm::vec3 BunnyModel::BUNNY_SHAPE_COLORS[] = { vec3{ 1, 0.870588, 0.678431 }, vec3{ 1, 0.54902, 0 }, vec3{ 1, 0.54902, 0 }, vec3{ 1, 0.54902, 0 }, vec3{ 1, 0.870588, 0.678431 }, vec3{ 0, 0, 0.803922 }, vec3{ 0.686275, 0.933333, 0.933333 }, vec3{ 0, 0, 0.803922 }, vec3{ 0.686275, 0.933333, 0.933333 } };

BunnyModel::BunnyModel() : ObjectModel(HOLY_BUNNY, HOLY_BUNNY_MATERIAL, BUNNY_SHAPE_COLORS)
{
	SetScaling(glm::vec3(10.0f, 10.0f, 10.0f));
}