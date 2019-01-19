/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<UpDown.h>
Purpose:<declare the class UpDown, a simple up-down AI>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"Component.h"
#include"../EventManager.h"
class Component;

class UpDown:public Component {
public:
	UpDown();
	~UpDown();
	void Update();
	void Serialize(FILE **file);
	void Serialize(Json::Value);
	void HandleEvent(Event* pEvent);
	UpDown* Clone(GameObject* _owners);
private:
	bool InitOrigionY;
	float speed;
	float dis;
	bool upFlag;
	float passedTime;
	float origionY;
};