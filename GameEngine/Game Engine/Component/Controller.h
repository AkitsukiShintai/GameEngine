/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Controller.h>
Purpose:<declare the class Controller, can use up down left right buttons to control the object>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Component.h"
class PlayerScript;
class Controller:public Component {
public:
	enum DIR {
		DIR_RIGHT,
		DIR_LEFT,
		DIR_JUMP
	};


public:
	Controller();
	~Controller();
	Controller* Clone(GameObject* _owners);
	void Update();
	void Serialize(FILE **file);
	void Serialize(Json::Value);
public:
	//friend PlayerScript;
	bool isJumping;
	bool left;
	bool right;
	DIR currentState;
	float speed;
	bool canControll;
	bool pauseFlag;
};