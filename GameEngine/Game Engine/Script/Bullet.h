/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Bullet.h>
Purpose:<declared class Bullet, for behaviour of weapon 2>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#pragma once
#include "Script.h"
#include"../Component/Body.h"
#include"../Component/Controller.h"
#include"../GameObject.h"
#include"../FrameController.h"
#include <regex>
extern FrameController* gpFrameController;
class Bullet :public Script {
public:
	Bullet() :Script(BULLET) {}
	~Bullet() {}
	void OnCollision(GameObject* go) {
		if (std::regex_match(go->name, std::regex("enemy.*")))
		{
			go->isExist = false;
			mOwner->isShown = false;
		}
		else if (go->name != "player0")
		{
			mOwner->isShown = false;
		}
	

	}

	void Init() {
		mOwner->isShown = false;
		countTime = 0;
	}

	void Update() {
		if (!mOwner->isShown)
		{
			return;
		}
		if (countTime > 1.0f)
		{
			mOwner->isShown = false;
			return;
		}
		//static_cast<Body*>(mOwner->GetComponent(BODY))->mVelX = 500.0f;	
		countTime += gpFrameController->DeltaTime();
	}
public:
	float countTime;

};