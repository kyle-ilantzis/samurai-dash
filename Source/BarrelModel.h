#ifndef BARRELMODEL_H
#define BARRELMODEL_H

#include "Model.h"
#include "ObjectModel.h"
#include "Textures.h"

class BarrelModel : public ObjectModel
{
public:
	static const glm::vec3 BARREL_SHAPE_COLORS[];
	BarrelModel();

	virtual void Draw();

private:
	Texture2D barrelTexture;

};
#endif