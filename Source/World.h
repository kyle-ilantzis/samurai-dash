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
#include "ThirdPersonCamera.h"
#include "ThirdPersonCameraFar.h"
#include "Discoball.h"
#include "SkyboxModel.h"
#include "StopWatch.h"

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
class TopGun;

enum WorldCameraType { WORLD_CAMERA_THIRD_PERSON, WORLD_CAMERA_THIRD_PERSON_FAR, WORLD_CAMERA_FIRST_PERSON, WORLD_CAMERA_NIL };

class World
{
public:
	static const char* sceneFile;
	// If true then models with bounding volumes will draw the volumes
	static const bool DRAW_BOUNDING_VOLUME = false;
	// If true the animations will draw their key frames points as a path
	static const bool DRAW_ANIM_PATH = false;
	// How long to wait after the player has died or reached the goal before restarting.
	static const float RESTART_DELAY_SECONDS;
	// If true collision with the goal will be tested for
	static const bool COLLISION_GOAL = true;
	// If true collision with obstacles will be tested for
	static const bool COLLISION_OBSTACLES = true;
	// If true the first person camera can be switched to during gameplay.
	static const bool CAN_USE_FIRST_PERSON_CAMERA = false;

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
	void SetLighting();
	void SetCoefficient(bool enabled = true, float a = 0.3);
	void SetFog(bool setCamera, int fog_eq);
    
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
	StopWatch* sw;
	int score;
	int lastScoreUpdate;
	int lastPointsUpdate;
	int points;

	SplineModel* mSplineModel;
	PlayerModel* mPlayerModel;
	FighterJetModel* mFighterJetModel;
	UFOModel* mUFOModel;
	Obstacles* mObstacles;
	SkyboxModel* mSkyboxModel;

	TopGun* mTopGun;

	Texture2D mBarrelTexture;
};
