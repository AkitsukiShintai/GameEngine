/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<PhysicsManager.cpp>
Purpose:<implement all functions of class PhysicsManager>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"PhysicsManager.h"
#include"GameObject.h"
#include"Component/Body.h"
#include"Component/Transform.h"
#include"Component/Component.h"
#include"GameObjectManager.h"
#include"CollisionManager.h"
#include"Render/Program.h"
#include<iostream>
#include<regex>
#include"Math/q_tree.h"
//#define QTREE
extern GameObjectManager* gpGameObjectManager;
extern CollisionManager* gpCollisionManager;
extern Program* gpProgram;
using  Q_TREE::Rectangle;
PhysicsManager::PhysicsManager() :a(0, Rectangle<GameObject*>(glm::vec2(-1000.0f, -500.0f), glm::vec2(7000.0f, 1000.0f))) {


}
PhysicsManager::~PhysicsManager() {


}
void PhysicsManager::Update(float framTime) {
	gpCollisionManager->Reset();

#ifdef QTREE


	std::list<GameObject*> t;
	a.clear();
	int ttttt = 0;
	for (auto go : gpGameObjectManager->GameObjects)
	{
		Body* pTb = static_cast<Body*>(go->GetComponent(BODY));
		if (pTb != nullptr)
		{
			pTb->Intergrate(1000, framTime);
			Transform* pT = static_cast<Transform*> (go->GetComponent(TRANSFORM));
			Shape* pB = static_cast<Body*> (go->GetComponent(BODY))->mpShape;
			if (pB->mType == SHAPE_AABB)
			{
				ShapeAABB* AABB = static_cast<ShapeAABB*>(pB);
				a.insert(Rectangle<GameObject*>(glm::vec2(pT->mPos.x + AABB->mLeft, pT->mPos.y + AABB->mBottom), glm::vec2(AABB->mRight - AABB->mLeft, AABB->mTop - AABB->mBottom), go));

			}
			else if (pB->mType == SHAPE_CIRCLE)
			{
				ShapeCircle* cir = static_cast<ShapeCircle*>(pB);
				a.insert(Rectangle<GameObject*>(glm::vec2(pT->mPos.x - cir->mRadius, pT->mPos.y - cir->mRadius), glm::vec2(cir->mRadius*2.0f, cir->mRadius*2.0f), go));

			}
		}
	}
	Transform* pT;
	Shape* pB;
	for (auto go : gpGameObjectManager->GameObjects)
	{
		Body* pTb = static_cast<Body*>(go->GetComponent(BODY));
		if (pTb != nullptr)
		{
			pT = static_cast<Transform*> (go->GetComponent(TRANSFORM));
			pB = static_cast<Body*> (go->GetComponent(BODY))->mpShape;
			std::list<Rectangle<GameObject*>> t;
			if (pB->mType == SHAPE_AABB)
			{

				ShapeAABB* AABB = static_cast<ShapeAABB*>(pB);
				//a.insert(Rectangle<GameObject*>(glm::vec2(pT->mPos.x + AABB->mLeft, pT->mPos.y + AABB->mBottom), glm::vec2(AABB->mRight - AABB->mLeft, AABB->mTop - AABB->mBottom), go));
				a.retrieve(t, Rectangle<GameObject*>(glm::vec2(pT->mPos.x + AABB->mLeft, pT->mPos.y + AABB->mBottom), glm::vec2(AABB->mRight - AABB->mLeft, AABB->mTop - AABB->mBottom), go));
				for (auto go2 : t)
				{
					Body* pTb2 = static_cast<Body*>(go2.data->GetComponent(BODY));
 					if (pTb2 != nullptr)
					{
   						gpCollisionManager->CheckCollisionAndGenerateContact(
							pTb->mpShape, pTb->mPosX, pTb->mPosY,
							pTb2->mpShape, pTb2->mPosX, pTb2->mPosY
						);
					}

				}
			}
			else if (pB->mType == SHAPE_CIRCLE)
			{
				ShapeCircle* cir = static_cast<ShapeCircle*>(pB);
				a.retrieve(t, Rectangle<GameObject*>(glm::vec2(pT->mPos.x - cir->mRadius, pT->mPos.y - cir->mRadius), glm::vec2(cir->mRadius*2.0f, cir->mRadius*2.0f), go));

				for (auto go2 : t)
				{
					Body* pTb2 = static_cast<Body*>(go2.data->GetComponent(BODY));
					gpCollisionManager->CheckCollisionAndGenerateContact(
						pTb->mpShape, pTb->mPosX, pTb->mPosY,
						pTb2->mpShape, pTb2->mPosX, pTb2->mPosY
					);
				}



			}


		}
	}


#endif // QTREE

#ifndef QTREE


	for (auto go : gpGameObjectManager->GameObjects)
	{
		Body* pTb = static_cast<Body*>(go->GetComponent(BODY));
		if (pTb != nullptr)
		{
			pTb->Intergrate(1000, framTime);

		}
	}

	auto pObject1 = gpGameObjectManager->GameObjects.begin();
	auto pObjLast = gpGameObjectManager->GameObjects.end();

	for (; pObject1 != pObjLast; ++pObject1)
	{

		Body* pBody1 = static_cast<Body*>((*pObject1)->GetComponent(BODY));
		if (pBody1 == nullptr || !(*pObject1)->isShown)
		{
			continue;
		}



		for (auto pObject2 = pObject1 + 1; pObject2 != pObjLast; ++pObject2)
		{
			Body* pBody2 = static_cast<Body*>((*pObject2)->GetComponent(BODY));
			if (pBody2 == nullptr || !(*pObject2)->isShown)
			{
				continue;
			}


			if (pBody2->mOwner->name == "bullet" || pBody1->mOwner->name == "bullet")
			{
				//std::cout << "collision numbers" << gpCollisionManager->mCotacts.size() << std::endl;
			}


			gpCollisionManager->CheckCollisionAndGenerateContact(
				pBody1->mpShape, pBody1->mPosX, pBody1->mPosY,
				pBody2->mpShape, pBody2->mPosX, pBody2->mPosY
			);
		}
	}




#endif // !QTREE


}

