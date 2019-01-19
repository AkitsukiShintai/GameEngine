/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ObjectFactory.h>
Purpose:<declare ObjectFactory class, use this to initialize scene and create objects from json files>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#pragma once

#include"Component/component.h"
#include"json.h"
class ObjectFactory {
public:
	GameObject* LoadGameObject(std::string, Json::Value attributes);
	GameObject* LoadGameObject(const char* filePath);
	void LoadLevelFromJson(const char* filePath);
	void LoadLevelFromTxt(const char* filePath);
	void LoadScript(const char* filePath);
	ObjectFactory();
public:
};