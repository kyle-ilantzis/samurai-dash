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
	mpBillboardListGoose = new BillboardList(10, billboardTextureGoose);
	mpBillboardListIceman = new BillboardList(10, billboardTextureIceman);
	mpBillboardListMaverick = new BillboardList(10, billboardTextureMaverick);
	mpBillboardListTGend = new BillboardList(10, billboardTextureTGend);
	mpBillboardListTG = new BillboardList(10, billboardTextureTG);

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
		b->size = glm::vec2(20.0, 10.0);
		b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);
		
		if (i == 0)
		{ 
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
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
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
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
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
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
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
		}
		else
		{
			b->position = p.position + (World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, distanceTime * count)*(SplineFactory::trackWidth*1.5f));
		}
		mpBillboardListIceman->AddBillboard(b);
	}

	count++;

	// Above End of Track
	Billboard* b = new Billboard();
	b->size = glm::vec2(40.0, 20.0);
	b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);

	b->position = p.position + vec3(0.0f,SplineFactory::trackWidth,0.0f);

	mpBillboardListTGend->AddBillboard(b);

}