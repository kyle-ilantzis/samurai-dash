#include "BarrelModel.h"
#include "AssetsDir.h"
#include "Animation.h"
#include "TextureLoader.h"
#include "RendererHelper.h"
#include "World.h"


using namespace std;
using namespace glm;


const glm::vec3 BarrelModel::BARREL_SHAPE_COLORS[] = { vec3(0.372549f, 0.619608f, 0.627451f) };

BarrelModel::BarrelModel() : ObjectModel(HOLY_BARREL, HOLY_BARREL_MATERIAL, BARREL_SHAPE_COLORS), barrelTexture()
{
	SetScaling(glm::vec3(0.6f, 0.6f, 0.6f));
	
	FreeImage barrelPic(TEXTURE_BARREL);
	barrelTexture.SetData(barrelPic);

}

void BarrelModel::Draw()
{
	ShaderType oldShader = (ShaderType)Renderer::GetCurrentShader();

	Shader shader = RendererHelper::GetShader(SHADER_TEXTURED);
	Renderer::SetShader(SHADER_TEXTURED);

	shader.Bind();
	shader.SetMatrix("ViewProjectionTransform", World::GetInstance()->GetCamera()->GetViewProjectionMatrix());
	shader.SetMatrix("ViewTransform", World::GetInstance()->GetCamera()->GetViewMatrix());
	shader.SetMatrix("ProjectionTransform", World::GetInstance()->GetCamera()->GetProjectionMatrix());
	World::GetInstance()->SetCoefficient();
	World::GetInstance()->SetLighting();

	shader.SetTexture("myTextureSampler", barrelTexture, GL_TEXTURE0);
	ObjectModel::Draw();
	Renderer::SetShader(oldShader);
}