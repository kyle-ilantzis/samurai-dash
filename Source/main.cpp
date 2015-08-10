//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include <Windows.h>
#include <MMSystem.h>
#define SLEEP_FUNC(x) Sleep((x))

#include "Renderer.h"
#include "World.h"
#include "EventManager.h"
#include "Billboard.h"
#include "TextureLoader.h"
#include "LoadingScreen.h"

using namespace std;

#include <GLFW/glfw3.h>

#define FPS 30
#define PHYSICS_FPS 30
// #define DEBUG_FRAME_RATE

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

	// If Running on Windows Then Play Background Music
	// PlaySound(TEXT("../Assets/Sounds/Danger-Zone.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	/*loading screen block*/ {

		LoadingScreen loadingScreen;
		loadingScreen.Draw();

		//	world.LoadScene("../Assets/Scenes/AnimatedSceneWithParticles.scene");
		//	world.LoadScene("../Assets/Scenes/AnimatedScene.scene");
		//	world.LoadScene("../Assets/Scenes/Spline.scene");
		//	world.LoadScene("../Assets/Scenes/StaticScene.scene");
		//	world.LoadScene("../Assets/Scenes/CoordinateSystem.scene");
		//	world.LoadScene("../Assets/Scenes/CollisionDemo.scene");
		//	world.LoadScene("../Assets/Scenes/Animal.scene");
		//	world.LoadScene("../Assets/Scenes/StaticScene.scene");
		//	world.LoadScene("../Assets/Scenes/CoordinateSystem.scene");
		//	world.LoadScene("../Assets/Scenes/Discoball.scene");
		//	world.LoadScene("../Assets/Scenes/Player.scene");
		//	world.LoadScene("../Assets/Scenes/Barrel.scene");
			world.LoadScene();
	}

	double fps = 1.0f / FPS;
	double dtStep = 1.0f / PHYSICS_FPS;
	
	double dtAcc = 0;

#ifdef DEBUG_FRAME_RATE
	long seconds = 0;
	double currentTime = 0.0;
	long remainingMsAcc = 0;
	long sleepCtr = 0;
#endif

	// Reset the polled values in the EventManager because scene loading is long.
	EventManager::Update();

	do
	{
		double start = glfwGetTime();

		// Update Event Manager - Frame time / input / events processing 
		EventManager::Update();

		float dt = EventManager::GetFrameTime();

		// Apply fixed delta time steps to each world update,
		// and drawing can be done if at least 1 world update was done.
		dtAcc += dt;
		bool draw = false;
		while (dtAcc >= dtStep) {
			dtAcc -= dtStep;
			world.Update(dtStep);
			draw = true;
		}

		if (draw) {
			world.Draw();
		}

#ifndef DEBUG_FRAME_RATE
		// Each frame should be "fps" seconds long.
		// If updating and rendering took less than fps seconds long then sleep for the remainder.
		int remainingMs = (start + fps - glfwGetTime()) * 1000;
		if (remainingMs > 0) {
			SLEEP_FUNC(remainingMs);
		}
#else
		long remainingMs = (start + fps - glfwGetTime()) * 1000;
		remainingMsAcc += remainingMs;

		currentTime += dt;
		if (currentTime - seconds >= 1) {
			seconds++;

			double avgRemaingMs = remainingMsAcc / (double)sleepCtr;
			cout << "avg remaining ms " << avgRemaingMs << endl;

			remainingMsAcc = 0;
			sleepCtr = 0;
		}

		if (remainingMs < 0) {
			cout << "OVER FRAME TIME BY " << abs(remainingMs) << " ms" << endl;
		}

		if (remainingMs > 0) {
			sleepCtr++;
			SLEEP_FUNC(remainingMs);
		}
#endif
	}
	while(EventManager::ExitRequested() == false);

	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
