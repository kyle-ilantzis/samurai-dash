#include "Billboard.h"
#include "Renderer.h"
#include "World.h"
#include "Camera.h"
#include <GL/glew.h>
#include "TopGun.h"
#include "SplineModel.h"
#include "SplineFactory.h"

using namespace std;
using namespace glm;

TopGun::TopGun()
{
	// Add Different Textures
	int billboardTextureGoose= TextureLoader::LoadTexture("../Assets/Textures/Goose.jpg");
	int billboardTextureIceman = TextureLoader::LoadTexture("../Assets/Textures/Iceman.jpg");
	int billboardTextureMaverick = TextureLoader::LoadTexture("../Assets/Textures/Maverick.jpg");
	int billboardTextureTGend = TextureLoader::LoadTexture("../Assets/Textures/Top_Gun_Ending.jpg");
	int billboardTextureTG = TextureLoader::LoadTexture("../Assets/Textures/TopGun.jpg");


	assert(billboardTextureGoose != 0);
	assert(billboardTextureIceman != 0);
	assert(billboardTextureMaverick != 0);
	assert(billboardTextureTGend != 0);
	assert(billboardTextureTG != 0);

	// Create New BillboardLists for them
	mpBillboardListGoose = new BillboardList(10, billboardTextureGoose, true, true);
	mpBillboardListIceman = new BillboardList(10, billboardTextureIceman, true, true);
	mpBillboardListMaverick = new BillboardList(10, billboardTextureMaverick, true, true);
	mpBillboardListTGend = new BillboardList(10, billboardTextureTGend, true, true);
	mpBillboardListTG = new BillboardList(10, billboardTextureTG, true, true);

}

void TopGun::Update(float dt)
{
	mpBillboardListGoose->Update(dt);
	mpBillboardListIceman->Update(dt);
	mpBillboardListMaverick->Update(dt);
	mpBillboardListTGend->Update(dt);
	mpBillboardListTG->Update(dt);
}

void TopGun::Draw()
{
	mpBillboardListGoose->Draw();
	mpBillboardListIceman->Draw();
	mpBillboardListMaverick->Draw();
	mpBillboardListTGend->Draw();
	mpBillboardListTG->Draw();
}

void TopGun::Reset()
{
	mpBillboardListGoose->DeleteAll();
	mpBillboardListIceman->DeleteAll();
	mpBillboardListMaverick->DeleteAll();
	mpBillboardListTGend->DeleteAll();
	mpBillboardListTG->DeleteAll();

	int count = 1;
	float maxTime = World::GetInstance()->GetSpline()->MaxTime();
	float distanceTime = maxTime / MAX_TGBillboards;

	for(int i=0; i < 2; i++)
	{
		Billboard* b = new Billboard();
		b->size = glm::vec2(30.0, 10.0);
		b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);
		
		if (i == 0)
		{ 
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.35f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.35f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		mpBillboardListTG->AddBillboard(b);
	}

	count++;

	for (int i = 0; i < 2; i++)
	{
		Billboard* b = new Billboard();
		b->size = glm::vec2(20.0, 10.0);
		b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);

		if (i == 0)
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.1f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.1f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		mpBillboardListMaverick->AddBillboard(b);
	}

	count++;

	for (int i = 0; i < 2; i++)
	{
		Billboard* b = new Billboard();
		b->size = glm::vec2(20.0, 10.0);
		b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);

		if (i == 0)
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.1f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.1f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		mpBillboardListGoose->AddBillboard(b);
	}

	count++;

	for (int i = 0; i < 2; i++)
	{
		Billboard* b = new Billboard();
		b->size = glm::vec2(20.0, 10.0);
		b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);

		if (i == 0)
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.1f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.1f)) + vec3(0.0f, 6.0f, 0.0f);
		}
		mpBillboardListIceman->AddBillboard(b);
	}

	count++;

	// Above End of Track
	Billboard* b = new Billboard();
	b->size = glm::vec2(51.0, 36.0);
	b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);

	b->position = p.position + vec3(0.0f, 20.0f, -30.0f);

	mpBillboardListTGend->AddBillboard(b);

}