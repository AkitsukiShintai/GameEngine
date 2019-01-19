/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<CollisionManager.cpp>
Purpose:<implement all functions of class CollisionManager>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"CollisionManager.h"
#include<iostream>
#include"Script/Script.h"
#include<regex>
#include"glm.hpp"
extern EventManager* gpEventManager;

Contact::Contact() {
	mpBody[0] = nullptr;
	mpBody[1] = nullptr;
}
Contact::~Contact() {

}


CollisionManager::CollisionManager() {
	//CollisionFunctions[CIRCLE][AABB] = aa;
	//.........................
	for (size_t i = 0; i < SHAPE_NUM; ++i)
	{
		for (size_t j = 0; j < SHAPE_NUM; ++j)
		{
			CollisionFunctions[i][j] = nullptr;
		}
	}
	CollisionFunctions[SHAPE_CIRCLE][SHAPE_CIRCLE] = StaticCircleToStaticCircle;
	CollisionFunctions[SHAPE_CIRCLE][SHAPE_AABB] = StaticCircleToStaticRect;
	CollisionFunctions[SHAPE_AABB][SHAPE_CIRCLE] = StaticRectToStaticCircle;
	CollisionFunctions[SHAPE_AABB][SHAPE_AABB] = StaticRectToStaticRect;


}

CollisionManager::~CollisionManager() {
	Reset();
}

void CollisionManager::Reset() {

	for (auto c : mCotacts)
	{
		delete c;
	}
	mCotacts.clear();
}

void CollisionManager::CheckCollisionAndGenerateContact(Shape *pShape1, float pos1X, float pos1Y,
	Shape *pShape2, float pos2X, float pos2Y) {

	if (CollisionFunctions[pShape1->mType][pShape2->mType] != nullptr)
	{


		bool b = CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, pos1X, pos1Y,
			pShape2, pos2X, pos2Y, &mCotacts);
		//pShape1->mBody->mOwner->OnCollide();
		if (b)
		{

			CollisionEvent* e1 = new CollisionEvent(pShape2->mBody->mOwner);
			//gpEventManager->BroadcastToSubscribe(e);
			pShape1->mBody->mOwner->HandelEvent(e1);
			//if (pShape1->mBody != nullptr && pShape2->mBody != nullptr ) {
			CollisionEvent* e2 = new CollisionEvent(pShape1->mBody->mOwner);
			pShape2->mBody->mOwner->HandelEvent(e2);
			delete e2;
			delete e1;

		}

	}
	else
	{
		std::cout << "has no function match the Shape type:  " << pShape1->mType << " , " << pShape2->mType << " to claculate if collide" << std::endl;
	}

	return;

}