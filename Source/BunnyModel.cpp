#include "BunnyModel.h"
#include "AssetsDir.h"
#include "Animation.h"

using namespace std;
using namespace glm;


const glm::vec3 BunnyModel::BUNNY_SHAPE_COLORS[] = { glm::vec3( 1, 0.870588, 0.678431 ), glm::vec3( 1, 0.54902, 0 ), glm::vec3( 1, 0.54902, 0 ), glm::vec3( 1, 0.54902, 0 ), glm::vec3( 1, 0.870588, 0.678431 ), glm::vec3( 0, 0, 0.803922 ), glm::vec3( 0.686275, 0.933333, 0.933333 ), glm::vec3( 0, 0, 0.803922 ), glm::vec3( 0.686275, 0.933333, 0.933333 ) };

BunnyModel::BunnyModel() : ObjectModel(HOLY_BUNNY, HOLY_BUNNY_MATERIAL, BUNNY_SHAPE_COLORS)
{
	SetScaling(glm::vec3(1.5f, 1.5f, 1.5f));
	SetPosition(glm::vec3(0.0f, 2.9f, 0.0f));
}