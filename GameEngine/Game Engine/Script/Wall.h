/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Wall.h>
Purpose:<declared class Wall, for behaviour of obstacles suspended in the air >
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include "Script.h"
#include"../Component/Body.h"
#include"../Component/Controller.h"
#include"../GameObject.h"
#include"../GameObjectManager.h"
#include<regex>
extern GameObjectManager* gpGameObjectManager;
class Wall :public Script {

public:
	Wall() :Script(WALL) {}
	~Wall() {}
	void OnCollision(GameObject* go) {
		if (go->name == "player0" )
		{

 			playerSprite = static_cast<Sprite*>(go->GetComponent(SPRITE));
			playerBody = static_cast<Body*>(go->GetComponent(BODY));
			myBody = static_cast<Body*>(mOwner->GetComponent(BODY));
			playerTrans = static_cast<Transform*>(go->GetComponent(TRANSFORM));

			pController = static_cast<Controller*>(go->GetComponent(CONTROLLER));
			mySprite = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));

			if (myBody->mPosX - mySprite->size.x/2.0f > playerBody->mPosX) // collide at left
			{
				playerBody->mVelX = 0.0f;
  				pController->right = false;
				//playerBody->mPosX = myBody->mPosX - mySprite->size.x / 2.0f - playerSprite->size.x / 2.0f ;		
			}
			else if (myBody->mPosX + mySprite->size.x/2.0f < playerBody->mPosX) // collide at right
			{
				//playerBody->mPosX = myBody->mPosX + mySprite->size.x / 2.0f + playerSprite->size.x / 2.0f ;

				playerBody->mVelX = 0.0f;
				pController->left = false;
			}
			
			

			if (playerBody->mVelY < 0)
			{
				return;
			}

			if ( myBody->mPosY- mySprite->size.y/2.0f > playerBody->mPosY || myBody->mPosY > playerBody->mPosY + playerSprite->size.y/2.0f || playerBody->mVelY>0) // collide at bottom
			{
			
				playerBody->mVelY = -100.0f;
				//playerBody->mPosY = myBody->mPosY - mySprite->size.y / 2.0f - playerSprite->size.y / 2.0f - 1.0f;
				//playerTrans->mPos.y = playerBody->mPosY;

				return;
			}
		}
		else if ( std::regex_match(go->name, std::regex("enemy.*")))
		{
			playerSprite = static_cast<Sprite*>(go->GetComponent(SPRITE));
			playerBody = static_cast<Body*>(go->GetComponent(BODY));
			myBody = static_cast<Body*>(mOwner->GetComponent(BODY));
			playerTrans = static_cast<Transform*>(go->GetComponent(TRANSFORM));
			mySprite = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));

			if (myBody->mPosY - mySprite->size.y / 2.0f > playerBody->mPosY || myBody->mPosY > playerBody->mPosY + playerSprite->size.y / 2.0f) // collide at bottom
			{
				playerBody->mVelY = -100.0f;
				playerBody->mPosY = myBody->mPosY - mySprite->size.y / 2.0f - playerSprite->size.y / 2.0f - 1.0f;
				//playerTrans->mPos.y = playerBody->mPosY;

				return;
			}


		}
	}

	
	void Init() {


	}
private:
	Sprite* playerSprite;
	Body* playerBody;
	Sprite* mySprite;
	Body* myBody;
	Controller* pController;
	Transform* playerTrans;
};