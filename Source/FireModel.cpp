#include "FireModel.h"
#include "Billboard.h"
#include "ParticleEmitter.h"
#include "ObstacleDescriptor.h"
#include "World.h"

#include "glm\glm.hpp"

FireModel::FireModel() :Model()
{
	
	ParticleDescriptor* desc = new ParticleDescriptor();
	desc->SetFireDescriptor();

	// @blenkz - need to pass a model (which this fire is) for parenting
 	ParticleEmitter* emitter = new ParticleEmitter(mPosition, this);

	// @blenkz - the model class has a variable for particle systems. 
	// Its destructor will remove the system from the world and then delete it.
	mParticleSystem = new ParticleSystem(emitter, desc);
	World::GetInstance()->AddParticleSystem(mParticleSystem);
}

void FireModel::Draw(){
	
}

void FireModel::Update(float dt){
	// @blenkz - if you add a particle system to the world, the world will take care of updating it.
	// flameSystem->Update(dt);
}

bool FireModel::ParseLine(const std::vector<ci_string> &token){
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}