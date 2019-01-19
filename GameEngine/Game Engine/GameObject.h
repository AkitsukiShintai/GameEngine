/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<GameObject.h>
Purpose:<declare GameObject class. For basic object attribute>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include "Component/Component.h"
#include<vector>
#include"value.h"
#include"EventManager.h"
#include"Script/Script.h"
//#include"Script/Script.h"
class Component;
class Script;

class GameObject {
public:
	GameObject() ;
	GameObject(std::string _name);
	~GameObject() ;
	void Update();
	//use for Component, not Script
	Component* AddComponent(unsigned int type);
	Component* AddComponent(std::string);
	Component* GetComponent(unsigned int type);
	Script* GetScript(ScriptType type);
	//use for Script, not Component
	Script* AddScript(ScriptType);
	Script* AddScript(std::string);
	void HandelEvent(Event* pEvent);
	void Destory();
	GameObject* Clone();

	
	/*template<typename T>
	T* GetComponent() {
		Component* component = nullptr;
		COMPONENT_TYPE t;
		if (typeid(Animation) == typeid(T))
		{
			t = ANIMATION;
		}
		else if (typeid(Body) == typeid(T))
		{
			t = BODY;
		}
		else if (typeid(Sprite) == typeid(T))
		{
			t = SPRITE;
		}
		else if(typeid(Transform) == typeid(T))
		{
			t = TRANSFORM;
		}
		else if (typeid(UpDown) == typeid(T))
		{
			t = UPDOWN;
		}

		for (size_t i = 0; i < mComponents.size();++i)
		{
			if (mComponents[i]->mType == t)
			{
				component = mComponents[i];
			}
		}

		return static_cast<T*> (component);
	
	}
*/
	void SetRenderOrder(int i);
public:
	std::vector<Component*> mComponents;
	std::vector<Script*> mScripts;
	std::string name;
	int renderLayer;
	bool isExist;
	bool isShown;

private:
	friend class EventManager;
	friend class GameObjectManager;
	int ID;
};


