#include "BarrelModel.h"
#include "AssetsDir.h"


using namespace std;
using namespace glm;


const glm::vec3 BarrelModel::BARREL_SHAPE_COLORS[] = { vec3(1) };

BarrelModel::BarrelModel() : ObjectModel(HOLY_BARREL, HOLY_BARREL_MATERIAL, BARREL_SHAPE_COLORS, true)
{
	SetScaling(glm::vec3(0.6f, 0.6f, 0.6f));
}

void BarrelModel::Draw()
{
	ObjectModel::Draw();
}