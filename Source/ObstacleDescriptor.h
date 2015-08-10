#pragma once

#include <glm/glm.hpp>
#include "ParticleSystem.h"
#include "ParticleDescriptor.h"
#include "ObstacleDescriptor.h"

class ObstacleDescriptor: public ParticleDescriptor
{
public:
	ObstacleDescriptor(void);

	void createFlameObstacle();
	void createIceObstacle();


	~ObstacleDescriptor(void);

private:
    
    glm::vec3 velocity;                 // initial speed vector - units per second
    float velocityDeltaAngle;           // angle in degrees from velocity - you can use spherical coordinates to alter velocity
    glm::vec3 acceleration;             // units per second^2
    
    glm::vec2 initialSize;              // initial size of billboard in x and y
    glm::vec2 initialSizeDelta;
    
    glm::vec2 sizeGrowthVelocity;       // growth of the billboard in units per second
    
    glm::vec4 initialColor;                // initial particle color - linearly interpolate towards mid color
    glm::vec4 midColor;                 // mid color - constant during mid stage
    glm::vec4 endColor;                 // end color - interpolates from mid to end color during end stage
    
    float emissionRate;                 // number of particles per second emitted
    float fadeInTime;                   // time from initial to mid stage
    float fadeOutTime;                  // time from mid to end stage
    float totalLifetime;                // amount of time in seconds the particle will remain alive
    float totalLifetimeDelta;

	friend class FlameSystem;
};

