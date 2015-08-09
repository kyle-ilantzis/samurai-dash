//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"
#include "Model.h"
#include "Animation.h"

class ThirdPersonCameraFar : public Camera
{
public:
	ThirdPersonCameraFar(glm::vec3 position);
	virtual ~ThirdPersonCameraFar();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;
	virtual glm::vec3 GetPosition() const { return mPosition; };

	void SetTargetModel(Model* m);

private:
	Model* mTargetModel;
	glm::vec3 mPosition;	
	float mHorizontalAngle; // horizontal angle
	float mVerticalAngle;   // vertical angle
	float mSpeed;			// World units per second
	float mAngularSpeed;    // Degrees per pixel
	glm::vec3 mLookAt;
	Animation myAnimate;
	AnimationKey* k1;
	AnimationKey* k2;
	AnimationKey* k3;
	AnimationKey* k4;
	AnimationKey* k5;
	AnimationKey* k6;

	glm::vec3 mCenter;
};
