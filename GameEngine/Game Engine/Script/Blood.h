/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Blood.h>
Purpose:<declared class Blood, for calculating the blood of player>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include "Script.h"
#include <regex>
#include"../GameObject.h"
#include"../FrameController.h"
#include"../GameObjectManager.h"
#include"../EventManager.h"
#include"../Script/Script.h"
extern FrameController* gpFrameController;
extern GameObjectManager* gpGameObjectManager;
extern GameObjectManager* gpGameObjectManager;
extern EventManager* gpEventManager;


class Blood :public Script {

public:
	Blood() :Script(BLOOD) {
		blood++;
	}
	~Blood() {}
	void OnCollision(GameObject* go) {
		
	}

	void Init() {
		for (auto go:gpGameObjectManager->GameObjects)
		{
			if (std::regex_match(go->name,std::regex("blood.*")))
			{
				blood++;
			}
		}
	}

	void Update() {
		if (isUnableToDamage)
		{
			mOwner->isShown = !mOwner->isShown;
			countDown -= gpFrameController->DeltaTime();
			if (countDown < 0.0f)
			{
				countDown = 2.0f;
				isUnableToDamage = false;
				mOwner->isShown = true;
			}
		}

	}

	void DamageCome() {
		if (!isUnableToDamage)
		{
			isUnableToDamage = true;
			blood--;
			if (blood>0)
			{
				for (auto i = gpGameObjectManager->GameObjects.end() - 1; i >= gpGameObjectManager->GameObjects.begin(); --i)
				{
					if (std::regex_match((*i)->name, std::regex("blood.*")))
					{
						(*i)->Destory();
						return;
					}
				}
			}
			else
			{
				static_cast<Controller*>(mOwner->GetComponent(CONTROLLER))->canControll = false;

				mOwner->isShown = false;
				SceneChangeEvent* e = new SceneChangeEvent("game_over","game_over");
				gpEventManager->BroadcastEvent(e);
			}
		}
	}


private:
	bool isUnableToDamage = false;
	int blood = 0;
	float countDown = 2.0f;
};