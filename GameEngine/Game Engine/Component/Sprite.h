/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Sprite.h>
Purpose:<declare the class Sprite, define what the sprite should the object show>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include <SDL_surface.h>
#include "Component.h"
#include"../Render/Texture.h"
class Sprite :public Component {
public:
	Sprite();
	~Sprite();
	void Update();
	void Serialize(FILE **file);
	void Serialize(Json::Value);
	Sprite* Clone(GameObject*_owner);
public:
	glm::vec2 size;
	SDL_Surface* sprite;
	Texture* texture;
};