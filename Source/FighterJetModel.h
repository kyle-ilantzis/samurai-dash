#ifndef FIGHTERJETMODEL_H
#define FIGHTERJETMODEL_H

#include "Model.h"
#include "ObjectModel.h"

// Define Colors For Enemeny Jet
#define JET_COLORe glm::vec3(0, 0, 0)
#define JET_COLORe2 glm::vec3(1, 0, 0)

class FighterJetModel : public ObjectModel
{
public:
	static const glm::vec3 FIGHTER_JET_SHAPED_COLORS[];
	FighterJetModel();
	virtual void Update(float dt);
	virtual glm::mat4 GetWorldMatrix() const;
};
#endif