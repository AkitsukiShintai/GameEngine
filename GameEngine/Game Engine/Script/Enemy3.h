/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Enemy3.h>
Purpose:<declared class Enemy3, for third kind of enemy>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"../Component/Body.h"
#include"../Component/Controller.h"
#include"../GameObject.h"
#include"../FrameController.h"
#include"../GameObjectManager.h"
#include "../Script/Blood.h"
#include"../Component/Transform.h"
#include"glm.hpp"
#include<regex>
extern FrameController* gpFrameController;
extern GameObjectManager* gpGameObjectManager;
class Enemy3 :public Script {

public:
	Enemy3() :Script(ENEMY_3) {  }
	~Enemy3() {}
	void OnCollision(GameObject* go) {
		if (go->name == "player0")
		{
			Blood* bloo = static_cast<Blood*>(go->GetScript(BLOOD));
			bloo->DamageCome();
			//go->Destory();		
		}
	}

	void Init() {

	}

	void Update() {
		Body* mB = static_cast<Body*>(mOwner->GetComponent(BODY));
		Transform* mT = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM));		
		//Sprite* mS = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));
		if (passed < time)
		{
			mB->mVelY = speed * flag;
			passed += gpFrameController->DeltaTime();
			return;
		}
		flag = -flag;
		passed = 0;
	}
private:
	float time = 2.0f;
	float passed = 0.0f;
	float flag = 1.0f;
	float speed = 50.0f;
};