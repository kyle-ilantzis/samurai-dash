#include "Obstacles.h"
#include "CapsuleModel.h"
#include "BunnyModel.h"
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
}

glm::vec3 Obstacles::RandomizeTrack(float t, ObstacleDifficulty difficulty)
{
	int rng = rand() % 3;

	switch (difficulty)
	{
	case OBSTACLE_EASY:
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
	case OBSTACLE_MEDIUM:
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
		};
	case OBSTACLE_HARD:
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
		};
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
		glm::vec3 newPosition = p.position + model->GetPosition() + RandomizeTrack(distanceTime*count, obstacle_difficulty);
		model->SetPosition(newPosition);
		//add function taht will set the scale to take 2 rooms, and also change the trackhard, trackmedium
	}
}

ObstacleDifficulty Obstacles::GetDifficulty(float t)
{
	maxTime = World::GetInstance()->GetSpline()->MaxTime();

	float LEVEL_1 = 1.0/maxTime;
	float LEVEL_2 = (1.0/maxTime) * 2;
	float LEVEL_3 = (1.0/maxTime) * 3;

	if (t >= LEVEL_1 && t < LEVEL_2)
	{
		return OBSTACLE_EASY;
	}
	else if (t >= LEVEL_2 && t < LEVEL_3)
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
		/*
		case OBSTACLE_FIRE:
		...
		break;
		*/
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
	// if (...) {
	//	FireModel* fireModel = new FireModel();
	//	...
	// }
}
