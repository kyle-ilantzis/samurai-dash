#include "Renderer.h"
#include "ObjectModel.h"
#include "tiny_obj_loader.h"
#include <vector>

using namespace std;
using namespace tinyobj;
using namespace glm;


ObjectModel::ObjectModel(const char* objFile, const char* matFile, const vec3 colorForShapeI[]) : Model(), shapesVertexBuffer()
{
	// Vector Array for Shape
	vector<shape_t> shapes;
	vector<material_t> materials;

	// Import the Sheep
	string name = LoadObj(shapes, materials, objFile, matFile);

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Adds elements of the sheep (Body, Iris, Eye)

	// Main loop for creating the sheep
	for (int index = 0; index < shapes.size(); ++index)
	{
		// Unsigned Integer for Vertex, Indices, Size and Color Vertex
		unsigned int v;
		unsigned int i;
		unsigned int s;
		unsigned int colorVertexBuffer;
		unsigned int n;

		// Vertex Buffer
		glGenBuffers(1, &v);
		glBindBuffer(GL_ARRAY_BUFFER, v);
		glBufferData(GL_ARRAY_BUFFER, shapes[index].mesh.positions.size() * sizeof(float), &shapes[index].mesh.positions[0], GL_STATIC_DRAW);

		// Normal Buffer
		if (shapes[index].mesh.normals.size() == 0)
		{
			glGenBuffers(1, &n);
			glBindBuffer(GL_ARRAY_BUFFER, n);
			glBufferData(GL_ARRAY_BUFFER, shapes[index].mesh.normals.size() * sizeof(float), 0, GL_STATIC_DRAW);
		}
		else
		{
			glGenBuffers(1, &n);
			glBindBuffer(GL_ARRAY_BUFFER, n);
			glBufferData(GL_ARRAY_BUFFER, shapes[index].mesh.normals.size() * sizeof(float), &shapes[index].mesh.normals[0], GL_STATIC_DRAW);
		}

		// Color Buffer
		vector<vec3> colors(shapes[index].mesh.positions.size() * sizeof(float), colorForShapeI[index]);
		glGenBuffers(1, &colorVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors.size(), &colors[0], GL_STATIC_DRAW);

		// Index Buffer
		glGenBuffers(1, &i);
		glBindBuffer(GL_ARRAY_BUFFER, i);
		glBufferData(GL_ARRAY_BUFFER, shapes[index].mesh.indices.size() * sizeof(int32), &shapes[index].mesh.indices[0], GL_STATIC_DRAW);

		s = shapes[index].mesh.indices.size() * sizeof(int32);

		shapesVertexBuffer.push_back(v);
		shapesVertexBuffer.push_back(i);
		shapesVertexBuffer.push_back(s);
		shapesVertexBuffer.push_back(colorVertexBuffer);
		shapesVertexBuffer.push_back(n);
	}
}

void ObjectModel::Draw()
{
	glBindVertexArray(mVertexArrayID);

	for (int index = 0; index < shapesVertexBuffer.size(); index += 5)
	{
		unsigned int vertex = shapesVertexBuffer[index];
		unsigned int indice = shapesVertexBuffer[index + 1];
		unsigned int size = shapesVertexBuffer[index + 2];
		unsigned int color = shapesVertexBuffer[index + 3];
		unsigned int normal = shapesVertexBuffer[index + 4];

		GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
		glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

		// First Attribute (Vertex Position)
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glVertexAttribPointer(0,				// attribute. No particular reason for 0, but must match the layout in the shader.
			3,				// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,	// stride
			(void*)0		// array buffer offset
			);

		// Third Attribute (Normal)
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normal);
		glVertexAttribPointer(1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0    // Normal is Offseted by vec3 (see class Vertex)
			);

		// Third Attribute (Color)
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, color);
		glVertexAttribPointer(2,				// attribute. No particular reason for 0, but must match the layout in the shader.
			3,				// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,	// stride
			(void*)0		// array buffer offset
			);

		// Bind the Buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice);

		// Draw the elements.
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		// Close the Buffers.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

bool ObjectModel::ParseLine(const std::vector<ci_string> &token)
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