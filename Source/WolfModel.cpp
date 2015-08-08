#include "WolfModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;


const glm::vec3 WolfModel::WOLF_SHAPE_COLORS[] = { vec3{ 1.0f, 1.0f, 1.0 } };

WolfModel::WolfModel() : ObjectModel(HOLY_WOLF, HOLY_WOLF_MATERIAL, WOLF_SHAPE_COLORS)
{
	SetScaling(glm::vec3(0.02f,0.02f,0.02f));
}