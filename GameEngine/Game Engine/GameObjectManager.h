/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<GameObjectManager.h>
Purpose:<declare GameObjectManager class. For managing objects and determining the render sort>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include<vector>
#include<list>
#include"GameObject.h"
class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();
	void InsertInRenderList(GameObject*);
	GameObject* FindeGameObjectByName(std::string);
	void ClearAll();
	void Update();
public:
	int count;
	std::vector<GameObject*> GameObjects;
	std::list<GameObject*> GameObjectsRenderList;
};