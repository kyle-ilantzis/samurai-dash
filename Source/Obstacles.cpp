#include "Obstacles.h"
#include "CapsuleModel.h"
#include "BunnyModel.h"
#include "FireModel.h"
#include "RealTimeCollisionDetection.h"
#include "PlayerModel.h"
#include "SplineModel.h"
#include "SplineFactory.h"
#include "World.h"
#include <GL/glew.h>

using namespace rtcd;
using namespace std;
using namespace glm;

Obstacles::Obstacles() : listObstacles()
{
	obstacle_difficulty = OBSTACLE_EASY;
	existing_fire = 0;
}

glm::vec3 Obstacles::RandomizeTrack(float t)
{
	int rng = rand() % 3;

		if (rng == 0)
		{
			return World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, t) * SplineFactory::trackWidth*(1.0f / 3.0f);
		}
		else if (rng == 1)
		{
			return World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, t)* SplineFactory::trackWidth*(1.0f / 3.0f);
		}
		else
		{
			return World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_MIDDLE, t)* SplineFactory::trackWidth*(1.0f / 3.0f);
		}
}

void Obstacles::LoadObstacles()
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
	{
		listObstacles.push_back(GetRandomModel());
	}
}

void Obstacles::Reset()
{
	int count = 0;
	float maxTime = World::GetInstance()->GetSpline()->MaxTime();
	float distanceTime = maxTime / MAX_OBSTACLES;

	for (obstacle_vector_itr it = listObstacles.begin(); it != listObstacles.end(); it++)
	{
		ObstacleType type = (*it).first;
		Model* model = (*it).second;
		
		ResetObstacle(type, model);

		count++;
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);
		obstacle_difficulty = GetDifficulty(distanceTime*count);
		
		glm::vec3 newPosition = p.position + model->GetPosition() + RandomizeTrack(distanceTime*count);
		model->SetPosition(newPosition);
		if (model->GetAnimation() != nullptr)
		{
			delete model->GetAnimation();
		}
		model->setAnimation(CreateAnimation(distanceTime*count, newPosition, obstacle_difficulty, type));
	}
}

Animation* Obstacles::CreateAnimation(float t, glm::vec3 pos, ObstacleDifficulty diff, ObstacleType type)
{
	AnimationKey* key1 = new AnimationKey();
	AnimationKey* key2 = new AnimationKey();
	AnimationKey* key3 = new AnimationKey();

	try
	{
		vec3 left = World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, t) * SplineFactory::trackWidth*(1.0f / 3.0f);
		vec3 right =World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, t) * SplineFactory::trackWidth*(1.0f / 3.0f);
		if (pos.x < 0)
		{
			
			key1->SetScaling(GetScalingType(type));
			key1->SetPosition(right + vec3(0.0f,pos.y,pos.z));
			key2->SetScaling(GetScalingType(type));
			key2->SetPosition(left + vec3(0.0f, pos.y, pos.z));
			key3->SetScaling(GetScalingType(type));
			key3->SetPosition(right + vec3(0.0f, pos.y, pos.z));
		}
		else
		{
			key1->SetScaling(GetScalingType(type));
			key1->SetPosition(left + vec3(0.0f, pos.y, pos.z));
			key2->SetScaling(GetScalingType(type));
			key2->SetPosition(right + vec3(0.0f, pos.y, pos.z));
			key3->SetScaling(GetScalingType(type));
			key3->SetPosition(left + vec3(0.0f, pos.y, pos.z));
		}
	}
	catch (exception e)
	{
		std::cout << "key error";
	}

	Animation* animate = new Animation();
	
	switch (diff)
	{
	case OBSTACLE_EASY:
		animate->AddKey(key1, 0.0);
		animate->AddKey(key2, 5.0);
		animate->AddKey(key3, 10.0);
		break;
	case OBSTACLE_MEDIUM:
		animate->AddKey(key1, 0.0);
		animate->AddKey(key2, 3.0);
		animate->AddKey(key3, 5.0);
		break;
	case OBSTACLE_HARD:
		animate->AddKey(key1, 0.0);
		animate->AddKey(key2, 1.0);
		animate->AddKey(key3, 3.0);
		break;
	}
	return animate;
}

void Obstacles::Update(float dt)
{
	for (obstacle_vector_itr it = listObstacles.begin(); it != listObstacles.end(); it++)
	{
		Model* model = (*it).second;
		if (model->GetAnimation() != nullptr)
			model->GetAnimation()->Update(dt);
	}
}

glm::vec3 Obstacles::GetScalingType(ObstacleType type)
{
	switch (type)
	{
	case OBSTACLE_CUBE:
		return glm::vec3(3.0f, 3.0f, 3.0f);
	case OBSTACLE_BARREL:
		return glm::vec3(0.6f, 0.6f, 0.6f);
	case OBSTACLE_BUNNY:
		return glm::vec3(1.5f, 1.5f, 1.5f);
	case OBSTACLE_DISCO_BALL:
		return glm::vec3(2.0f, 2.0f, 2.0f);
	case OBSTACLE_FIRE:
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}
}


