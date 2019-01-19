/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ResourceManager.cpp>
Purpose:<implement functions in ResourceManager.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/

#include"ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include"glew.h"
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;


bool LoadImage(const char* filePath, int * w, int * h, GLuint* texture) {
	unsigned char * image_data = nullptr;
	int c = -1;
	if (std::regex_match(filePath, std::regex("(.*)(.jpg)")) || std::regex_match(filePath, std::regex("(.*)(.bmp)"))) {

		image_data = stbi_load(filePath, w, h, &c, 3);
		if (c != 3 && image_data == nullptr)
		{
			printf("load image %s fail or com is not mach\n", filePath);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *w, *h, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			stbi_image_free(image_data);
			return true;
		}

		
	}
	else if (std::regex_match(filePath, std::regex("(.*)(.png)")))
	{
		image_data = stbi_load(filePath, w, h, &c, 4);
		if (c != 4 && image_data == nullptr)
		{
			printf("load image %s fail or com is not mach \n", filePath);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *w, *h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glPixelStoref(GL_PACK_ALIGNMENT, 1);
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
			stbi_image_free(image_data);
			return true;
		}
	
	}
	printf("image is not mach any form \n", filePath);
	return false;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto ele : mSurfaces)
	{
		SDL_FreeSurface(ele.second);
	}
}

SDL_Surface * ResourceManager::LoadSurface(const char *filePath) {

	SDL_Surface * pSurface = mSurfaces[filePath];
	if (pSurface)
	{
		return pSurface;
	}

	pSurface = SDL_LoadBMP(filePath);

	if (pSurface)
	{
		mSurfaces[filePath] = pSurface;
	}
	else
	{
		printf("Load img failed");
	}

	return pSurface;
}


Texture* ResourceManager::LoadTexture(const char *filePath) {

	Texture * pTexture = mTexture[filePath];
	if (pTexture)
	{
		return pTexture;
	}

	GLuint texture = -1;
	int w = 0, h = 0;

	//rgba
	 //load image

	bool b = LoadImage(filePath, &w, &h, &texture);

	Texture* tex = new Texture();
	tex->texture = texture;
	//tex->originSize = glm::vec2(w, h);
	tex->size = glm::vec2(w, h);
	tex->texcoords[0] = glm::vec2(0, 0);
	tex->texcoords[1] = glm::vec2(0, 1);
	tex->texcoords[2] = glm::vec2(1, 1);
	tex->texcoords[3] = glm::vec2(1, 0);

    mTexture[filePath] = tex;
	return tex;
	//return nullptr;
}


