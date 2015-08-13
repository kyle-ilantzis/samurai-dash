//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

struct GLFWwindow;

enum GameStatus
{
	PAUSED,
	RUNNING,
};

// A class for knowing if a key is typed.
// That is you want the key press event once and not constantly as the key is held down.
class KeyTyped {

public:
	KeyTyped(int key) : mKey(key), mBeforePressed(), mNowPressed() {}

	void Update();
	bool IsKeyTyped() { return !mBeforePressed && mNowPressed; }

private:
	int mKey;
	bool mBeforePressed;
	bool mNowPressed;
};

class EventManager
{
public:
	static void Initialize();
	static void Shutdown();

	static void Update();

	static float GetFrameTime();
	static bool ExitRequested();

	static GLFWwindow* GetWindow();

	static float GetMouseMotionX();
	static float GetMouseMotionY();

	static void EnableMouseCursor();
	static void DisableMouseCursor();
    static float GetRandomFloat(float min, float max);

	static bool IsKeyPressed(int key);
	static bool IsKeyUnpressed(int key);

	static GameStatus status;
private:
	// Time
	static double sLastFrameTime;
	static float sFrameTime;

	// Mouse
	static double sLastMousePositionX;
	static float  sMouseDeltaX;
	static double sLastMousePositionY;
	static float  sMouseDeltaY;

	// Window
	static GLFWwindow* spWindow;

};
