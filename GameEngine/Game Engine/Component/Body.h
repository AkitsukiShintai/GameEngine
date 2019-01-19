/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Body.h>
Purpose:<declare class Body as a component of game object>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Component.h"
#include"Shape.h"
#include"glm.hpp"
class Shape;
class Body :public Component{
public:
	Body();
	Body* Clone(GameObject*_owner);
	~Body();
	 void Update();

	 void Serialize(FILE **file);
	 void Serialize(Json::Value);

	 void Init();

	 void Intergrate(float gravity, float framtime);

public:
	float mPosX, mPosY;
	float mPreviousX, mPreviousY;
	float mVelX, mVelY;
	float mAccX, mAccY;
	float mTotalForceX, mTotalForceY;
	float mMass, mInvMass;
	glm::vec2 mRotate;
	Shape* mpShape;
};