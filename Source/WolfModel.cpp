#include "WolfModel.h"
#include "AssetsDir.h"

using namespace std;
using namespace glm;

vec3 v = vec3( 1.0f, 0.0784314f, 0.576471f );
const glm::vec3 WolfModel::WOLF_SHAPE_COLORS[] = { v };

WolfModel::WolfModel() : ObjectModel(HOLY_WOLF, HOLY_WOLF_MATERIAL, WOLF_SHAPE_COLORS)
{

}