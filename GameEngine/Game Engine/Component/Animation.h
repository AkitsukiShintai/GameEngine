/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Animation.h>
Purpose:<declare class Animation as a component of game object>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Component.h"
#include<unordered_map>

class Animation : public Component {
public:
	Animation();
	~Animation();
	void Update();
	Animation* Clone(GameObject*_owner);
	void Serialize(FILE **file);
	void Serialize(Json::Value);
	void HandleEvent(Event* pEvent);
	//void OnCollision(GameObject* pGameObject);
public:
	bool run;
	std::unordered_map<std::string, int> stateIndex;

private:
	float duringTime;
	float time;
	std::string imgType;
	int currentIndex;
	std::string currentState;
};