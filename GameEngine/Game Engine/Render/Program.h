/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Program.h>
Purpose:<declared class Program.h, for rendering in each frame>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include<unordered_map>
//#include "SDL_opengl.h"
//#include "glm.hpp"
#include"Buffer.h"
#include"Renderer.h"
 
#define BUFFCOUNT 4
class Program {
public:
	Program(int,int);
	~Program(void);
	void draw();
	void resize(int W, int H);
	void Init();
public:	
	int w;
	int h;
	float fov;
	float aspect;
	float time;
	glm::vec3 eye;
	bool renderDebug;
	bool collisionDebug;
	bool showSprite;
	bool pause;
private:

	std::unordered_map<std::string ,Buffer*> mBuffer;//GL Buffer, including texture coord, vertex,normal, and face buffers
	std::unordered_map<std::string, Renderer*> mRenderer;//GL Program
};