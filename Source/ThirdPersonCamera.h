//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#ifndef THIRDPERSONCAMERA_H
#define THIRDPERSONCAMERA_H

#include "Camera.h"
#include "Animation.h"
#include "PlayerModel.h"

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(glm::vec3 position);
	virtual ~ThirdPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;
	virtual glm::vec3 GetPosition() const { return mPosition; };

	void SetTargetModel(PlayerModel* m);

private:
	PlayerModel* mTargetModel;
	glm::vec3 mPosition;	
	float mHorizontalAngle; // horizontal angle
	float mVerticalAngle;   // vertical angle
	float mSpeed;			// World units per second
	float mAngularSpeed;    // Degrees per pixel
	glm::vec3 mLookAt;
	glm::vec3 mCenter;

	Animation deadAnimation;
	Animation winAnimation;
	AnimationKey* k1;
	AnimationKey* k2;
	AnimationKey* k3;
	AnimationKey* k4;
	AnimationKey* k5;
	AnimationKey* k6;

	AnimationKey* w1;
	AnimationKey* w2;
	AnimationKey* w3;
	AnimationKey* w4;
	AnimationKey* w5;
};

#endif