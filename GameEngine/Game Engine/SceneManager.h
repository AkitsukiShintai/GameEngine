/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<SceneManager.h>
Purpose:<declare functions of SceneManager class. For determining if need to load new scene or game objects>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include<string>
class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void Update();
	void LoadScene(std::string _sceneName, std::string _scriptsName);
	void LoadNewGameObject(std::string _sceneName, std::string _scriptsName);

private:
	enum LOAD_TYPE
	{
		SCENE,
		GAMEOBJECT,
		NOTHING
	};
	std::string sceneName;
	std::string scriptsName;
	bool loaded;
	LOAD_TYPE state;
};