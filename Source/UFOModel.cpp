#include "UFOModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;

vec3 a = vec3( 1, 0.843137, 0 );
vec3 b= vec3( 0.180392, 0.545098, 0.341176 );
const glm::vec3 UFOModel::UFO_SHAPE_COLORS[] = {a,b };

UFOModel::UFOModel() : ObjectModel(HOLY_UFO, HOLY_UFO_MATERIAL, UFO_SHAPE_COLORS)
{
}