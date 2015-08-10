#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "Model.h"

class ObjectModel : public Model
{

public:
	ObjectModel(const char* objFile, const char* matFile, const glm::vec3 colorForShapeI[], bool isTextured = false);

		unsigned int mVertexArrayID;
		std::vector<unsigned int> shapesVertexBuffer;
		virtual void Draw();
		virtual void Update(float dt)
		{

		}
		virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	bool mIsTextured;
};



#endif