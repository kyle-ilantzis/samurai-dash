#include "FighterJetModel.h"
#include "AssetsDir.h"
#include "Animation.h"
#include "World.h"
#include "PlayerModel.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

const glm::vec3 FighterJetModel::FIGHTER_JET_SHAPED_COLORS[] = {JET_COLORe, JET_COLORe2, JET_COLORe, JET_COLORe, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe, JET_COLORe, JET_COLORe,
JET_COLORe, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe, JET_COLORe, JET_COLORe, JET_COLORe2, JET_COLORe2, JET_COLORe, JET_COLORe,
JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2,
JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe2, JET_COLORe };

FighterJetModel::FighterJetModel() : ObjectModel(HOLY_JET, HOLY_JET_MATERIAL, FIGHTER_JET_SHAPED_COLORS)
{
}

void FighterJetModel::Update(float dt)
{
	SetPosition( World::GetInstance()->GetPlayer()->GetPosition() );
	//SetRotation( World::GetInstance()->GetPlayer()->GetRotationAxis(), World::GetInstance()->GetPlayer()->GetRotationAngle() );
}

mat4 FighterJetModel::GetWorldMatrix() const
{
	mat4 WM = translate(mat4(1.0f), (GetPosition() + vec3(0.0f,10.0f,15.0f)) ) * rotate(mat4(1.0f), -90.0f, vec3(0.0f, 1.0f, 0.0f)) * Model::GetWorldMatrix();
	return WM;
}