//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <FreeImageIO.h>

class FreeImage {

public:
	FreeImage(const char* imagePath);
	~FreeImage();

	int GetWidth() { return FreeImage_GetWidth(mImage32); }
	int GetHeight() { return FreeImage_GetHeight(mImage32); }
	
	void* GetData() { return (void*) FreeImage_GetBits(mImage32); }

private:
	FIBITMAP* mImage;
	FIBITMAP* mImage32;
};

// Simple Texture Loader Class
class TextureLoader
{
public:
	static int LoadTexture(const char * imagePath);
	static int LoadDDS(const char * path);

private:
    
};

#endif
