#include "PlayerModel.h"
#include "AssetsDir.h"

using namespace std;
using namespace glm;


const glm::vec3 PlayerModel::SHEEP_SHAPE_COLORS[] = { vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 1.0f, 1.0f, 1.0f } };

PlayerModel::PlayerModel() : ObjectModel(HOLY_SHEEP, HOLY_SHEEP_MATERIAL, SHEEP_SHAPE_COLORS)
{
	
}