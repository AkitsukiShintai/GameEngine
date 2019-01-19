/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<StartMenu.h>
Purpose:<declared class StartMenu, for logic of menu in the start scene>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Script.h"
#include"SDL_scancode.h"
#include<vector>
#include"../InputManager.h"
#include"../GameObjectManager.h"
#include<regex>
#include"../SceneManager.h"
extern InputManager* gpInputManager;
extern GameObjectManager* gpGameObjectManager;
extern SceneManager* gpSceneManager;

class StartMenu:public Script{
public:
	StartMenu() :Script(START_MENU),current(0), size(0){}
	~StartMenu() {}

	void OnCollision(GameObject* go) {
	
	
	}
	void HandleEvent(Event* pEvent) {
	
	
	}
	void Init() {
		for (size_t i = 0; i < gpGameObjectManager->GameObjects.size(); i++)
		{
			if (std::regex_match( gpGameObjectManager->GameObjects[i]->name,std::regex(".*UI")))
			{
				buttoms.push_back(gpGameObjectManager->GameObjects[i]);
			}
		}
		size = buttoms.size()-1;
		outline = gpGameObjectManager->FindeGameObjectByName("outline");
		current = 1;
		help = gpGameObjectManager->FindeGameObjectByName("help");
		isHelp = false;
		help->isShown = false;
	}

	void Update() {


		if (isHelp)
		{
			if (gpInputManager->IsTriggered(SDL_SCANCODE_RETURN)) {
			
				help->isShown = false;
				isHelp = false;
					
			}	
			return;
		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_UP))
		{
			current++;
			if (current > size)
			{
				current = size;
			}
		}
		if (gpInputManager->IsTriggered(SDL_SCANCODE_DOWN))
		{
			

			current--;
			if (current < 0)
			{
				current = 0;
			}
		}
		static_cast<Transform*>(outline->GetComponent(TRANSFORM))->mPos =
			static_cast<Transform*>(buttoms[current]->GetComponent(TRANSFORM))->mPos;
		if (gpInputManager->IsTriggered(SDL_SCANCODE_RETURN))
		{	

			if (current == 1)
			{
				gpSceneManager->LoadScene("in_game_May", "in_game_May");
			}
			else if (current == 0)
			{
				help->isShown = true;
				isHelp = true;
			}
		
		}
	}
public:
	std::vector<GameObject*> buttoms;
	int size;
	int current;
	GameObject* outline;
	GameObject* help;
	bool isHelp;
};