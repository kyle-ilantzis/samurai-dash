#include "ObstacleDescriptor.h"

using namespace glm;

ObstacleDescriptor::ObstacleDescriptor(void) :ParticleDescriptor()
{
	createFlameObstacle();
}

void ObstacleDescriptor::createIceObstacle(){
	velocity = vec3(0.0f, 8.0f, 0.0f);
    velocityDeltaAngle = 0;
    
    acceleration = vec3(0.0f, -5.0f, 0.0f);
    
    initialSize = vec2(0.1f, 0.1f);
    initialSizeDelta = vec2(0.1f, 0.1f);
    
    sizeGrowthVelocity = vec2(0.7f, 0.7f);
    
    initialColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);
	
    midColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    endColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);

    emissionRate = 2.0f;
    fadeInTime = 0.1f;
    fadeOutTime = 0.3f;
    totalLifetime = 0.5f;
    totalLifetimeDelta = 0.3f;
}

void ObstacleDescriptor::createFlameObstacle(){
	velocity = vec3(0.0f, 5.0f, 0.0f);
    velocityDeltaAngle = 10;
    
    acceleration = vec3(0.0f, -3.8f, 0.0f);
    
    initialSize = vec2(0.1f, 0.1f);
    initialSizeDelta = vec2(0.1f, 0.1f);
    
    sizeGrowthVelocity = vec2(0.7f, 0.7f);
    
    initialColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);
	
    midColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    endColor = vec4(0.5f, 0.5f, 0.5f, 0.0f);

    emissionRate = 100.0f;
    fadeInTime = 0.1f;
    fadeOutTime = 0.3f;
    totalLifetime = 0.5f;
    totalLifetimeDelta = 0.3f;
}

ObstacleDescriptor::~ObstacleDescriptor(void)
{
}
