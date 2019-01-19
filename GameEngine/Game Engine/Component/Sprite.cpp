/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Sprite.cpp>
Purpose:<implement all functions in class Sprite>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#include "Sprite.h"
#include"../ResourceManager.h"
extern ResourceManager* gpResourceManager;

Sprite::Sprite() : Component(SPRITE){

	sprite = nullptr;
	texture = nullptr;
	size = glm::vec2(0,0);
}

Sprite* Sprite::Clone(GameObject*_owner) {
	Sprite* a = new Sprite();
	a->mOwner = _owner;
	a->size = size;
	a->sprite = sprite;
	a->texture = texture;
	return a;
}

Sprite::~Sprite() {

	//sprite = nullptr;
}

void Sprite::Update() {  };


void  Sprite::Serialize(FILE **file) {
	char imageName[256];
	memset(imageName, 0, 256 * sizeof(char));
	std::string filep = "../Resource/";
	fscanf_s(*file,"%255s\n",imageName,sizeof(imageName));
	filep += imageName;
	sprite = gpResourceManager->LoadSurface((filep.c_str()));
}


void Sprite::Serialize(Json::Value value) {
	std::string filep = "../Resource/Image/";
	filep += value["name"].asString();
	size.x = value["width"].asInt();
	size.y = value["height"].asInt();
	//sprite = gpResourceManager->LoadSurface((filep.c_str()));
	texture = gpResourceManager->LoadTexture((filep.c_str()));
	if (size.x == 0)
	{
		size.x = texture->size.x;
		size.y = texture->size.y;
	}
}