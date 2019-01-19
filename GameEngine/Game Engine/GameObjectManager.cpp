/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<GameObjectManager.cpp>
Purpose:<implement all functions of class GameObjectManager>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"GameObjectManager.h"
#include<vector>
#include<algorithm>
#include"GameObject.h"

typedef struct finder_t
{
	finder_t(std::string n) : _name(n) { };
	bool operator()(GameObject *p) { return (_name == p->name); }
	std::string _name;
};



GameObjectManager::GameObjectManager() {
	count = 0;
}
GameObjectManager::~GameObjectManager() {
	for (auto go : GameObjects)
	{
		delete go;
	}
	GameObjects.clear();
}
void GameObjectManager::Update() {
	for (auto i = GameObjects.begin(); i < GameObjects.end(); ++i)
	{
		if ((*i)->isExist == false)
		{
			for (auto j = GameObjectsRenderList.begin(); j != GameObjectsRenderList.end(); ++j)
			{
				if ((*j)->ID  == (*i)->ID)
				{
					GameObjectsRenderList.erase(j);
					break;
				}
			}
			(*i)->~GameObject();
			i = GameObjects.erase(i);
			//GameObjects.erase
		}
	}

}
void GameObjectManager::InsertInRenderList(GameObject* pG ) {

	

}

GameObject* GameObjectManager::FindeGameObjectByName(std::string name) {
	GameObject* go = nullptr;
	auto it = std::find_if(GameObjects.begin(), GameObjects.end(), finder_t(name));
	if (it!= GameObjects.end())
	{
		return *it;
	}
	return go;
}



void  GameObjectManager::ClearAll() {
	for (auto i = GameObjects.begin(); i != GameObjects.end(); i++)
	{
		delete (*i);
	}

	GameObjects.clear();
	GameObjectsRenderList.clear();
}