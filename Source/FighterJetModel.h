#ifndef FIGHTERJETMODEL_H
#define FIGHTERJETMODEL_H

#include "Model.h"
#include "ObjectModel.h"

// Define Colors For Enemeny Jet
#define JET_COLOR glm::vec3(0, 0, 0)
#define JET_COLOR2 glm::vec3(1, 0, 0)

class FighterJetModel : public ObjectModel
{
public:
	static const glm::vec3 FIGHTER_JET_SHAPED_COLORS[];
	FighterJetModel();
};
#endif