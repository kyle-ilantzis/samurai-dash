//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//         with help from Jordan Rutty
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//
#include "ParticleDescriptor.h"

// V1,V2,V3 are mutally exclusive, they decide which fountain descriptor to use.
#define V1
// #define V2
// #define V3

using namespace glm;

ParticleDescriptor::ParticleDescriptor()
{
    SetFountainDescriptor();
}

#if defined(V1)
void ParticleDescriptor::SetFountainDescriptor()
{
	velocity = vec3(0.0f, 10.0f, 0.0f);
	velocityDeltaAngle = 15;

	acceleration = vec3(0.0f, -9.8f, 0.0f);

	initialSize = vec2(0.1f, 0.1f);
	initialSizeDelta = vec2(0.1f, 0.1f);

	sizeGrowthVelocity = vec2(0.7f, 0.7f);

	initialColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);
	midColor = vec4(0.8f, 0.8f, 1.0f, 1.0f);
	endColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);

	emissionRate = 50.0f;
	fadeInTime = 0.2f;
	fadeOutTime = 0.7f;
	totalLifetime = 2.0f;
	totalLifetimeDelta = 0.3f;
}
#endif

#if defined(V2)
void ParticleDescriptor::SetFountainDescriptor()
{
	velocity = vec3(0.0f, 17.0f, 0.0f);
	velocityDeltaAngle = 15;

	acceleration = vec3(0.0f, -7.0f, 0.0f);

	initialSize = vec2(0.2f, 0.2f);
	initialSizeDelta = vec2(0.1f, 0.1f);
	sizeGrowthVelocity = vec2(0.7f, 0.7f);

	initialColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);
	midColor = vec4(0.9f, 0.9f, 1, 1.0f);
	endColor = vec4(0.5f, 0.6f, 1.0f, 0.0f);

	emissionRate = 50.0f;
	fadeInTime = 0.2f;
	fadeOutTime = 4.5f;
	totalLifetime = 5.0f;
	totalLifetimeDelta = 0.3f;
}
#endif

#if defined(V3)
void ParticleDescriptor::SetFountainDescriptor()
{
	velocity = vec3(0.0f, 17.0f, 0.0f);
	velocityDeltaAngle = 15;

	acceleration = vec3(0.0f, -7.0f, 0.0f);

	initialSize = vec2(0.4f, 0.4f);
	initialSizeDelta = vec2(0.1f, 0.1f);
	sizeGrowthVelocity = vec2(1.4f, 1.4f);

	initialColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);
	midColor = vec4(0.9f, 0.9f, 1, 1.0f);
	endColor = vec4(0.5f, 0.6f, 1.0f, 0.0f);

	emissionRate = 50.0f;
	fadeInTime = 0.2f;
	fadeOutTime = 4.5f;
	totalLifetime = 5.0f;
	totalLifetimeDelta = 0.3f;
}
#endif

void ParticleDescriptor::SetPoopDescriptor()
{
	velocity = vec3(0.0f, 0.1f, 0.0f);
	velocityDeltaAngle = 4.0f;

	acceleration = vec3(0.0f, 0.0f, 0.0f);

	initialSize = vec2(2.0f, 2.0f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(0.6f, 0.5f);

	initialColor = vec4(0.545098f, 0.270588f, 0.0745098f, 1.0f);
	midColor = vec4(0.545098f, 0.270588f, 0.0745098f, 0.8f);
	endColor = vec4(0.545098f, 0.270588f, 0.0745098f, 0.4f);

	emissionRate = 40.0f;
	fadeInTime = 0.0f;
	fadeOutTime = 1.5f;
	totalLifetime = 1.0f;
	totalLifetimeDelta = 0.0f;
}

void ParticleDescriptor::SetFireDescriptor()
{
	velocity = vec3(0.0f, 2.4f, 0.0f);
	velocityDeltaAngle = 10.0f;

	acceleration = vec3(1);

	initialSize = vec2(3.0f, 3.0f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(-1.2f, -1.2f);

	initialColor = vec4(1.0f, 0.0f, 0.0f, 0.1f);
	midColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	endColor = vec4(0.5f, 0.5f, 0.8f, 0.0f);

	emissionRate = 25.0f;
	fadeInTime = 1.5f;
	fadeOutTime = 0.2f;
	totalLifetime = 1.7f;
	totalLifetimeDelta = 0.0f;
}

void ParticleDescriptor::SetFlameDescriptor(){
	velocity = vec3(0.0f, 5.0f, 0.0f);
	velocityDeltaAngle = 10;

	acceleration = vec3(0.0f, -3.8f, 0.0f);

	initialSize = vec2(0.1f, 0.1f);
	initialSizeDelta = vec2(0.1f, 0.1f);

	sizeGrowthVelocity = vec2(0.7f, 0.7f);

	initialColor = vec4(1.0f, 0.0f, 0.0f, 0.2f);
	midColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	endColor = vec4(0.5f, 0.5f, 0.8f, 0.0f);

	/**
	initialColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);

	midColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	endColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);
	**/

	emissionRate = 100.0f;
	fadeInTime = 0.1f;
	fadeOutTime = 0.3f;
	totalLifetime = 0.5f;
	totalLifetimeDelta = 0.3f;
}