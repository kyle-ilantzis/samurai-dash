#include "Obstacles.h"
#include "PlayerModel.h"
#include "SplineModel.h"
#include "FireModel.h"
#include "SplineFactory.h"
#include "World.h"
#include <GL/glew.h>
using namespace std;

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
	static bool fire = false;

	if (!fire){
		fire = true;

		FireModel* flame = new FireModel();
		flame->SetPosition(glm::vec3(0, 1.0f, 0));
		return flame;
	}

	int randomNumb = 1;
	if (randomNumb == 0){
		CubeModel* cModel = new CubeModel();
		cModel->SetPosition(glm::vec3(0, 1.0f, 0));
		cModel->SetScaling(glm::vec3(3.0f,3.0f,3.0f));
		return cModel;
	}
	else if (randomNumb == 5)
	{
		return new WolfModel();
	}
	else {
		
		SphereModel* sModel = new SphereModel();
		sModel->SetPosition(glm::vec3(0, 1.0f, 0));
		sModel->SetScaling(glm::vec3(2.0f, 2.0f, 2.0f));
		return sModel;
		
	}
}

void Obstacles::Draw()
{
	for (std::vector<Model*>::iterator it = listObstacles.begin(); it != listObstacles.end(); ++it) 
	{
		(*it)->Draw();
	}
}