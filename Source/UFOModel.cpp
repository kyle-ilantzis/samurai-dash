#include "UFOModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;

const glm::vec3 UFOModel::UFO_SHAPE_COLORS[] = { vec3{ 1, 0.843137, 0 }, vec3{ 0.180392, 0.545098, 0.341176 } };

UFOModel::UFOModel() : ObjectModel(HOLY_UFO, HOLY_UFO_MATERIAL, UFO_SHAPE_COLORS)
{
}