#include "LoadingScreen.h"
#include "TextureLoader.h"
#include "AssetsDir.h"
#include "Renderer.h"
#include "Camera.h"

#include <glm/glm.hpp>

using namespace glm;

const float LoadingScreen::LOADING_MSG_DISTANCE = 100.0f;
const float LoadingScreen::LOADING_MSG_SIZE = 3;
const vec4 LoadingScreen::LOADING_MSG_BACKGROUND = vec4(0, 0, 1, 1);

LoadingScreen::LoadingScreen() : 
	mLoadingMsgTexture(), 
	mBillboardList(nullptr),
	mLoadingMsgBillboard(),
	mOldWorldCameraType(WORLD_CAMERA_NIL),
	mOldClearColor(Renderer::DEFAULT_CLEAR_COLOR) {

	FreeImage loadingMsgImg(TEXTURE_LOADING_MSG);
	mLoadingMsgTexture.SetData(loadingMsgImg);

	mBillboardList = new BillboardList(1, mLoadingMsgTexture.GetTextureId());
	mBillboardList->AddBillboard(&mLoadingMsgBillboard);

	World* w = World::GetInstance();
	
	mOldWorldCameraType = w->GetWorldCameraType();
	w->SetWorldCameraType(WORLD_CAMERA_STATIC_ABOVE);

	Camera* c = w->GetCamera();
	vec3 cameraPosition = c->GetPosition();
	mat4 viewMatrix = c->GetViewMatrix();
	vec3 back = vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);

	mLoadingMsgBillboard.position = cameraPosition + -back * Camera::near * LOADING_MSG_DISTANCE;
	mLoadingMsgBillboard.size = vec2(LOADING_MSG_SIZE);
	mLoadingMsgBillboard.color = vec4(1);

	mOldClearColor = Renderer::GetClearColor();
	Renderer::SetClearColor(LOADING_MSG_BACKGROUND);

	mBillboardList->Update(0);
}

LoadingScreen::~LoadingScreen() {

	if (mBillboardList) {
		mBillboardList->RemoveBillboard(&mLoadingMsgBillboard);
		delete mBillboardList;
	}

	World::GetInstance()->SetWorldCameraType(mOldWorldCameraType);

	Renderer::SetClearColor(mOldClearColor);
}

void LoadingScreen::Draw() {

	Renderer::BeginFrame();
	mBillboardList->Draw();
	Renderer::EndFrame();

	Renderer::BeginFrame();
	mBillboardList->Draw();
	Renderer::EndFrame();
}