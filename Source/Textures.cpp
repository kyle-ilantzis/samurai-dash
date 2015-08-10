#include "Textures.h"

Texture2D::Texture2D() : mTextureId() {
	
	glGenTextures(1, &mTextureId);

	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture2D::~Texture2D() {

	glDeleteTextures(1, &mTextureId);
}

void Texture2D::Bind(GLenum textureUnit) {
	
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void Texture2D::SetData(FreeImage& image) {

	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.GetWidth(), image.GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.GetData());
}

TextureCubemap::TextureCubemap() : mTextureId() {

	glGenTextures(1, &mTextureId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

TextureCubemap::~TextureCubemap() {

	glDeleteTextures(1, &mTextureId);
}

void TextureCubemap::Bind(GLenum textureUnit) {

	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
}

void TextureCubemap::SetData( GLenum cubemapEnum, FreeImage& image) {

	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
	glTexImage2D(cubemapEnum, 0, GL_RGBA8, image.GetWidth(), image.GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.GetData());
}



