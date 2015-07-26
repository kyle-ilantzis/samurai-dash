//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"

class SphereModel : public Model
{
public:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	typedef void(*forEachVertex)(Vertex* vertexBuffer, int len);

	static const Vertex sVertexBuffer[];
	static const int sVertexBufferSize;

	SphereModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), forEachVertex fev = nullptr);
    virtual ~SphereModel(void);

	virtual void Update(float dt);
    virtual void Draw();
    
	int GetNumberOfVertices() { return mNumOfVertices; }

protected:
    virtual bool ParseLine(const std::vector<ci_string> &token);
private:
    unsigned int mVertexArrayID;
    unsigned int mVertexBufferID;
	unsigned int mNumOfVertices;
public:
};


