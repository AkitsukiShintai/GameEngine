/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<SceneManager.cpp>
Purpose:<implement all functions of class SceneManager>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"SceneManager.h"
#include"GameObjectManager.h"
#include"ObjectFactory.h"
#include"Render/Program.h"
#include"PhysicsManager.h"
extern GameObjectManager* gpGameObjectManager;
extern ObjectFactory* gpObjectFactory;
extern Program* gpProgram;
extern PhysicsManager* gpPhysicsManager;
SceneManager::SceneManager() {
	
	sceneName = "in_game_May";
	scriptsName = "in_game_May";
	sceneName = "start";
	scriptsName = "start";
	loaded = false;
	state = SCENE;
}
SceneManager::~SceneManager() {

}


void SceneManager::Update() {
	if (!loaded)
	{
		if (state == GAMEOBJECT)
		{
			if (sceneName != "")
			{
				gpObjectFactory->LoadLevelFromJson(sceneName.c_str());
				
			}
			if (scriptsName != "")
			{
				gpObjectFactory->LoadScript(scriptsName.c_str());
			}
			loaded = true;
			state = NOTHING;
		}
		else if (state == SCENE)
		{
			gpGameObjectManager->ClearAll();
			if (sceneName != "")
			{
				gpObjectFactory->LoadLevelFromJson(sceneName.c_str());
			}
			if (scriptsName != "")
			{
				gpObjectFactory->LoadScript(scriptsName.c_str());
			}
			gpProgram->eye = glm::vec4(0);
			state = NOTHING;
		}
		
	}



}
void SceneManager::LoadScene(std::string _sceneName, std::string _scriptsName) {
	scriptsName = _scriptsName;
	sceneName = _sceneName;
	loaded = false;
	state = SCENE;
}


void SceneManager::LoadNewGameObject(std::string _sceneName, std::string _scriptsName) {
	scriptsName = _scriptsName;
	sceneName = _sceneName;
	loaded = false;
	state = GAMEOBJECT;

}
