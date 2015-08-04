#include "UFOModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;

const glm::vec3 UFOModel::UFO_SHAPE_COLORS[] = { vec3{ 1.0f, 0.0784314f, 0.576471f } };

UFOModel::UFOModel() : ObjectModel(HOLY_UFO, HOLY_UFO_MATERIAL, UFO_SHAPE_COLORS)
{
	SetScaling(glm::vec3(10.0f, 10.0f, 10.0f));
}