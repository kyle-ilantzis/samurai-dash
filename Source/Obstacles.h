#pragma once

#include <vector>
#include <utility>

#include <GLM/glm.hpp>
#include "CubeModel.h"
#include "SphereModel.h"
#include "Discoball.h"
#include "CapsuleModel.h"
#include "RealTimeCollisionDetection.h"
#include "BarrelModel.h"

class PlayerModel;

enum ObstacleType { OBSTACLE_CUBE, OBSTACLE_BARREL, OBSTACLE_BUNNY, OBSTACLE_DISCO_BALL, /*OBSTACLE_FIRE*/ };
enum ObstacleDifficulty { OBSTACLE_EASY, OBSTACLE_MEDIUM, OBSTACLE_HARD};

class Obstacles
{
public:
	typedef std::vector<std::pair<ObstacleType, Model*>> obstacle_vector;
	typedef std::vector<std::pair<ObstacleType, Model*>>::iterator obstacle_vector_itr;

	static const int MAX_OBSTACLES = 15;
	float maxTime;
	ObstacleDifficulty obstacle_difficulty;
	Obstacles();

	void LoadObstacles();
	
	void Reset();

	ObstacleDifficulty GetDifficulty(float t);

	obstacle_vector& getObstacles() { return listObstacles; }

private:
	void ResetObstacle(ObstacleType type, Model* model);

	glm::vec3 RandomizeTrack(float t, ObstacleDifficulty difficulty);

	std::pair<ObstacleType,Model*> GetRandomModel();

	obstacle_vector listObstacles;
};
