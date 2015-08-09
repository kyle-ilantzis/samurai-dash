#include "UFOModel.h"
#include "AssetsDir.h"
#include "Animation.h"
#include "World.h"
#include "PlayerModel.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

const glm::vec3 UFOModel::UFO_SHAPE_COLORS[] = { vec3{ 1, 0.843137, 0 }, vec3{ 0.180392, 0.545098, 0.341176 } };

UFOModel::UFOModel() : ObjectModel(HOLY_UFO, HOLY_UFO_MATERIAL, UFO_SHAPE_COLORS)
{
}

void UFOModel::Update(float dt)
{
	SetPosition( World::GetInstance()->GetPlayer()->GetPosition() );
}

mat4 UFOModel::GetWorldMatrix() const
{
	mat4 WM = translate(mat4(1.0f), GetPosition()) * Model::GetWorldMatrix();
	return WM;
}