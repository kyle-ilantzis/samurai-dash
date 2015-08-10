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
#include "World.h"
#include <glm/gtx/quaternion.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>
using namespace glm;

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position) :  
	Camera(), 
	mPosition(position), 
	mLookAt(0.0f, 0.0f, -1.0f), 
	mHorizontalAngle(90.0f), 
	mVerticalAngle(0.0f), 
	mSpeed(5.0f), 
	mAngularSpeed(2.5f),
	deadAnimation(),
	winAnimation(),
	mTargetModel(nullptr)
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
	deadAnimation.AddKey(k1, dt);
	deadAnimation.AddKey(k2, dt+0.05);
	deadAnimation.AddKey(k3, dt+0.1);
	deadAnimation.AddKey(k4, dt+0.15);
	deadAnimation.AddKey(k5, dt+0.2);
	deadAnimation.AddKey(k6, dt+0.25);

	
	w1 = new AnimationKey();
	w2 = new AnimationKey();

	int r1, r2;
	r1 = 15;
	r2 = 60;

	w1->SetPosition(vec3(r1,0,0));
	w2->SetPosition(vec3(r2,0,0));

	winAnimation.AddKey(w1, 0);
	winAnimation.AddKey(w2, 1);
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Update(float dt)
{

	if (World::GetInstance()->GetPlayer() &&
		World::GetInstance()->GetPlayer()->IsDead()){
		deadAnimation.Update(dt);
	}
	if (World::GetInstance()->GetPlayer() &&
		World::GetInstance()->GetPlayer()->HasReachedGoal()){
		winAnimation.Update(dt);
	}

	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();

	// The Camera moves based on the User inputs
	// - You can access the mouse motion with EventManager::GetMouseMotionXY()
	// - For mapping A S D W, you can look in World.cpp for an example of accessing key states
	// - Don't forget to use dt to control the speed of the camera motion

	// Mouse motion to get the variation in angle
	mHorizontalAngle -= EventManager::GetMouseMotionX() * mAngularSpeed * dt;
	mVerticalAngle -= EventManager::GetMouseMotionY() * mAngularSpeed * dt;

	vec3 currentPos = mTargetModel ? mTargetModel->GetPosition() : vec3(0);

	vec3 splNorm;
	vec3 splTan;
	if (World::GetInstance()->GetSpline()) {
		
		SplineModel::Plane spline = World::GetInstance()->GetSpline()->PlaneAt(mTargetModel->GetCurrentSplineTime());
		vec3 splNorm = spline.normal;
		vec3 splTan = spline.tangent;
	}
	else {
		vec3 splNorm = vec3(-1,0,0);
		vec3 splTan = vec3(0,0,-1);
	}

	vec3 j = vec3(0, 1, 0);
	vec3 B = normalize(cross(splTan, splNorm));

	mVerticalAngle = acos(dot(j, splTan))+20;	

	mHorizontalAngle = std::max(250.0f, std::min(290.0f, mHorizontalAngle));
	
	float radianValueTheta = mVerticalAngle * M_PI / 180.0; 
	float radianValueBeta = mHorizontalAngle * M_PI / 180.0; 
	
	mCenter = mTargetModel ? mTargetModel->GetPosition() : vec3(0);

	int radius = 15;

	if (World::GetInstance()->GetPlayer() && 
		World::GetInstance()->GetPlayer()->HasReachedGoal()){

		mat4 matWin = winAnimation.GetAnimationWorldMatrix();
		vec3 vecWin = vec3(matWin[3][0], matWin[3][1], matWin[3][2]);
		
		float rWin = vecWin.x;
		radius = rWin;
	}
		
	float posX = radius * cos (radianValueTheta) * cos (radianValueBeta);
	float posY = radius * sin (radianValueTheta);
	float posZ = -radius * cos (radianValueTheta) * sin (radianValueBeta);

	mPosition = mCenter + vec3(posX,posY,posZ);

	if (World::GetInstance()->GetPlayer() && 
		World::GetInstance()->GetPlayer()->IsDead()){

		mat4 matDead = deadAnimation.GetAnimationWorldMatrix();
		vec3 vecDead = vec3(matDead[3][0], matDead[3][1], matDead[3][2]);
		mCenter += vecDead;
	}
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(	mPosition, mCenter, vec3(0.0f, 1.0f, 0.0f) );	
}

void ThirdPersonCamera::SetTargetModel(PlayerModel* m)
{
	mTargetModel = m;
}