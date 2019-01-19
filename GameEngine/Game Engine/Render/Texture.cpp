/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Texture.cpp>
Purpose:<implement all functions declared in Texture.h, storage openGL texture>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Texture.h"
#include"../ResourceManager.h"

Texture::Texture() {
	renderer = "defult";
}


Texture::~Texture() {

	glDeleteTextures(1,&texture);

}

