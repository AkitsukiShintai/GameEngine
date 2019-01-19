/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Script.cpp>
Purpose:<implement functions in Script.h, for basic class  of all other scripts>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Script.h"
#include"../EventManager.h"
#include"../SceneManager.h"
extern SceneManager* gpSceneManager;

Script::Script(ScriptType t):mType(t) ,mOwner(nullptr){



}
Script::~Script(){


}

void Script::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == EVENT_COLLIDE)
	{
		CollisionEvent*p = static_cast<CollisionEvent*>(pEvent);
		
		OnCollision(p->target);		

	}
	else if (pEvent->mEventType == EVENT_SCENE_CHANGE)
	{
		SceneChangeEvent* p = static_cast<SceneChangeEvent*>(pEvent);
		gpSceneManager->LoadNewGameObject(p->scene,p->script);
	}

	
	return;
}

void Script::OnCollision(GameObject* go) {



}
void Script::Init() {


}

void Script::Update() {


}