#ifndef UFOMODEL_H
#define UFOMODEL_H

#include "Model.h"
#include "ObjectModel.h"

class UFOModel : public ObjectModel
{
public:
	static const glm::vec3 UFO_SHAPE_COLORS[];
	UFOModel();
};

#endif