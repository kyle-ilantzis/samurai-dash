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

#include <GLFW/glfw3.h>

#define FPS 60

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;    
    
	world.LoadScene();

	// If Running on Windows Then Play Background Music
	PlaySound(TEXT("../Assets/Sounds/RainbowRoad.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

//	if (argc > 1)
//	{
//		world.LoadScene(argv[1]);
//	}
//	else
//	{
//		// TODO - You can alternate between different scenes for testing different things
//		// Static Scene contains no animation
//		// Animated Scene does
//		world.LoadScene("../Assets/Scenes/AnimatedSceneWithParticles.scene");
//		world.LoadScene("../Assets/Scenes/AnimatedScene.scene");
//		world.LoadScene("../Assets/Scenes/Spline.scene");
//		world.LoadScene("../Assets/Scenes/StaticScene.scene");
//		world.LoadScene("../Assets/Scenes/CoordinateSystem.scene");
//#endif
//	}

	double fps = 1.0f / FPS;

	// Main Loop
	do
	{
		double start = glfwGetTime();

		// Update Event Manager - Frame time / input / events processing 
		EventManager::Update();

		// Update World
		float dt = EventManager::GetFrameTime();
		world.Update(dt);

		// Draw World
		world.Draw();

		// Each frame should be "fps" seconds long.
		// If updating and rendering took less than fps seconds long then sleep for the remainder.
		int remainingMs = (start + fps - glfwGetTime()) * 1000;
		if (remainingMs > 0) {
			SLEEP_FUNC(remainingMs);
		}
		world.Draw();    
	}
	while(EventManager::ExitRequested() == false);

	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
