/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Transform.h>
Purpose:<declare the class Transform, define the position of the object>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Component.h"
#include"glm.hpp"
class Transform:public Component {
public:
	Transform();
	~Transform();
	void Update();
	Transform* Clone(GameObject* _owner);
	void Serialize(FILE **file);
	void Serialize(Json::Value);
public:
	/*float posX;
	float posY;*/
	glm::vec2 mPos;
	glm::vec2 mRotate;
	glm::vec2 mScale;
};