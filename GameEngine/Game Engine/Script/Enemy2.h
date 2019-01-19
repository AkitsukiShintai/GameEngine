/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Enemy2.h>
Purpose:<declared class Enemy2, for second kind of enemy>
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
class Enemy2 :public Script {

public:
	Enemy2() :Script(ENEMY_2) {  }
	~Enemy2() {}
	void OnCollision(GameObject* go) {
		if (go->name == "player0")
		{		
				Blood* bloo = static_cast<Blood*>(go->GetScript(BLOOD));
				bloo->DamageCome();
				//go->Destory();		
		}

		if (std::regex_match(go->name, std::regex("ground.*")))
		{
			isJumping = false;
			//go->Destory();		
		}
		if (std::regex_match(go->name, std::regex("obstacle.*")))
		{
			flag = -flag;
			
			if (flag>0)
			{
				
				mB->mPosX =
					static_cast<Transform*>(go->GetComponent(TRANSFORM))->mPos.x + static_cast<Sprite*>(go->GetComponent(SPRITE))->size.x / 2.0f + mS->size.x / 2.0f + 0.5f;
			}
			else
			{
				
				mB->mPosX =
					static_cast<Transform*>(go->GetComponent(TRANSFORM))->mPos.x - static_cast<Sprite*>(go->GetComponent(SPRITE))->size.x / 2.0f - mS->size.x / 2.0f - 0.5f;

			}
			if (flag > 0)
			{
				mB->mRotate.x = 0.0f;
			}
			else {
				mB->mRotate.x = 180.0f;
			}
		}
	}

	void Init() {
		player = gpGameObjectManager->FindeGameObjectByName("player0");
		mB = static_cast<Body*>(mOwner->GetComponent(BODY));
		mT = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM));
		goT = static_cast<Transform*>(player->GetComponent(TRANSFORM));
		mS = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));
		goS = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));
	}

	void Update() {
		float D = glm::distance(mT->mPos, goT->mPos);
		mB->mPosX += flag * vel * gpFrameController->DeltaTime();
	

		if (D < (mS->size.x+ goS->size.x)/2.0f + dis)
		{
			if (isJumping)
			{
				return;
			}
			mB->mVelY = 500.0f;
			mB->mInvMass = 1.0f;

			isJumping = true;
		}

		
		// =   delta;
	}
private:
	float dis = 200.0f;
	float x = 100.0f;
	float delta = 0.0f;
	float vel = 50.0f;
	bool isJumping = false;
	float flag = 1.0f;
	GameObject* player;
	Body* mB ;

	Transform* mT;// = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM));
	Transform* goT;// = static_cast<Transform*>(player->GetComponent(TRANSFORM));
	Sprite* mS;//= static_cast<Sprite*>(mOwner->GetComponent(SPRITE));
	Sprite* goS;// = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));
};