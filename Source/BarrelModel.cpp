#include "BarrelModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;


const glm::vec3 BarrelModel::BARREL_SHAPE_COLORS[] = { vec3{0.372549f, 0.619608f, 0.627451f} };

BarrelModel::BarrelModel() : ObjectModel(HOLY_BARREL, HOLY_BARREL_MATERIAL, BARREL_SHAPE_COLORS)
{
	SetScaling(glm::vec3(0.6f, 0.6f, 0.6f));
}