#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"

#include "Camera.h"

#include "Animation.h"
#include "Billboard.h"
#include "SplineFactory.h"

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

	if ((mPlayerModel->IsDead() || mPlayerModel->HasReachedGoal()) && mPlayerModel->GetStateCurrentTime() >= RESTART_DELAY_SECONDS) {
		Reset();
	}
}

void World::UpdateCollision(float dt) {

	static int ctr = 1;

	if (!mPlayerModel || mPlayerModel->IsDead() || mPlayerModel->HasReachedGoal()) { return; }

	if (mSplineModel) {
		Model* splineBvm = mSplineModel->GetBoundingVolumeModel();
		if (splineBvm && TestBoundingVolumes(*mPlayerModel, *mSplineModel)) {

			cout << "collision " << ctr++ << "! You Win!" << endl;
			mPlayerModel->ReachedGoal();
			return;
		}
	}

	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		if (mPlayerModel == *it) { continue; }
		
		Model* m = *it;

		bool r = TestBoundingVolumes(*mPlayerModel, *m);
		
		if (!r) { continue; }

		cout << "collision " << ctr++ << "! You Died!" << endl;
	}
}