/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ElectricShield.h>
Purpose:<declared class ElectricShield, for behaviour of weapon 1>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include "Script.h"
#include"../Component/Body.h"
#include"../Component/Controller.h"
#include"../GameObject.h"
#include"../FrameController.h"
#include <regex>

class ElectricShield :public Script {
public:
	ElectricShield() :Script(ELECTRIC_SHIELD) {}
	~ElectricShield() {}
	void OnCollision(GameObject* go) {
		if (std::regex_match(go->name, std::regex("enemy.*")))
		{
			go->isExist = false;
		}
	}

	void Init() {
		mOwner->isShown = false;
	}

	void Update() {
		if (!mOwner->isShown)
		{
			usedEnerge -= recoverEnergeSpeed * gpFrameController->DeltaTime();
			if (usedEnerge<0.0f)
			{
				usedEnerge = 0.0f;
			}
			return;
		}

		if (usedEnerge > totalEnerge)
		{
			mOwner->isShown = false;
			return;
		}

		usedEnerge += usedSpeed* gpFrameController->DeltaTime();
		rotate += gpFrameController->DeltaTime()*speed;
		static_cast<Transform*>(mOwner->GetComponent(TRANSFORM))->mRotate.y = rotate;
		//rotate = 100;
	}
public:
	float totalEnerge = 100.0f;
	float rotate = 0;
	float speed = 1000.0f;
	float usedEnerge = 0;
	float recoverEnergeSpeed = 20.0f;
	float usedSpeed = 50.0f;
};