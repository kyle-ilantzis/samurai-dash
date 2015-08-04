#pragma once

#include "Model.h"
#include "glm\glm.hpp"
#include "Billboard.h"
#include "ParticleEmitter.h"
#include "ObstacleDescriptor.h"

using namespace glm;

class FireModel: public Model
{
public:
	FireModel();
	
	virtual void Draw();
	virtual bool ParseLine(const std::vector<ci_string> &token);
	virtual void Update(float dt);
	~FireModel();

private:
	ParticleDescriptor* desc;
	ParticleSystem* flameSystem;
	ParticleEmitter* emitter;
};

