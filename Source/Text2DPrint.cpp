#include "Text2DPrint.h"
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include <glm/gtx/transform.hpp>

using namespace glm;
using namespace std;

unsigned int Text2DTextureID;
unsigned int Text2DVertexBufferID;
unsigned int Text2DUVBufferID;
unsigned int Text2DShaderID;
unsigned int Text2DUniformID;

void initText(int texture)
{
	// Initialize VBO
	Text2DTextureID = texture;
	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);

	// Initialize Shader
	Text2DShaderID = Renderer::LoadShaders("../Assets/Shaders/TextVertexShader.vertexshader", "../Assets/Shaders/TextVertexShader.fragmentshader");

	// Initialize uniforms' IDs
	Text2DUniformID = glGetUniformLocation(Text2DShaderID, "myTextureSampler");
}

void DrawTime(const char* text, int tSize, int xPosition, int yPosition){

	vector<vec2> vertexes;
	vector<vec2> uvs;

	unsigned int len = strlen(text);

	for (int i = 0; i < len; i++){

		//First Triangle
		vec2 topLeft = vec2(xPosition+i*tSize,yPosition + tSize);
		vec2 topRight = vec2(xPosition + i*tSize + tSize, yPosition + tSize);
		vec2 bottomLeft = vec2(xPosition + i*tSize, yPosition);
		vec2 bottomRight = vec2(xPosition + i*tSize + tSize, yPosition);
		

		//Second Triangle
		//vec2 topRight2 = vec2(xPosition + i*tSize + tSize, yPosition + tSize);
		
	//	vec2 bottomLeft2 = vec2(xPosition + i*tSize, yPosition);

		vertexes.push_back(topLeft);
		vertexes.push_back(bottomLeft);
		vertexes.push_back(topRight);

		vertexes.push_back(bottomRight);
		vertexes.push_back(topRight);
		vertexes.push_back(bottomLeft);

		char letter = text[i];
		float uvx = (letter % 16) / 16.0f;
		float uvy = (letter / 16) / 16.0f;

		vec2 uvTopLeft = vec2(uvx,uvy);
		vec2 uvTopRight = vec2(uvx + 1.0f / 16.0f, uvy);
	//	vec2 uvTopRight2 = vec2(uvx + 1.0f / 16.0f, uvy);

		vec2 uvBottomLeft = vec2(uvx, uvy + 1.0f / 16.0f);
		vec2 uvBottomRight = vec2(uvx + 1.0f / 16.0f, uvy + 1.0f / 16.0f);
		//vec2 uvBottomLeft2 = vec2(uvx, uvy + 1.0f / 16.0f);
		
		uvs.push_back(uvTopLeft);
		uvs.push_back(uvBottomLeft);
		uvs.push_back(uvTopRight);

		uvs.push_back(uvBottomRight);
		uvs.push_back(uvTopRight);
		uvs.push_back(uvBottomLeft);

	}

	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec2), &vertexes[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	// Bind shader
	glUseProgram(Text2DShaderID);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(Text2DUniformID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertexes.size());

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void cleanupText(){
	// Delete buffers
	glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);

	// Delete texture
	glDeleteTextures(1, &Text2DTextureID);

	// Delete shader
	glDeleteProgram(Text2DShaderID);
}
