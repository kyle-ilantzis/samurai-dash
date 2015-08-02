#include "WolfModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;


const glm::vec3 WolfModel::WOLF_SHAPE_COLORS[] = { vec3{ 1.0f, 0.0784314f, 0.576471f } };

WolfModel::WolfModel() : ObjectModel(HOLY_WOLF, HOLY_WOLF_MATERIAL, WOLF_SHAPE_COLORS)
{
}