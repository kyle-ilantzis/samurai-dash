#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "Textures.h"
#include "Billboard.h"
#include "World.h"

class LoadingScreen {

public:
	static const float LOADING_MSG_DISTANCE;
	static const float LOADING_MSG_SIZE;
	static const glm::vec4 LOADING_MSG_BACKGROUND;

	LoadingScreen();
	~LoadingScreen();

	void Draw();

private:
	
	Texture2D mLoadingMsgTexture;
	BillboardList* mBillboardList;
	Billboard mLoadingMsgBillboard;

	WorldCameraType mOldWorldCameraType;
	glm::vec4 mOldClearColor;
};

#endif