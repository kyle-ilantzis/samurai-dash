#ifndef BUNNYMODEL_H
#define BUNNYMODEL_H

#include "Model.h"
#include "ObjectModel.h"

class BunnyModel : public ObjectModel
{
public:
	static const glm::vec3 BUNNY_SHAPE_COLORS[];
	BunnyModel();
};
#endif