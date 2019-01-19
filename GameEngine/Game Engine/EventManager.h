/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<EventManager.h>
Purpose:<declare EventManager class. For broudcasting event for objects>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include<list>
#include<unordered_map>
enum EventType {
	EVENT_SCENE_CHANGE,
	EVENT_COLLIDE,
	EVENT_INPUT,
	EVENT_NUM
};


class Event {
public:
	Event::Event(EventType, float);
	Event(EventType);
	virtual~Event();

public:
	float mTime;
	EventType mEventType;
};
class GameObject;
class EventManager {

public:
	EventManager();
	~EventManager();
	void BroadcastEvent(Event* pEvent);
	void BroadcastToSubscribe(Event* pEvent);
	void AddTimedEvent(Event* pEvent);
	void Update(float time);
	void Subscribe(EventType type, GameObject* pGameObject);
	void UnSubscribe(EventType type, GameObject* pGameObject);
public:
	std::list<Event*> mTimedEvent;
	std::unordered_map<EventType, std::unordered_map<int, GameObject *>> mSubscribeEvent;
};


class CollisionEvent : public Event {
public:
	CollisionEvent(GameObject* go) :Event(EVENT_COLLIDE) , target(go) {};
	GameObject* target;
};


class InputEvent :public Event {
public:
	InputEvent() :Event(EVENT_INPUT) {};
};

class SceneChangeEvent : public Event {
public:
	SceneChangeEvent(std::string _scene, std::string  _script) :Event(EVENT_SCENE_CHANGE), scene(_scene), script(_script){};
public:
	std::string scene, script;
};
