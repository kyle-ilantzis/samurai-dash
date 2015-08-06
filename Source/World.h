//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include "ParsingHelper.h"
#include "Billboard.h"
#include <vector>
#include "Discoball.h"

class Camera;
class SplineModel;
class Animation;
class AnimationKey;
class ParticleSystem;

// Add Class Of Models
class Model;
class PlayerModel;
class Obstacles;
class UFOModel;
class FighterJetModel;

enum WorldCameraType { WORLD_CAMERA_FIRST_PERSON, WORLD_CAMERA_STATIC_ABOVE, WORLD_CAMERA_STATIC_ORIGIN, WORLD_CAMERA_NIL };

class World
{
public:
	static const char* sceneFile;
	// If true then models with bounding volumes will draw the volumes
	static const bool DRAW_BOUNDING_VOLUME = true;
	// How long to wait after the player has died or reached the goal before restarting.
	static const int RESTART_DELAY_SECONDS = 3;

	World();
	~World();
	
    static World* GetInstance();

	void Reset();
	void Update(float dt);
	void Draw();

	void World::LoadScene();

	void LoadScene(const char * scene_path);

    Animation* FindAnimation(ci_string animName);
	AnimationKey* FindAnimationKey(ci_string keyName);

    const Camera* GetCurrentCamera() const;
    void AddBillboard(Billboard* b);
    void RemoveBillboard(Billboard* b);
    void AddParticleSystem(ParticleSystem* particleSystem);
    void RemoveParticleSystem(ParticleSystem* particleSystem);
    
	Camera* GetCamera() { return mCamera[mCurrentCamera]; };
	
	WorldCameraType GetWorldCameraType() { return (WorldCameraType)mCurrentCamera; }
	void SetWorldCameraType(WorldCameraType type) { if (type != WORLD_CAMERA_NIL) mCurrentCamera = (int)type; }

	SplineModel* GetSpline() { return mSplineModel; };

	PlayerModel* GetPlayer() { return mPlayerModel; };

	Obstacles* GetObstacles() { return mObstacles; };

private:

	void UpdateCollision(float dt);

    static World* instance;
    
	std::vector<Model*> mModel;
    std::vector<Animation*> mAnimation;
    std::vector<AnimationKey*> mAnimationKey;
	std::vector<Camera*> mCamera;
    std::vector<ParticleSystem*> mParticleSystemList;
	unsigned int mCurrentCamera;

    BillboardList* mpBillboardList;

	SplineModel* mSplineModel;
	PlayerModel* mPlayerModel;
	FighterJetModel* mFighterJetModel;
	UFOModel* mUFOModel;
	Obstacles* mObstacles;
};
