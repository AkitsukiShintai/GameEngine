/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Hell.h>
Purpose:<declared class Hell, for behaviour of hell>
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
#include <regex>
#include"../GameObject.h"
#include"../FrameController.h"
#include"../GameObjectManager.h"
#include"../SceneManager.h"
#include"../InputManager.h"
#include"SDL_scancode.h"
#include"../Component/Controller.h"
extern InputManager* gpInputManager;
extern SceneManager* gpSceneManager;
class Hell :public Script {

public:
	Hell() :Script(HELL) {
	}
	~Hell() {}
	void OnCollision(GameObject* go) {
		if (go->name == "player0")
		{
			gpSceneManager->LoadNewGameObject("game_over", "game_over");
			canControl = true;
			static_cast<Controller*>(go->GetComponent(CONTROLLER))->canControll = false;
		}
	}

	void Init() {

	}

	void Update() {
		if (canControl)
		{
			if (gpInputManager->IsTriggered(SDL_SCANCODE_R))
			{
				gpSceneManager->LoadScene("in_game_May", "in_game_May");
				canControl = false;
				//playerCon->canControll = true;
			}

			if (gpInputManager->IsTriggered(SDL_SCANCODE_RETURN))
			{
				gpSceneManager->LoadScene("start", "start");
				canControl = false;
				//playerCon->canControll = true;
			}
		}
	}

public:
	bool canControl = false;
	//Controller* playerCon;
};