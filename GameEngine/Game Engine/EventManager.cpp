/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<EventManager.cpp>
Purpose:<implement all functions of class EventManager>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"EventManager.h"
#include"GameObjectManager.h"
extern GameObjectManager *gpGameObjectManager;

Event::Event(EventType t) {
	mEventType = t;
	mTime = 0.0f;
}
Event::Event(EventType t, float time) {
	mEventType = t;
	mTime = time;
}
Event::~Event() {

}
EventManager::EventManager() {

}
EventManager::~EventManager() {
	for (auto e :mTimedEvent)
	{
		delete e;
	}

	mTimedEvent.clear();
}

void EventManager::BroadcastEvent(Event* pEvent) {
	for (auto go: gpGameObjectManager->GameObjects)
	{
		go->HandelEvent(pEvent);
	}
}


void EventManager::BroadcastToSubscribe(Event* pEvent) {

	auto &i = mSubscribeEvent[pEvent->mEventType];
	for (auto go : i)
	{
		go.second->HandelEvent(pEvent);
	}
	delete pEvent;
}

void EventManager::AddTimedEvent(Event* pEvent) {

	mTimedEvent.push_back(pEvent);

}


void EventManager::Update(float time) {

	std::list<Event*>::iterator it = mTimedEvent.begin();
	while (it != mTimedEvent.end())
	{
		Event* e = *it;
		e->mTime -= time;
		if (e->mTime < 0 || e->mTime == 0)
		{
			BroadcastToSubscribe(e);
			delete e;
			it = mTimedEvent.erase(it);
		}
		else
		{
			++it;
		}
	}
	
}
void EventManager::Subscribe(EventType type, GameObject* pGameObject) {

	auto &i = mSubscribeEvent[type];
	GameObject* go = i[pGameObject->ID];

	if (go != nullptr)
	{
		return;
	}

	i[pGameObject->ID]=pGameObject;
}

void EventManager::UnSubscribe(EventType type, GameObject* pGameObject) {

	auto &i = mSubscribeEvent[type];
	auto it = i[pGameObject-> ID];
	if (it != nullptr)
	{
		i.erase(pGameObject->ID);
	}
}