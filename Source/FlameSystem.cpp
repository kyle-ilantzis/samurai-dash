#include "FlameSystem.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "ParticleDescriptor.h"
#include "World.h"
#include "EventManager.h"
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;

FlameSystem::FlameSystem(ParticleEmitter* emitter, ParticleDescriptor* descriptor) :ParticleSystem(emitter,descriptor)
{
	
}

void FlameSystem::Update(float dt){
	// Emit particle according to the emission rate
	float averageTimeBetweenEmission = 1.0f / mpDescriptor->emissionRate;
	float randomValue = EventManager::GetRandomFloat(0.0f, 1.0f) * averageTimeBetweenEmission;
	while (mInactiveParticles.size() > 0 && randomValue < dt)
	{
		randomValue += averageTimeBetweenEmission;

		// emit particle
		// transfer a particle from the inactive pool to the active pool
		Particle* newParticle = mInactiveParticles.back();
		mParticleList.push_back(newParticle);
		mInactiveParticles.pop_back();

		// Set particle initial parameters
		newParticle->billboard.position = mpEmitter->GetRandomPosition();
		newParticle->billboard.size = mpDescriptor->initialSize + EventManager::GetRandomFloat(-1.0f, 1.0f) * mpDescriptor->initialSizeDelta;
		newParticle->billboard.color = mpDescriptor->initialColor;
		newParticle->currentTime = 0.0f;
		newParticle->lifeTime = mpDescriptor->totalLifetime + mpDescriptor->totalLifetimeDelta * EventManager::GetRandomFloat(-1.0f, 1.0f);
		newParticle->velocity = mpDescriptor->velocity;

		// @TODO 6 - Initial Random Particle Velocity vector
		//
		// Adjust the random velocity according to a random vertical angle variation on a cone
		//
		// Step 1 : You can rotate the velocity vector by a random number between 0 and
		//          mpDescriptor->velocityDeltaAngle.
		// Step 2 : You can rotate the result in step 1 by an random angle from 0 to
		//          360 degrees about the original velocity vector

		vec3 velocity = rotateZ(newParticle->velocity, EventManager::GetRandomFloat(-mpDescriptor->velocityDeltaAngle, mpDescriptor->velocityDeltaAngle));
		newParticle->velocity = velocity;

		World::GetInstance()->AddBillboard(&newParticle->billboard);
	}


	for (std::list<Particle*>::iterator it = mParticleList.begin(); it != mParticleList.end();)
	{
		Particle* p = *it;
		p->currentTime += dt;

		// @TODO 5 - Update each particle's parameter
		//
		// Update the velocity and position of the particle from the acceleration of the descriptor
		// Update the size of the particle according to its growth
		// Update The color is also updated in 3 phases
		//
		//
		// Phase 1 - Initial: from t = [0, fadeInTime] - Linearly interpolate between initial color and mid color
		// Phase 2 - Mid:     from t = [fadeInTime, lifeTime - fadeOutTime] - color is mid color
		// Phase 3 - End:     from t = [lifeTime - fadeOutTime, lifeTime]

		vec3 velocity = p->velocity;
		p->velocity += mpDescriptor->acceleration * dt;
		p->billboard.position += velocity * dt + 0.5f * mpDescriptor->acceleration * dt * dt;

		if (p->currentTime <= mpDescriptor->fadeInTime) { // Initial
			float c = p->currentTime / mpDescriptor->fadeInTime;
			p->billboard.color = mix(mpDescriptor->initialColor, mpDescriptor->midColor, c);
		}
		else if (p->currentTime <= p->lifeTime - mpDescriptor->fadeOutTime) { // Mid
			p->billboard.color = mpDescriptor->midColor;
		}
		else if (p->currentTime <= p->lifeTime) { // End
			float c = (p->currentTime - (p->lifeTime - mpDescriptor->fadeOutTime)) / mpDescriptor->fadeOutTime;
			p->billboard.color = mix(mpDescriptor->midColor, mpDescriptor->endColor, c);
		}

		p->billboard.size += mpDescriptor->sizeGrowthVelocity * dt;

		// Particles are destroyed if expired
		// Remove from the send particle to inactive list
		// Remove the billboard from the world
		if (p->currentTime > p->lifeTime)
		{
			mInactiveParticles.push_back(*it);

			World::GetInstance()->RemoveBillboard(&(*it)->billboard);
			it = mParticleList.erase(it);
		}
		else
		{
			++it;
		}
	}

}

FlameSystem::~FlameSystem()
{
}
