#pragma once

#include <vector>
#include <utility>

#include <GLM/glm.hpp>
#include "CubeModel.h"
#include "SphereModel.h"
#include "WolfModel.h"
#include "Discoball.h"
#include "CapsuleModel.h"
#include "RealTimeCollisionDetection.h"

class PlayerModel;

enum ObstacleType { OBSTACLE_CUBE, OBSTACLE_WOLF, OBSTACLE_BUNNY, OBSTACLE_DISCO_BALL, /*OBSTACLE_FIRE*/ };

class Obstacles
{
public:
	typedef std::vector<std::pair<ObstacleType, Model*>> obstacle_vector;
	typedef std::vector<std::pair<ObstacleType, Model*>>::iterator obstacle_vector_itr;

	static const int MAX_OBSTACLES = 15;

	Obstacles();

	void LoadObstacles();
	
	void Reset();

	obstacle_vector& getObstacles() { return listObstacles; }

private:

	glm::vec3 RandomizeTrack(float t);

	std::pair<ObstacleType,Model*> GetRandomModel();

	obstacle_vector listObstacles;
};
