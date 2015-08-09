#ifndef SKYBOXMODEL_H
#define SKYBOXMODEL_H

#include "CubeModel.h"
#include "Textures.h"
#include "AssetsDir.h"

//#define SKYBOXMODEL_SKYBOX SKYBOX_NIGHTSKY
#define SKYBOXMODEL_SKYBOX SKYBOX_BLUESKY
//#define SKYBOXMODEL_SKYBOX SKYBOX_DUNES
#define SKYBOXMODEL_SKYBOX_RIGHT SKYBOXMODEL_SKYBOX "/right.jpg"
#define SKYBOXMODEL_SKYBOX_LEFT SKYBOXMODEL_SKYBOX "/left.jpg"
#define SKYBOXMODEL_SKYBOX_TOP SKYBOXMODEL_SKYBOX "/top.jpg"
#define SKYBOXMODEL_SKYBOX_BOTTOM SKYBOXMODEL_SKYBOX "/bottom.jpg"
#define SKYBOXMODEL_SKYBOX_FRONT SKYBOXMODEL_SKYBOX "/front.jpg"
#define SKYBOXMODEL_SKYBOX_BACK SKYBOXMODEL_SKYBOX "/back.jpg"

class SkyboxModel : public CubeModel {

public:

	SkyboxModel();

	virtual void Update(float dt);

	virtual void Draw();

private:
	TextureCubemap mCubemap;
};

#endif