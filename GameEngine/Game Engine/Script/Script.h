/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Script.h>
Purpose:<declare class Script, for basic class  of all other scripts>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
class Event;
class GameObject;
class EventManager;
extern EventManager* gpEventManager;


enum ScriptType {
	GAME_OVER,
	ENEMY_3,
	ENEMY_2,
	START_MENU,
	HELL,
	BLOOD,
	ELECTRIC_SHIELD,
	BULLET,
	ENEMY_1,
	WALL,
	GROUND,
	PLAYER_SCRIPT,
	SCRITP_NUM

};

class Script {
public:
	Script(ScriptType);
	~Script();
	virtual	void OnCollision(GameObject* go);
	virtual void HandleEvent(Event* pEvent);
	virtual void Init();
	virtual void Update();
public:
	GameObject* mOwner;
	ScriptType mType;
};
