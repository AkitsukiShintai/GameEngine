/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<CollisionManager.h>
Purpose:<declare CollisionManager class. For managing collision functions and event>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include"Component/Body.h"
#include"Math/Math2D.h"
#include<list>
#include"EventManager.h"


class Contact {
public:
	Contact();
	~Contact();

public:
	Body*	mpBody[2];
};


class CollisionManager {
public:
	CollisionManager();
	~CollisionManager();
	void Reset();
	void CheckCollisionAndGenerateContact(Shape *pShape1, float pos1X, float pos1Y,Shape *pShape2, float pos2X, float pos2Y);

public:
	std::list<Contact*> mCotacts;
	//2D array of funciton pointers, used to store the collision function* addresses
	bool(*CollisionFunctions[SHAP_TYPE::SHAPE_NUM][SHAP_TYPE::SHAPE_NUM]) (Shape *, float, float,Shape *, float, float, std::list<Contact*> *);

};