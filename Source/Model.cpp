//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "Model.h"
#include "Animation.h"
#include "World.h"
#include "ParticleEmitter.h"
#include "ParticleDescriptor.h"
#include "ParticleSystem.h"
#include "RealTimeCollisionDetection.h"
#include "CapsuleModel.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;
using namespace rtcd;

Model::Model() : 
	mName("UNNAMED"),
	mPosition(0.0f, 0.0f, 0.0f), 
	mScaling(1.0f, 1.0f, 1.0f), 
	mRotationAxis(0.0f, 1.0f, 0.0f),
	mRotationAngleInDegrees(0.0f), 
	mBoundingVolume(),
	mParent(nullptr),
	mAnimation(nullptr), 
	mParticleSystem(nullptr),
	mBoundingVolumeModel(nullptr) {}

Model::~Model()
{
	if (mParticleSystem)
    {
        World::GetInstance()->RemoveParticleSystem(mParticleSystem);
        delete mParticleSystem;
    }

	if (mBoundingVolumeModel) { delete mBoundingVolumeModel; }
}

void Model::Update(float dt)
{
}

void Model::Draw()
{
}


void Model::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0].c_str());
			getchar();
			exit(-1);
		}
	}
}

bool Model::ParseLine(const std::vector<ci_string> &token)
{
		if (token.empty() == false)
	{
		if (token[0].empty() == false && token[0][0] == '#')
		{
			return true;
		}
		else if (token[0] == "name")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			mName = token[2];	
		}
		else if (token[0] == "position")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mPosition.x = static_cast<float>(atof(token[2].c_str()));
			mPosition.y = static_cast<float>(atof(token[3].c_str()));
			mPosition.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "rotation")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mRotationAxis.x = static_cast<float>(atof(token[2].c_str()));
			mRotationAxis.y = static_cast<float>(atof(token[3].c_str()));
			mRotationAxis.z = static_cast<float>(atof(token[4].c_str()));
			mRotationAngleInDegrees = static_cast<float>(atof(token[5].c_str()));

			glm::normalize(mRotationAxis);
		}
		else if (token[0] == "scaling")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mScaling.x = static_cast<float>(atof(token[2].c_str()));
			mScaling.y = static_cast<float>(atof(token[3].c_str()));
			mScaling.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "animation")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			ci_string animName = token[2];
            
            mAnimation = World::GetInstance()->FindAnimation(animName);
		}
        else if (token[0] == "particlesystem")
        {
            assert(token.size() > 2);
            assert(token[1] == "=");
			assert(token[2] == "\"fire\"" || token[2] == "\"fountain\"" || token[2] == "\"JetFlame1\"" || token[2] == "\"UFOBeam\"" || token[2] == "\"JetFlame2\"" || token[2] == "\"JetFlame3\"" || token[2] == "\"EnemyAttackLazer\""); // only to hardcoded particle systems

			// Create Particle Emitter
			ParticleEmitter* emitter;

			// Define flame location in World
			if (token[2] == "\"JetFlame1\"")
			{
				emitter = new ParticleEmitter(vec3(0.3f, 0.4f, 3.2f), this);
			}
			else if (token[2] == "\"JetFlame2\"")
			{
				emitter = new ParticleEmitter(vec3(-0.3f, 0.4f, 3.2f), this);
			}
			else if (token[2] == "\"JetFlame3\"")
			{
				emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 3.5f), this);
			}
			else if (token[2] == "\"UFOBeam\"")
			{
				emitter = new ParticleEmitter(vec3(0.0f, -1.0f, 0.0f), this);
			}
			else if (token[2] == "\"EnemyAttackLazer\"")
			{
				emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 3.5f), this);
			}
			else
			{
				emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f), this);
			}
   
			// Create new particle descriptor
            ParticleDescriptor* desc = new ParticleDescriptor();
            
			// The descriptor being set for plane Engines.
            if (token[2] == "\"fire\"")
            {
                desc->SetFireDescriptor();
            }
            else if (token[2] == "\"fountain\"")
            {
                desc->SetFountainDescriptor();
            }
			else if (token[2] == "\"JetFlame1\"")
			{
				desc->SetJetFlameDescriptor();
			}
			else if (token[2] == "\"JetFlame2\"")
			{
				desc->SetJetFlameDescriptor();
			}
			else if (token[2] == "\"JetFlame3\"")
			{
				desc->SetEnemyJetFlameDescriptor();
			}
			else if (token[2] == "\"EnemyAttackLazer\"")
			{
				desc->SetEnemyJetAttackDescriptor();
			}
			else if (token[2] == "\"UFOBeam\"")
			{
				desc->SetUFODescriptor();
			}
            
			// Create Particle System & Get World Instance
            mParticleSystem = new ParticleSystem(emitter, desc);
            World::GetInstance()->AddParticleSystem(mParticleSystem);
        }
		// Code for collision capsule creation
		else if (token[0] == "boundingVolume") {

			assert(token.size() > 15 );
			assert(token[1] == "=");
			assert(token[2] == "capsule");
			assert(token[3] == "a");
			assert(token[4] == "=");
			float ax = static_cast<float>(atof(token[5].c_str()));
			float ay = static_cast<float>(atof(token[6].c_str()));
			float az = static_cast<float>(atof(token[7].c_str()));
			assert(token[8] == "b");
			assert(token[9] == "=");
			float bx = static_cast<float>(atof(token[10].c_str()));
			float by = static_cast<float>(atof(token[11].c_str()));
			float bz = static_cast<float>(atof(token[12].c_str()));
			assert(token[13] == "r");
			assert(token[14] == "=");
			float r = static_cast<float>(atof(token[15].c_str()));

			setCapsuleBoundingVolume(new Capsule(vec3(ax, ay, az), vec3(bx, by, bz), r));
		}
		else
		{
			return false;
		}
	}
	return true;
}

glm::mat4 Model::GetWorldMatrix() const
{
	mat4 worldMatrix(1.0f);

    // Solution TRS
#if 1
    if (mAnimation)
    {
        // Get world transform from animation key frames / current time
        worldMatrix = mAnimation->GetAnimationWorldMatrix();
    }
    else
    {
        mat4 t = glm::translate(mat4(1.0f), mPosition);
        mat4 r = glm::rotate(mat4(1.0f), mRotationAngleInDegrees, mRotationAxis);
        mat4 s = glm::scale(mat4(1.0f), mScaling);
        worldMatrix = t * r * s;

		if (mParent) {
			worldMatrix = mParent->GetWorldMatrix() * worldMatrix;
		}
    }
#endif
 
	return worldMatrix;
}

void Model::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

void Model::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void Model::SetRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;
}

void Model::setCapsuleBoundingVolume(Capsule* capsule) {
	
	mBoundingVolume.setCapsule(capsule);

	if (World::DRAW_BOUNDING_VOLUME) {
		
		if (mBoundingVolumeModel) { delete mBoundingVolumeModel; }
		
		mBoundingVolumeModel = new CapsuleModel(*capsule);
		mBoundingVolumeModel->SetParent(this);
	}
}