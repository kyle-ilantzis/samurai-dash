#include "SkyboxModel.h"
#include "World.h"
#include "RendererHelper.h"
#include "Camera.h"

using namespace glm;

SkyboxModel::SkyboxModel() : mCubemap() {
	
	FreeImage right(SKYBOXMODEL_SKYBOX_RIGHT);
	FreeImage left(SKYBOXMODEL_SKYBOX_LEFT);
	FreeImage top(SKYBOXMODEL_SKYBOX_TOP);
	FreeImage bottom(SKYBOXMODEL_SKYBOX_BOTTOM);
	FreeImage back(SKYBOXMODEL_SKYBOX_BACK);
	FreeImage front(SKYBOXMODEL_SKYBOX_FRONT);

	mCubemap.SetPosXData(right);
	mCubemap.SetNegXData(left);
	// In the fragment shader we flipped the y value of the texture coordinate,
	// so we rearrange the neg and pos y.
	mCubemap.SetPosYData(bottom);
	mCubemap.SetNegYData(top);
	// we also rearrange the neg and pos z.
	mCubemap.SetPosZData(front);
	mCubemap.SetNegZData(back);

	mScaling = vec3(Camera::farView);
}

void SkyboxModel::Update(float dt) {
	
	Camera* c = World::GetInstance()->GetCamera();

	mPosition = c->GetPosition();
}

void SkyboxModel::Draw() {

	ShaderType oldShader = (ShaderType)Renderer::GetCurrentShader();

	GLint oldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);


	// Since the skybox is on the far plane of the projection frustrum
	// we want the skybox to pass the z-buffer test if if it LESS-THAN-OR-EQUAL
	// instead of the default LESS-THAN.
	// (see the skybox vertex shader for more info).
	glDepthFunc(GL_LEQUAL);


	Shader shader = RendererHelper::GetShader(SHADER_SKYBOX);
	Renderer::SetShader(SHADER_SKYBOX);
	shader.Bind();

	shader.SetMatrix("ViewProjectionTransform", World::GetInstance()->GetCamera()->GetViewProjectionMatrix());
	shader.SetTexture("TextureCubemap", mCubemap, GL_TEXTURE0);

	CubeModel::Draw();

	glDepthFunc(oldDepthFuncMode);
	Renderer::SetShader(oldShader);
}