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

}

glm::vec3 Obstacles::RandomizeTrack(float t)
{
	int rng = rand() % 3;
	if (rng == 0)
	{
		return World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_LEFT, t) * SplineFactory::trackWidth*(1.0f/3.0f);
	}
	else if (rng == 1)
	{
		return World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_RIGHT, t)* SplineFactory::trackWidth*float(1.0f/3.0f);
	}
	else
	{
		return World::GetInstance()->GetSpline()->TrackShiftDir(TRACK_MIDDLE, t)* SplineFactory::trackWidth*float(1.0f/3.0f);
	}
}

void Obstacles::PopulateRandomSample()
{
	int count = 0;
	float maxTime = World::GetInstance()->GetSpline()->MaxTime();
	float distanceTime = maxTime / 15.0f;

	for (int i = 0; i < 15; i++)
	{
		listObstacles.push_back(GetRandomModel());
	}

	for each (Model* m in listObstacles)
	{
		count++;
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);
		glm::vec3 poop = p.position + m->GetPosition() + RandomizeTrack(distanceTime*count);
		m->SetPosition(poop);
	}
}

Model* Obstacles::GetRandomModel()
{
	int randomNumb = rand() % 4;
	if (randomNumb == 0){
		CubeModel* cModel = new CubeModel();
		cModel->SetPosition(glm::vec3(0, 1.6f, 0));
		cModel->SetScaling(glm::vec3(3.0f,3.0f,3.0f));
		return cModel;
	}
	else if (randomNumb == 1)
	{
		Capsule* WolfCapsule = new Capsule();
		WolfCapsule->a = vec3(210, 0, 0);
		WolfCapsule->b = vec3(-130, 0, 0);
		WolfCapsule->r = 450;

		return new WolfModel();
	}
	else if (randomNumb == 2)
	{
		return new BunnyModel();
	}
	else
	{
		Discoball* cDiscoBall = new Discoball();
		cDiscoBall->SetPosition(glm::vec3(0, 2.2f, 0));
		cDiscoBall->SetScaling(glm::vec3(2.0f, 2.0f, 2.0f));
		return cDiscoBall;
	}

}

void Obstacles::Draw()
{
	for (std::vector<Model*>::iterator it = listObstacles.begin(); it != listObstacles.end(); ++it) 
	{
		(*it)->Draw();
	}
}