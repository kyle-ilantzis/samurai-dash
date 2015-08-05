#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glew.h>

#include "TextureLoader.h"

class Texture2D {

public:
	Texture2D();
	~Texture2D();

	void Bind(GLenum textureUnit);

	void SetData(FreeImage& image);

	GLuint GetTextureId() { return mTextureId; }

private:
	GLuint mTextureId;
};

class TextureCubemap {

public:
	TextureCubemap();
	~TextureCubemap();

	void Bind(GLenum textureUnit);

	void SetPosXData(FreeImage& image) { SetData(GL_TEXTURE_CUBE_MAP_POSITIVE_X, image); }
	void SetNegXData(FreeImage& image) { SetData(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, image); }
	void SetPosYData(FreeImage& image) { SetData(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, image); }
	void SetNegYData(FreeImage& image) { SetData(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, image); }
	void SetPosZData(FreeImage& image) { SetData(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, image); }
	void SetNegZData(FreeImage& image) { SetData(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, image); }

private:
	void SetData(GLenum cubemapEnum, FreeImage& image);

	GLuint mTextureId;
};

#endif