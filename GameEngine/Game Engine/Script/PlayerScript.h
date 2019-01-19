/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<PlayerScript.h>
Purpose:<declared class PlayerScript, for behaviour of player>
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
#include<regex>
#include"../Render/Program.h"
extern Program* gpProgram;

class PlayerScript :public Script {

public:

	PlayerScript() :Script(PLAYER_SCRIPT) {

		//mType = PLAYER_SCRIPT;
	}

	void OnCollision(GameObject* go) {
	
		if (go->name == "enemy1")
		{
			//goBody->mPosX += 100;
		}

		else if (std::regex_match(go->name, std::regex("ground.*")))
		{
			Controller* mController = static_cast<Controller*>	(mOwner->GetComponent(CONTROLLER));
			mController->isJumping = false;
			 static_cast<Body*>	(mOwner->GetComponent(BODY))->mInvMass = 1.0f;
			//static_cast<Controller*>	(mOwner->GetComponent(CONTROLLER))->isJumping = false;

		}

		else	if (std::regex_match(go->name, std::regex("obstacle.*")))
		{
			Body* mBody = static_cast<Body*>	(mOwner->GetComponent(BODY));
			Controller* mController = static_cast<Controller*>	(mOwner->GetComponent(CONTROLLER));
			Body* goBody = static_cast<Body*>	(go->GetComponent(BODY));
			if (mBody->mPosX > goBody->mPosX)
			{
				mController->left = false;
			}
			else if (mBody->mPosX < goBody->mPosX)
			{
				mController->right = false;
			}
			
		}
	}

	void Init() {

		//gpEventManager->Subscribe(EVENT_COLLIDE, mOwner);
	}

	void Update() {
		Body* pBody = static_cast<Body*> (mOwner->GetComponent(BODY));
		if (pBody->mPosX < 100.0f)
		{
			gpProgram->eye.x = 100.0f;
		}
		else if (pBody->mPosX >4200.0f)
		{
			gpProgram->eye.x = 4200.0f;
		}
		else
		{
			gpProgram->eye.x = pBody->mPosX;
		}
	}

public:
};
