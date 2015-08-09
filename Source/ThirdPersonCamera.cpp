//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//
#define _USE_MATH_DEFINES
#include <math.h>
#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "PlayerModel.h"
#include "World.h"

#include <GLFW/glfw3.h>
#include <algorithm>
using namespace glm;

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position) :  Camera(), mPosition(position), mLookAt(0.0f, 0.0f, -1.0f), mHorizontalAngle(90.0f), mVerticalAngle(0.0f), mSpeed(5.0f), mAngularSpeed(2.5f),
	prevPos(0)
{
	k1 = new AnimationKey();
	k2 = new AnimationKey();
	k3 = new AnimationKey();
	k4 = new AnimationKey();
	k5 = new AnimationKey();
	k6 = new AnimationKey();
	
	k1->SetPosition(vec3(-2.5,0,0));
	k2->SetPosition(vec3(0,2.5,0));
	k3->SetPosition(vec3(2.5,0,0));
	k4->SetPosition(vec3(-0.5,1.5,0));
	k5->SetPosition(vec3(0.5,1.5,0));
	k6->SetPosition(vec3(-2.5,0,0));

	float dt = 0;
	myAnimate.AddKey(k1, dt);
	myAnimate.AddKey(k2, dt+0.05);
	myAnimate.AddKey(k3, dt+0.1);
	myAnimate.AddKey(k4, dt+0.15);
	myAnimate.AddKey(k5, dt+0.2);
	myAnimate.AddKey(k6, dt+0.25);

}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Update(float dt)
{
	
	if(World::GetInstance()->GetPlayer()->IsDead()){
		myAnimate.Update(dt);
	}

	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();
	
	if(prevPos == vec3(0))
		prevPos = mTargetModel->GetPosition();

	// The Camera moves based on the User inputs
	// - You can access the mouse motion with EventManager::GetMouseMotionXY()
	// - For mapping A S D W, you can look in World.cpp for an example of accessing key states
	// - Don't forget to use dt to control the speed of the camera motion

	// Mouse motion to get the variation in angle
	mHorizontalAngle -= EventManager::GetMouseMotionX() * mAngularSpeed * dt;
	mVerticalAngle   -= EventManager::GetMouseMotionY() * mAngularSpeed * dt;

	/*
	if (mHorizontalAngle > 180)
	{
		mHorizontalAngle -= 180;
	}
	else if (mHorizontalAngle < -180)
	{
		mHorizontalAngle += 180;
	}*/
	
	mHorizontalAngle = std::max(180.0f, std::min(360.0f, mHorizontalAngle));

	vec3 currentPos = mTargetModel->GetPosition();

	if(dt==0 || mTargetModel->GetPosition().z == 0){
		mVerticalAngle = std::max(40.0f, std::min(75.0f, mVerticalAngle));
	}
	if(currentPos.y < prevPos.y){
		mVerticalAngle = std::max(20.0f, std::min(75.0f, mVerticalAngle));
	}else{
		// Clamp vertical angle to [0, 75] degrees
		mVerticalAngle = std::max(0.0f, std::min(75.0f, mVerticalAngle));
	}
	prevPos = currentPos;
	
	int radius = 15;

	float radianValueTheta = mVerticalAngle * M_PI / 180.0;
	float radianValueBeta = mHorizontalAngle * M_PI / 180.0;

	float posX = radius * cos(radianValueTheta) * cos(radianValueBeta);
	float posY = radius * sin(radianValueTheta);
	float posZ = -radius * cos(radianValueTheta) * sin(radianValueBeta);

	mCenter = mTargetModel->GetPosition();

	mPosition = mCenter + vec3(posX, posY, posZ);

	if (World::GetInstance()->GetPlayer()->IsDead()){

		mat4 animateMat = myAnimate.GetAnimationWorldMatrix();
		vec3 animateVec = vec3(animateMat[3][0], animateMat[3][1], animateMat[3][2]);

		mCenter += animateVec;
	}
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt( mPosition, mCenter, vec3(0.0f, 1.0f, 0.0f) );
}

void ThirdPersonCamera::SetTargetModel(Model* m)
{
	mTargetModel = m;
}