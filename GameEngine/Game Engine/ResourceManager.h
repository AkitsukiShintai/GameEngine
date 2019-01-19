/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ResourceManager.h>
Purpose:<declare ResourceManager class, for load image>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#include"SDL_timer.h"
#ifndef RESOURCE_H
#define RESOURCE_H
#include"SDL.h"
#include <string>
#include<unordered_map>
#include"Render/Texture.h"


//unsigned char* loadBitmapFile(const char *fname, int *width, int *height);//
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface * LoadSurface(const char *filePath);
	Texture* LoadTexture(const char *filePath);
	
private:
	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
	std::unordered_map<std::string, Texture*> mTexture;
};
#endif // !RESOURCE_H