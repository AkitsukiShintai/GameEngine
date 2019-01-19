/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Ground.h>
Purpose:<declared class Ground, for behaviour of grounds>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Script.h"
#include"../Component/Body.h"
#include"../Component/Sprite.h"
#include"../GameObject.h"
#include <regex>
#include"../GameObjectManager.h"
extern GameObjectManager* gpGameObjectManager;
class Ground :public Script
{
public:
	Ground() : Script(GROUND) {



	}
	~Ground() {



	}
	void OnCollision(GameObject* go) {
	
		Body* goBody = static_cast<Body*>	(go->GetComponent(BODY));

		if (!std::regex_match(go->name, std::regex("ground.*")) && !std::regex_match(go->name, std::regex("obstacle.*")) && !std::regex_match(go->name, std::regex("wall.*")) && !std::regex_match(go->name, std::regex("hell.*")) && !std::regex_match(go->name, std::regex("home.*")))
		{
			if (std::regex_match(go->name, std::regex("flower.*")))
			{
				return;
			}
			//static_cast<Body*>	(go->GetComponent(BODY))->mTotalForceY = 10.0f;
			goBody->mVelY = 0.0f;
			//static_cast<Body*>	(go->GetComponent(BODY))->mMass = 0.0f;
			//goBody->mPosY = static_cast<Sprite*> (mOwner->GetComponent(SPRITE))->size.y / 2.0f + static_cast<Transform*> (mOwner->GetComponent(TRANSFORM))->mPos.x + static_cast<Sprite*> (go->GetComponent(SPRITE))->size.y / 2.0f ;
			//goBody->mInvMass = 0;
			Sprite* mySprite = static_cast<Sprite*> (mOwner->GetComponent(SPRITE));
			if (mySprite!=nullptr)
			{
				goBody->mPosY = mySprite->size.y / 2.0f + static_cast<Transform*> (mOwner->GetComponent(TRANSFORM))->mPos.y + static_cast<Sprite*> (go->GetComponent(SPRITE))->size.y / 2.0f;

			}
			else
			{
				goBody->mPosY = 1.0f + static_cast<Transform*> (mOwner->GetComponent(TRANSFORM))->mPos.y + static_cast<Sprite*> (go->GetComponent(SPRITE))->size.y / 2.0f;

			}
			
			return;
		}
		if (std::regex_match(go->name, std::regex("obstacle.*")) && mOwner->name == "ground")
		{
			if (flagOb)
			{
				return;
			}
			goBody->mVelY = 0.0f;
			goBody->mPosY = static_cast<Sprite*> (mOwner->GetComponent(SPRITE))->size.y / 2.0f + static_cast<Transform*> (mOwner->GetComponent(TRANSFORM))->mPos.y + static_cast<Sprite*> (go->GetComponent(SPRITE))->size.y / 2.0f;
			flagOb = true;
			return;
		}
		
		//gpEventManager->UnSubscribe(EVENT_COLLIDE,go);
	}

	void Init() {

		//gpEventManager->Subscribe(EVENT_COLLIDE, mOwner);
		if (mOwner->name != "ground")
			return;
		//GameObject* go = gpGameObjectManager->FindeGameObjectByName("ground");
		Transform* tt = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM));
		for (int i = 1; i < 100; ++i)
		{
			if (i ==21+7 || i == 22+7 || i == 47 + 7 || i == 49 + 7 || i == 50 + 7 || i == 52 + 7 || i == 64 + 7 || i == 66 + 7 || i == 68 + 7)
			{
				continue;
			}
			GameObject* newGo = mOwner->Clone();
			Transform* newGoT = static_cast<Transform*>(newGo->GetComponent(TRANSFORM));
			newGoT ->mPos.x = tt->mPos.x + 50.0f*(float)i;
			//newGoT->mPos.x = 0.0f;
		}


	}

private:
	bool flagOb = false;
};

