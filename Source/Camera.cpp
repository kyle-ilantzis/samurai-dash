//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "Camera.h"
#include <GLM/gtx/transform.hpp>

using namespace glm;

const float Camera::fieldOfView = 45.0f;
const float Camera::aspect = 4.0f / 3.0f;
const float Camera::nearView = 0.1f;
const float Camera::farView = 100.0f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

mat4 Camera::GetViewProjectionMatrix() const
{
	// @TODO 1 - Calculate View Projection Matrix
	//           The projection matrix is hardcoded below
	//           The view matrix is set in the derived camera classes.
	
    // mat4 viewProjection(1.0f);
        
    // return viewProjection;

	// @MYCODE
	return GetProjectionMatrix() * GetViewMatrix();
}

mat4 Camera::GetProjectionMatrix() const
{
	return perspective(fieldOfView, aspect, nearView, farView);
}
