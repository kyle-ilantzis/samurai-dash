#include "FireModel.h"
#include "World.h"
#include "TextureLoader.h"

FireModel::FireModel() :Model()
{
	
	desc = new ParticleDescriptor();
	desc->SetFireDescriptor();
	emitter = new ParticleEmitter(mPosition);
	flameSystem = new ParticleSystem(emitter, desc);
	World::GetInstance()->AddParticleSystem(flameSystem);
	
}

void FireModel::Draw(){
	
}

void FireModel::Update(float dt){
	flameSystem->Update(dt);
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


FireModel::~FireModel()
{
	delete flameSystem;
	delete emitter;
	delete desc;
}
