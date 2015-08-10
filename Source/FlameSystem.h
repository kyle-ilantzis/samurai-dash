
#pragma once

#include "Billboard.h"
#include "ParticleSystem.h"

class ParticleDescriptor;
class ParticleEmitter;


class FlameSystem:public ParticleSystem
{
public:
	FlameSystem(ParticleEmitter* emitter, ParticleDescriptor* descriptor);
	~FlameSystem();

	virtual void Update(float dt);


};
