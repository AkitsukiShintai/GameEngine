/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<GameOver.h>
Purpose:<declared class GameOver, for logic of game over>
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
#include"../SceneManager.h"
#include"../InputManager.h"
#include <regex>
#include"SDL_scancode.h"
extern InputManager* gpInputManager;
extern SceneManager* gpSceneManager;
class GameOver :public Script {
public:
	GameOver() :Script(GAME_OVER) {}
	~GameOver() {}
	void OnCollision(GameObject* go) {
		
		 if (go->name == "player0")
		{
			 gpSceneManager->LoadNewGameObject("win", "");
			 canControl = true;
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
			}

			if (gpInputManager->IsTriggered(SDL_SCANCODE_RETURN))
			{
				gpSceneManager->LoadScene("start", "start");
				canControl = false;
			}
		}
	}
public:
private:
	bool canControl = true;
};