ObstacleDifficulty Obstacles::GetDifficulty(float t)
{
	maxTime = World::GetInstance()->GetSpline()->MaxTime();

	float LEVEL_1 = maxTime/3.0;
	float LEVEL_2 = maxTime/3.0 * 2;
	float LEVEL_3 = maxTime/3.0 * 3;

	if (t >= 0 && t < LEVEL_1)
	{
		return OBSTACLE_EASY;
	}
	else if (t >= LEVEL_1 && t < LEVEL_2)
	{
		return OBSTACLE_MEDIUM;
	}
	else
		return OBSTACLE_HARD;
}

void Obstacles::ResetObstacle(ObstacleType type, Model* model) {

	CubeModel* cModel = nullptr;
	Discoball* cDiscoBall = nullptr;
	BarrelModel* wModel = nullptr;
	BunnyModel* bModel = nullptr;
	FireModel* fModel = nullptr;

	switch (type) 
	{
	case OBSTACLE_CUBE:
		cModel = (CubeModel*)model;
		cModel->SetPosition(glm::vec3(0, 1.6f, 0));
		cModel->SetScaling(glm::vec3(3.0f, 3.0f, 3.0f));
		break;
	case OBSTACLE_BARREL:
		wModel = (BarrelModel*)model;
		wModel->SetScaling(glm::vec3(0.6f, 0.6f, 0.6f));
		wModel->SetPosition(vec3(0));
		break;
	case OBSTACLE_BUNNY:
		bModel = (BunnyModel*)model;
		bModel->SetPosition(vec3(0,3,0));
		break;
	case OBSTACLE_DISCO_BALL:
		cDiscoBall = (Discoball*)model;
		cDiscoBall->SetPosition(glm::vec3(0, 2.2f, 0));
		cDiscoBall->SetScaling(glm::vec3(2.0f, 2.0f, 2.0f));
		break;	
	case OBSTACLE_FIRE:
		fModel = (FireModel*)model;
		fModel->SetPosition(glm::vec3(0, 0, 0));
		fModel->SetScaling(glm::vec3(1.0f, 1.0f, 1.0f));
		break;
	}
}

pair<ObstacleType, Model*> Obstacles::GetRandomModel()
{
	int randomNumb = rand() % 4;

	if (randomNumb == 0)
	{
		// Create Collision Capsule Cube
		Capsule* CubeCapsule = new Capsule();
		CubeCapsule->a = vec3(0, 0.25, 0);
		CubeCapsule->b = vec3(0, -0.25, 0);
		CubeCapsule->r = 0.68;

		Model* wCube = new CubeModel();
		wCube->setCapsuleBoundingVolume(CubeCapsule);

		return make_pair(OBSTACLE_CUBE, wCube);
	}
	else if (randomNumb == 1)
	{
		// Create Collision Capsule Barrel
		Capsule* BarrelCapsule = new Capsule();
		BarrelCapsule->a = vec3(0, 5, 0);
		BarrelCapsule->b = vec3(0, 0, 0);
		BarrelCapsule->r = 2.2;
		BarrelModel* wModel = new BarrelModel();
		wModel->setCapsuleBoundingVolume(BarrelCapsule);

		return make_pair(OBSTACLE_BARREL, wModel);
	}
	else if (randomNumb == 2)
	{
		// Create Collision Capsule Bunny
		Capsule* BunnyCapsule = new Capsule();
		BunnyCapsule->a = vec3(0, 0.95, 0);
		BunnyCapsule->b = vec3(0, - 1.3, 0);
		BunnyCapsule->r = 1;

		Model* wBunny = new BunnyModel();
		wBunny->setCapsuleBoundingVolume(BunnyCapsule);

		return make_pair(OBSTACLE_BUNNY, wBunny);
	}
	else if (randomNumb == 3 && existing_fire <= MAX_FIRE) {
		existing_fire++;
		//Create Collision Capsule FireModel
		Capsule* FireCapsule = new Capsule();
		FireCapsule->a = vec3(0, 0.25, 0);
		FireCapsule->b = vec3(0, -0.25, 0);
		FireCapsule->r = 1;
		Model* wFire = new FireModel();
		wFire->setCapsuleBoundingVolume(FireCapsule);

		return make_pair(OBSTACLE_FIRE, wFire);
		
	}
	else
	{
		// Create Collision Capsule Disco Ball
		Capsule* DiscoCapsule = new Capsule();
		DiscoCapsule->a = vec3(0, 0.25, 0);
		DiscoCapsule->b = vec3(0, -0.25, 0);
		DiscoCapsule->r = 1.1;

		Model* wDiscoBall = new Discoball();
		wDiscoBall->setCapsuleBoundingVolume(DiscoCapsule);

		return make_pair(OBSTACLE_DISCO_BALL, wDiscoBall);
	}
	
}
