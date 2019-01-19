/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Number.h>
Purpose:<declare class Number as a component of game object>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Component.h"
#include<vector>

class Number : public Component {
public:
	Number();
	~Number();
	void Update();
	Number* Clone(GameObject*_owner);
	void Serialize(FILE **file);
	void Serialize(Json::Value);
	void HandleEvent(Event* pEvent);
	//void OnCollision(GameObject* pGameObject);
public:

	std::vector<GameObject*> numbers;
	int number;
private:

};