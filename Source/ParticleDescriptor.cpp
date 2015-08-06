//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//         with help from Jordan Rutty
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//
#include "ParticleDescriptor.h"

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

void ParticleDescriptor::SetFireDescriptor()
{
	velocity = vec3(0.0f, 0.1f, 0.0f);
	velocityDeltaAngle = 4.0f;

	acceleration = vec3(0.0f, 0.0f, 0.0f);

	initialSize = vec2(0.25f, 0.25f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(0.2f, 0.2f);

	initialColor = vec4(1.0f, 0.0f, 0.0f, 0.1f);
	midColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	endColor = vec4(0.0f, 0.0f, 0.8f, 0.0f);

	emissionRate = 25.0f;
	fadeInTime = 0.5f;
	fadeOutTime = 1.5f;
	totalLifetime = 2.5f;
	totalLifetimeDelta = 0.0f;
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

void ParticleDescriptor::SetFireDescriptor()
{
	velocity = vec3(0.0f, 2.4f, 0.0f);
	velocityDeltaAngle = 10.0f;

	acceleration = vec3(0, 0, 0);

	initialSize = vec2(6.0f, 6.0f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(-2.4f, -2.4f);

	initialColor = vec4(1.0f, 0.0f, 0.0f, 0.2f);
	midColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	endColor = vec4(0.5f, 0.5f, 0.8f, 0.0f);

	emissionRate = 25.0f;
	fadeInTime = 1.5f;
	fadeOutTime = 0.2f;
	totalLifetime = 1.7f;
	totalLifetimeDelta = 0.0f;
}
#endif
void ParticleDescriptor::SetJetFlameDescriptor()
{
	velocity = vec3(0.0f, 0.1f, 0.0f);
	velocityDeltaAngle = 4.0f;

	acceleration = vec3(0.0f, 0.0f, 0.0f);

	initialSize = vec2(0.6f, 0.6f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(1.5f, 0.9f);

	initialColor = vec4(0.862745f, 0.0784314f, 0.235294f, 1.0f);
	midColor = vec4(0.862745f, 0.0784314f, 0.235294f, 0.8f);
	endColor = vec4(0.745098f, 0.745098f, 0.745098f, 0.6f);

	emissionRate = 10.0f; // Original 50
	fadeInTime = 0.0f;
	fadeOutTime = 3.5f;
	totalLifetime = 0.7f;
	totalLifetimeDelta = 0.0f;
}

void ParticleDescriptor::SetUFODescriptor()
{
	velocity = vec3(70.0f, 0.0f, 70.0f);
	velocityDeltaAngle = 120.0f;

	acceleration = vec3(1.0f, 1.0f, 1.0f);

	initialSize = vec2(5.0f, 5.0f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(0.6f, 0.5f);

	initialColor = vec4(1 ,0.843137 ,0, 1);
	midColor = vec4(1, 0.843137, 0, 1);
	endColor = vec4(0, 1, 0, 1);

	emissionRate = 10.0f; // Original 20
	fadeInTime = 0.0f;
	fadeOutTime = 1.5f;
	totalLifetime = 2.0f;
	totalLifetimeDelta = 0.0f;
}

void ParticleDescriptor::SetEnemyJetFlameDescriptor()
{
	velocity = vec3(0.0f, 0.01f, 0.0f);
	velocityDeltaAngle = 0.1f;

	acceleration = vec3(0.0f, 0.0f, 0.0f);

	initialSize = vec2(3.0f, 3.0f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(2.0f, 2.0f);

	initialColor = vec4(0.741176f, 0.717647f, 0.419608f, 1.0f);
	midColor = vec4(0.517647f, 0.517647f, 0.517647f, 1.0f);
	endColor = vec4(0.156863f, 0.156863f, 0.156863f, 0.8f);

	emissionRate = 5.3f; //Original 13.3
	fadeInTime = 0.0f;
	fadeOutTime = 0.4f;
	totalLifetime = 1.0f;
	totalLifetimeDelta = 0.1f;
}

void ParticleDescriptor::SetEnemyJetAttackDescriptor()
{
	velocity = vec3(0.0f, 0.01f, -30.0f);
	velocityDeltaAngle = 10.9f;

	acceleration = vec3(0.0f, 0.0f, 3.0f);

	initialSize = vec2(1.0f, 1.0f);
	initialSizeDelta = vec2(2.0f, 0.02f);

	sizeGrowthVelocity = vec2(1.0f, 1.0f);

	initialColor = vec4(0.486275f, 0.988235f, 0.0f, 1.0f);
	midColor = vec4(0.486275f, 0.988235f, 0.0f, 1.0f);
	endColor = vec4(0.486275f, 0.988235f, 0.0f, 1.0f);

	emissionRate = 2.3f; //Original 6.3
	fadeInTime = 0.0f;
	fadeOutTime = 3.0f;
	totalLifetime = 2.5f;
	totalLifetimeDelta = 0.1f;
}