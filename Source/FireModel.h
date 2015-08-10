#pragma once

#include "Model.h"

using namespace glm;

class FireModel: public Model
{
public:
	FireModel();
	
	virtual void Draw();
	virtual bool ParseLine(const std::vector<ci_string> &token);
	virtual void Update(float dt);
};

