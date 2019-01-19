/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Texture.h>
Purpose:<declared class Texture.h, for storaging openGL texture>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"glm.hpp"
#include"glew.h"
#include<string>
class Texture {
public:
	Texture();
	~Texture();

	glm::vec2 size;
	glm::vec2 originSize;
	//glm::vec2 mPos;//mostly is the game object position
	glm::vec2 texcoords[4];
	std::string renderer ;
	GLuint texture;

};