/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Component.h>
Purpose:<declare the basic class Component for all component>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
//#include "../Game Engine/GameObject.h"
#include<iostream>
#include"json.h"
#include"../GameObject.h"
//#include"../EventManager.h"
class GameObject;
class Event;
enum COMPONENT_TYPE {
	NUMBER,
	UI,
	ANIMATION,
	BODY,
	UPDOWN,
	SPRITE,
	TRANSFORM,
	CONTROLLER ,
	MAX_COUNT
};

class Component {
public:
	Component(unsigned int type);
	virtual ~Component();
	virtual void Update();
	unsigned int GetType();
	GameObject* mOwner;
	virtual void Serialize(FILE **file);
	virtual void Serialize( Json::Value);
	virtual	void HandleEvent(Event* pEvent);
    virtual	void OnCollision(GameObject* pGameObject);
	virtual	Component* Clone(GameObject* _owner)=0;
private:
	unsigned int mType;

};
	
