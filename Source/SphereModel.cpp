//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "SphereModel.h"
#include "Renderer.h"

#include <algorithm>

using namespace glm;
using namespace std;

SphereModel::SphereModel(vec3 size, GLenum drawMode, forEachVertex fev) : Model()
{
	Vertex* vertexBuffer = new Vertex[sVertexBufferSize];
	copy(sVertexBuffer, sVertexBuffer + sVertexBufferSize, vertexBuffer);
	
	if (fev) {
		fev(vertexBuffer, sVertexBufferSize);
	}

	mNumOfVertices = sVertexBufferSize;

    glGenVertexArrays(1, &mVertexArrayID);
    glGenBuffers(1, &mVertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sVertexBufferSize * sizeof(Vertex), vertexBuffer, GL_STATIC_DRAW);

	mDrawMode = drawMode;

	delete vertexBuffer;
}

SphereModel::~SphereModel()
{
    glDeleteBuffers(1, &mVertexBufferID);
    glDeleteVertexArrays(1, &mVertexArrayID);
}


void SphereModel::Update(float dt)
{
    Model::Update(dt);
}

void SphereModel::Draw()
{
    // Draw the Vertex Buffer
    // Note this draws a unit Cube
    // The Model View Projection transforms are computed in the Vertex Shader
    glBindVertexArray(mVertexArrayID);

    GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
    
    // 1st attribute buffer : vertex Positions
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glVertexAttribPointer(  0,              // attribute. No particular reason for 0, but must match the layout in the shader.
                            3,              // size
                            GL_FLOAT,       // type
                            GL_FALSE,       // normalized?
                            sizeof(Vertex), // stride
                            (void*)0        // array buffer offset
                        );

    // 2nd attribute buffer : vertex normal
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glVertexAttribPointer(  1,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(Vertex),
                            (void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
                        );


    // 3rd attribute buffer : vertex color
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glVertexAttribPointer(  2,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(Vertex),
                            (void*) (2* sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
                        );

    // Draw the triangles !
	glDrawArrays(mDrawMode, 0, mNumOfVertices);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

bool SphereModel::ParseLine(const std::vector<ci_string> &token)
{
    if (token.empty())
    {
        return true;
    }
    else
    {
        return Model::ParseLine(token);
    }
}
