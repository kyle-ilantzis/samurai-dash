#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"

#include "Camera.h"

#include "Animation.h"
#include "Billboard.h"

#include <GLFW/glfw3.h>
#include "EventManager.h"

#include "ParticleSystem.h"

#include "PlayerModel.h"

#include "RealTimeCollisionDetection.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace rtcd;

void World::Update(float dt)
{
	// User Inputs
	// 0 1 2 to change the Camera
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
	{
		mCurrentCamera = 0;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2) == GLFW_PRESS)
	{
		if (mCamera.size() > 1)
		{
			mCurrentCamera = 1;
		}
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3) == GLFW_PRESS)
	{
		if (mCamera.size() > 2)
		{
			mCurrentCamera = 2;
		}
	}

	// Spacebar to change the shader
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_SOLID_COLOR);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_BLUE);
	}

	// Update animation and keys
	for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
	{
		(*it)->Update(dt);
	}

	for (vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
	{
		(*it)->Update(dt);
	}


	// Update current Camera
	mCamera[mCurrentCamera]->Update(dt);

	// Update models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->Update(dt);
	}

	// Update billboards

	for (vector<ParticleSystem*>::iterator it = mParticleSystemList.begin(); it != mParticleSystemList.end(); ++it)
	{
		(*it)->Update(dt);
	}

	mpBillboardList->Update(dt);

	UpdateCollision(dt);
}

void World::UpdateCollision(float dt) {

	static int ctr = 1;

	if (!mPlayerModel) { return; }

	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		if (mPlayerModel == *it) { continue; }

		bool r = TestBoundingVolumes(*mPlayerModel, **it);
		
		if (r) {
			cout << "collision " << ctr++ << "!" << endl;
		}
	}
}