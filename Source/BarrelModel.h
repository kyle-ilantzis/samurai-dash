#ifndef BARRELMODEL_H
#define BARRELMODEL_H

#include "ObjectModel.h"

class BarrelModel : public ObjectModel
{
public:
	static const glm::vec3 BARREL_SHAPE_COLORS[];
	BarrelModel();

	virtual void Draw();

private:

};
#endif