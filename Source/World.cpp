//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

// Other Assets
#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include <GLFW/glfw3.h>
#include "EventManager.h"
#include "TextureLoader.h"
#include "SplineFactory.h"
#include "Animation.h"
#include "ParticleSystem.h"

// Model Assets
#include "CubeModel.h"
#include "SphereModel.h"
#include "Billboard.h"
#include "Obstacles.h"
#include "Discoball.h"
#include "UFOModel.h"
#include "FighterJetModel.h"

using namespace std;
using namespace glm;

World* World::instance;

World::World()
{
    instance = this;
	
	// Setup Camera
	mCamera.push_back(new FirstPersonCamera(vec3(3.0f, 1.0f, 5.0f)));
	mCamera.push_back(new StaticCamera(vec3(3.0f, 30.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
	mCamera.push_back(new StaticCamera(vec3(0.5f,  0.5f, 5.0f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
	mCurrentCamera = 0;

    // TODO: You can play with different textures by changing the billboardTest.bmp to another texture

	// int billboardTextureID = TexureLoader::LoadTexture("../Assets/Textures/BillboardTest.bmp");
    int billboardTextureID = TextureLoader::LoadTexture("../Assets/Textures/Particle.png");
    assert(billboardTextureID != 0);

    mpBillboardList = new BillboardList(2048, billboardTextureID);

	mSplineModel = nullptr;
	mPlayerModel = nullptr;
	mFighterJetModel = nullptr;
	mUFOModel = nullptr;
	mObstacles = nullptr;
	mSkyboxModel = nullptr;

    // TODO - You can un-comment out these 2 temporary billboards and particle system
    // That can help you debug billboards, you can set the billboard texture to billboardTest.png
    /*    Billboard *b = new Billboard();
     b->size  = glm::vec2(2.0, 2.0);
     b->position = glm::vec3(0.0, 3.0, 0.0);
     b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
     
     Billboard *b2 = new Billboard();
     b2->size  = glm::vec2(2.0, 2.0);
     b2->position = glm::vec3(0.0, 3.0, 1.0);
     b2->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

     mpBillboardList->AddBillboard(b);
     mpBillboardList->AddBillboard(b2);

     
     ParticleDescriptor* fountainDescriptor = new ParticleDescriptor();
     fountainDescriptor->SetFireDescriptor();
     
     ParticleDescriptor* fireDescriptor = new ParticleDescriptor();
     fireDescriptor->SetFireDescriptor();
     
     ParticleEmitter* emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f));
     
     ParticleSystem* ps = new ParticleSystem(emitter, fountainDescriptor);
     AddParticleSystem(ps);

     */    // TMP
}

World::~World()
{
	// Models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		delete *it;
	}

	mModel.clear();

	for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
	{
		delete *it;
	}

	mAnimation.clear();

	for (vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
	{
		delete *it;
	}

	mAnimationKey.clear();

	// Camera
	for (vector<Camera*>::iterator it = mCamera.begin(); it < mCamera.end(); ++it)
	{
		delete *it;
	}
	mCamera.clear();

	if (mSplineModel) delete mSplineModel;
	if (mObstacles) delete mObstacles;
	if (mSkyboxModel) delete mSkyboxModel;
	
	delete mpBillboardList;
}

World* World::GetInstance()
{
    return instance;
}

void World::Draw()
{
	Renderer::BeginFrame();

	// Set shader to use
	glUseProgram(Renderer::GetShaderProgramID());

	// This looks for the MVP Uniform variable in the Vertex Program
	GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");
	GLuint WorldMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	GLuint ViewMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform");
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectionTransform");

	SetLighting();
	SetCoefficient();

	// Send the view projection constants to the shader
	mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
	mat4 View = mCamera[mCurrentCamera]->GetViewMatrix();
	glm::mat4 World(1.0f);
	mat4 Projection = mCamera[mCurrentCamera]->GetProjectionMatrix();
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);
	glUniformMatrix4fv(WorldMatrixID, 1, GL_FALSE, &World[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &Projection[0][0]);

	if (mObstacles)
	{
		for (Obstacles::obstacle_vector_itr it = mObstacles->getObstacles().begin(); it != mObstacles->getObstacles().end(); ++it)
		{
			Model* model = (*it).second;
			model->Draw();
		}

		if (DRAW_BOUNDING_VOLUME) {
			for (Obstacles::obstacle_vector_itr it = mObstacles->getObstacles().begin(); it != mObstacles->getObstacles().end(); ++it)
			{
				Model* model = (*it).second;
				Model* bvm = model->GetBoundingVolumeModel();

				if (bvm) 
				{
					bvm->Draw();
				}
			}
		}
	}

	// Set shader to use
	glUseProgram(Renderer::GetShaderProgramID());

	// This looks for the MVP Uniform variable in the Vertex Program
	VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");

	// Send the view projection constants to the shader
	VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->Draw();
	}

	if (DRAW_BOUNDING_VOLUME) {
		for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
		{
			Model* bvm = (*it)->GetBoundingVolumeModel();

			if (bvm) {
				bvm->Draw();
			}		
		}
	}

	if (DRAW_ANIM_PATH) {

		// Draw Path Lines
		// Set Shader for path lines
		unsigned int prevShader = Renderer::GetCurrentShader();
		Renderer::SetShader(SHADER_PATH_LINES);
		glUseProgram(Renderer::GetShaderProgramID());

		// Send the view projection constants to the shader
		VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

		for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
		{
			mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
			glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

			(*it)->Draw();
		}

		for (vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
		{
			mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
			glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

			(*it)->Draw();
		}

		// Restore previous shader
		Renderer::SetShader((ShaderType)prevShader);
	}

    Renderer::CheckForErrors();
    
	// Draw Spline
	if (mSplineModel) {
		mSplineModel->Draw();
		Model* bvm = mSplineModel->GetBoundingVolumeModel();
		if (DRAW_BOUNDING_VOLUME && bvm) { bvm->Draw(); }
	}

	if (mSkyboxModel) {
		mSkyboxModel->Draw();
	}

    // Draw Billboards
    mpBillboardList->Draw();

	Renderer::EndFrame();
}

Animation* World::FindAnimation(ci_string animName)
{
    for(std::vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
    {
        if((*it)->GetName() == animName)
        {
            return *it;
        }
    }
    return nullptr;
}

AnimationKey* World::FindAnimationKey(ci_string keyName)
{
    for(std::vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
    {
        if((*it)->GetName() == keyName)
        {
            return *it;
        }
    }
    return nullptr;
}

const Camera* World::GetCurrentCamera() const
{
     return mCamera[mCurrentCamera];
}

void World::AddBillboard(Billboard* b)
{
    mpBillboardList->AddBillboard(b);
}

void World::RemoveBillboard(Billboard* b)
{
    mpBillboardList->RemoveBillboard(b);
}

void World::AddParticleSystem(ParticleSystem* particleSystem)
{
    mParticleSystemList.push_back(particleSystem);
}

void World::RemoveParticleSystem(ParticleSystem* particleSystem)
{
    vector<ParticleSystem*>::iterator it = std::find(mParticleSystemList.begin(), mParticleSystemList.end(), particleSystem);
    mParticleSystemList.erase(it);
}

void World::SetLighting()
{
	// Get a handle for Light Attributes uniform
	GLuint LightPositionID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition");
	GLuint LightColorID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightColor");
	GLuint LightAttenuationID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightAttenuation");

	//const vec4 lightPosition(5.0f, 5.0f, -5.0f, 1.0f); // If w = 1.0f, we have a point light
	const vec4 lightPosition(25.0f, 25.0f, 5.0f, 0.0f); // If w = 0.0f, we have a directional light

	const vec3 lightColor(1.0f, 1.0f, 1.0f);
	glUniform4f(LightPositionID, lightPosition.x, lightPosition.y, lightPosition.z, lightPosition.w);
	glUniform3f(LightColorID, lightColor.r, lightColor.g, lightColor.b);
}

void World::SetCoefficient()
{
	GLuint MaterialAmbientID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialAmbient");
	GLuint MaterialDiffuseID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialDiffuse");
	GLuint MaterialSpecularID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialSpecular");
	GLuint MaterialExponentID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialExponent");
	// Material Coefficients
	const float ka = 0.2f;
	const float kd = 0.8f;
	const float ks = 0.2f;
	const float n = 90.0f;

	// Set shader constants
	glUniform1f(MaterialAmbientID, ka);
	glUniform1f(MaterialDiffuseID, kd);
	glUniform1f(MaterialSpecularID, ks);
	glUniform1f(MaterialExponentID, n);
}
