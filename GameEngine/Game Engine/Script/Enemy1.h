/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Enemy1.h>
Purpose:<declared class Enemy1, for first kind of enemy>
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
#include<regex>
extern FrameController* gpFrameController;
extern GameObjectManager* gpGameObjectManager;
class Enemy1 :public Script {

public:
	Enemy1() :Script(ENEMY_1) {}
	~Enemy1() {}
	void OnCollision(GameObject* go) {
		if (go->name == "player0")
		{
			if (static_cast<Transform*>(go->GetComponent(TRANSFORM))->mPos.y > static_cast<Transform*>(mOwner->GetComponent(TRANSFORM))->mPos.y+25) {
				mOwner->Destory();
			}
			else
			{
				Blood* bloo = static_cast<Blood*>(go->GetScript(BLOOD));
				bloo->DamageCome();
				//go->Destory();
			}
		}
		if (std::regex_match(go->name,std::regex( "player0")))
		{
			mT->mInvMass = 0.0f;
		}


	}

	void Init() {
		origX = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM))->mPos.x;
		mT = static_cast<Body*>(mOwner->GetComponent(BODY));
	}

	void Update() {

		//Body* mT = static_cast<Body*>(mOwner->GetComponent(BODY));
		if (abs(delta)>x)
		{
			delta = 0;
			flag = -flag;
			origX = mT->mPosX;
		}
		delta+= flag * vel * gpFrameController->DeltaTime();
		mT->mPosX = origX+delta;
		
	}
private:
	float origX = 0.0f;
	float x = 50.0f;
	float delta = 0.0f;
	float vel = 100.0f;
	float flag = -1.0f;
	Body* mT;
};