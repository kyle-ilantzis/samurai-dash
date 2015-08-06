#pragma once

#include <vector>

#include <GLM/glm.hpp>
#include "CubeModel.h"
#include "SphereModel.h"
#include "WolfModel.h"
#include "Discoball.h"
#include "CapsuleModel.h"
#include "RealTimeCollisionDetection.h"

class PlayerModel;

class Obstacles
{
public:
	std::vector < Model* > listObstacles;
	Obstacles();
	glm::vec3 RandomizeTrack(float t);
	void PopulateRandomSample();
	void Draw();
	Model* GetRandomModel();
};
