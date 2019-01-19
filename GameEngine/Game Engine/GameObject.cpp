/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<GameObject.cpp>
Purpose:<implement all functions of class GameObject>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"GameObject.h"
#include"GameObjectManager.h"
#include"Component/Sprite.h"
#include"Component/Transform.h"
#include"Component/Animation.h"
#include"Component/Body.h"
#include"Component/Controller.h"
#include"Component/Component.h"
#include"Component/UpDown.h"
#include"ComponentMap.h"
#include"Script/ScriptList.hpp"
#include"Component/Number.h"
#include"Component/UI.h"
#include<vector>
#include"EventManager.h"
//#include<algorithm>

extern GameObjectManager* gpGameObjectManager;
extern ComponentMap* gpComponentMap;

GameObject::GameObject() {
	gpGameObjectManager->GameObjects.push_back(this);
	name = "newGameobject";
	renderLayer = 0;
	ID = gpGameObjectManager->count;
	++gpGameObjectManager->count;
	isExist = true;
	isShown = true;
}

GameObject::GameObject(std::string _name) {
	gpGameObjectManager->GameObjects.push_back(this);
	name = _name;
	renderLayer = 0;
	ID = gpGameObjectManager->count;
	++gpGameObjectManager->count;
	isExist = true;
	isShown = true;
}


GameObject::~GameObject() {
	for (auto go : mComponents) {
		delete go;
	}
	for (auto script : mScripts) {
		delete script;
	}
	mComponents.clear();

}

void GameObject::Update() {
	for (auto s : mScripts) {
		s->Update();
	}
	for (auto go : mComponents) {
		go->Update();
	}
}

Component* GameObject::AddComponent(unsigned int type) {
	for (auto c : mComponents)
	{
		if (c->GetType() == type)
		{
			return c;
		}
	}

	Component* newComponent;
	switch (type)
	{
	case UPDOWN:
		newComponent = new UpDown();
		break;
	case CONTROLLER:
		newComponent =  new Controller();
		break;
	case SPRITE:
		newComponent = new Sprite();
		break;
	case TRANSFORM:
		newComponent = new Transform();
		break;
	case BODY:
		newComponent = new Body();
		break;
	case ANIMATION:
		newComponent = new Animation();
		break;
	case UI:
		newComponent = new UserInterface();
		break;
	case NUMBER:
		newComponent = new Number();
		break;
	/*case SCRIPT:
		newComponent = AddScript();
		break;*/
	}

	mComponents.push_back(newComponent);
	newComponent->mOwner = this;
	return newComponent;
}


Component* GameObject::AddComponent(std::string componentName) {
	if (gpComponentMap->ComponentTypeMap.size() == 9)
	{
		printf("");
	}
	unsigned int type = gpComponentMap->ComponentTypeMap[componentName];
	return AddComponent(type);
}


Component* GameObject::GetComponent(unsigned int type){

	for (auto c : mComponents)
	{
		if (c->GetType() == type)
		{
			return c;
		}
	}
	return nullptr;

}

Script* GameObject::GetScript(ScriptType type) {

	for (auto c : mScripts)
	{
		if (c->mType == type)
		{
			return c;
		}
	}
	return nullptr;

}



Script*  GameObject::AddScript(ScriptType t) {
	Script* pScript = nullptr;
	switch (t)
	{
	case PLAYER_SCRIPT:
		pScript = new PlayerScript();
		break;
	case GROUND:
		pScript = new Ground();
		break;
	case WALL:
		pScript = new Wall();
		break;
	case ENEMY_1:
		pScript = new Enemy1();
		break;
	case BULLET:
		pScript = new Bullet();
		break;
	case ELECTRIC_SHIELD:
		pScript = new ElectricShield();
		break;
	case BLOOD:
		pScript = new Blood();
		break;
	case HELL:
		pScript = new Hell();
		break;
	case START_MENU:
		pScript = new StartMenu();
		break;
	case ENEMY_2:
		pScript = new Enemy2();
		break;
	case ENEMY_3:
		pScript = new Enemy3();
		break;
	case GAME_OVER:
		pScript = new GameOver();
		break;
	default:
		break;
	}

	mScripts.push_back(pScript);
	if (pScript == nullptr)
	{
		printf("Loading script fail, Scrip Type:  %d",t );
		return pScript;
	}
	pScript->mOwner = this;
	return pScript;
}

Script* GameObject::AddScript(std::string scriptName) {
	ScriptType type = gpComponentMap->ScriptTypeMap[scriptName];
	return AddScript(type);
}


void GameObject::HandelEvent(Event* pEvent) {

	for (auto c: mComponents)
	{
		c->HandleEvent(pEvent);
	}

	for (auto c : mScripts)
	{
		c->HandleEvent(pEvent);
	}
}
void GameObject::Destory() {
	isExist = false;
}
GameObject* GameObject::Clone() {
	GameObject* newGo = new GameObject();

	for (size_t i = 0; i < this->mComponents.size(); i++)
	{
		Component* c =  this->mComponents[i]->Clone(newGo);
		newGo->mComponents.push_back(c);
	}
	for (size_t i = 0; i < this->mScripts.size(); i++)
	{
		Script* t = newGo->AddScript(this->mScripts[i]->mType);
		t->Init();

	}

	
	newGo->name = name;
	newGo->renderLayer = this->renderLayer;
	newGo ->isExist = this->isExist;
	newGo->isShown = this->isShown;

	auto t = std::find(gpGameObjectManager->GameObjectsRenderList.begin(), gpGameObjectManager->GameObjectsRenderList.end(), this);
	if (t!= gpGameObjectManager->GameObjectsRenderList.end())
	{
		gpGameObjectManager->GameObjectsRenderList.insert(t,newGo);
	}

	return newGo;
}


void GameObject::SetRenderOrder(int i) {

	renderLayer = i;


	//for (auto go : gpGameObjectManager->GameObjectsRenderList)
	//{
	//	if (go->renderLayer>i)
	//	{
	//		continue;
	//	}
	//}
	gpGameObjectManager->GameObjectsRenderList.push_back(this);


}