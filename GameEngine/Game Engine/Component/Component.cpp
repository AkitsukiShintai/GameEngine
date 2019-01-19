/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Component.cpp>
Purpose:<implement all functions in class component>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#include"Component.h"
//#include"../GameObject.h"
#include"../EventManager.h"
Component::Component(unsigned int type){

	//mID = typeid(Component);
	mType = type;
	mOwner = nullptr;
}

Component::~Component() {
		
}


void Component::Update() {

}
 void Component::Serialize(FILE **file) {

}

 void Component::Serialize( Json::Value value) {

 }
unsigned int Component::GetType() {

	return mType;
}

void Component::OnCollision(GameObject* pGameObject) {



}

void Component::HandleEvent(Event* pEvent) {

	return;

}
//virtual void Component::Serialize() {}