//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include <GLM/glm.hpp>

class Camera
{
public:
	static const float fieldOfView;
	static const float aspect;
	static const float nearView;
	static const float farView;

	Camera();
	virtual ~Camera();

	virtual void Update(float dt) = 0;

	virtual glm::vec3 GetPosition() const = 0;
	virtual glm::mat4 GetViewMatrix() const = 0;
	virtual glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const;

private:

};
