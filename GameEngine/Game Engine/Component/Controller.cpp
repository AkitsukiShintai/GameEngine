/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Controller.cpp>
Purpose:<implement all functions in class controller>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#include"Controller.h"
#include<SDL_scancode.h>
#include<algorithm>
#include"../InputManager.h"
#include"../FrameController.h"
#include"../Render/Program.h"
#include"../GameObjectManager.h"
#include"Component.h"
#include"Body.h"
#include"../Script/Bullet.h"

//#include"../GameObject.h"
extern Program* gpProgram;
extern   InputManager * gpInputManager;
extern   FrameController * gpFrameController;
extern   GameObjectManager * gpGameObjectManager;



Controller::Controller() :Component(CONTROLLER) {
	isJumping = false;
	left = true;
	right = true;
	currentState = DIR_RIGHT;
	speed = 150.0f;
	canControll = true;
	pauseFlag = false;
}
Controller::	~Controller() {
}

bool findBullet1(GameObject* it) {

	if (it->name == "bullet" && !it->isShown)
		return true;
	return false;

}


Controller* Controller::Clone(GameObject* _owners) {

	Controller* a = new Controller();
	a->isJumping = isJumping;
	a->left = left;
	a->mOwner = _owners;
	a->right = right;
	a->canControll = canControll;
	return a;

}
void Controller::Update() {
	if (!canControll)
	{
		return;
	}

	if (gpProgram->pause)
	{
		if (gpInputManager->IsTriggered(SDL_SCANCODE_F11)) {

			gpProgram->showSprite = !gpProgram->showSprite;

		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_F10)) {

			gpProgram->renderDebug = !gpProgram->renderDebug;

		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_F9)) {

			gpProgram->collisionDebug = !gpProgram->collisionDebug;

		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_P)) {

			gpProgram->pause = !gpProgram->pause;
			pauseFlag = true;
		}
		return;
	}

	if (gpInputManager->IsTriggered(SDL_SCANCODE_P)) {
		if (pauseFlag)
		{
			pauseFlag = false;
			return;
		}
		gpProgram->pause = !gpProgram->pause;

	}

	if (mOwner!= nullptr)
	{
		Body* pBody = static_cast<Body*>(mOwner->GetComponent(BODY));

		//gpInputManager->Update();
		
	/*	if (gpInputManager->IsPressed(SDL_SCANCODE_UP))
		{
			pT->mPosY += gpFrameController->DeltaTime() * 100;	
		}*/
	/*	if (gpInputManager->IsPressed(SDL_SCANCODE_DOWN))
		{
			pT->mPosY -= gpFrameController->DeltaTime() * 100;
		}*/
		if (gpInputManager->IsPressed(SDL_SCANCODE_LEFT) )
		{
			if (left)
			{
				float detaDis = gpFrameController->DeltaTime() * speed;
				pBody->mPosX -= detaDis;
				pBody->mRotate.x = 180.0f;
				currentState = DIR_LEFT;
			}
			else
			{
				left = true;
			}
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_RIGHT))
		{
			if (right)
			{
				float detaDis = gpFrameController->DeltaTime() * speed;
				pBody->mPosX += detaDis;
				pBody->mRotate.x = 0.0f;
				currentState = DIR_RIGHT;
			}
			else
			{
				right = true;
			}
		}
		if (gpInputManager->IsTriggered(SDL_SCANCODE_SPACE))
		{
			if (!isJumping)
			{
				pBody->mVelY += 500.0f;
				pBody->mInvMass =1.0f;
				isJumping = true;
			}		
		}

		if (gpInputManager->IsPressed(SDL_SCANCODE_1))
		{
			std::vector<GameObject*>::iterator shieldIt = std::find_if(gpGameObjectManager->GameObjects.begin(), gpGameObjectManager->GameObjects.end(), [](GameObject* t) {return t->name == "shield"; });
			Body* shieldBody = static_cast<Body*> ((*shieldIt)->GetComponent(BODY));

			shieldBody->mPosX = pBody->mPosX;
			shieldBody->mPosY = pBody->mPosY;
			(*shieldIt)->isShown = true;
		}

		if (gpInputManager->IsReleased(SDL_SCANCODE_1))
		{
			GameObject* shieldIt = gpGameObjectManager->FindeGameObjectByName("shield");
			shieldIt->isShown = false;
		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_2))
		{
			std::vector<GameObject*>::iterator bullet =  std::find_if(gpGameObjectManager->GameObjects.begin(), gpGameObjectManager->GameObjects.end(), findBullet1);
			if (bullet == gpGameObjectManager->GameObjects.end())
			{
				return;
				std::vector<GameObject*>::iterator bullet1 = std::find_if(gpGameObjectManager->GameObjects.begin(), gpGameObjectManager->GameObjects.end(), [](GameObject* t) {return t->name == "bullet"; });
				GameObject* newBullet = (*bullet1)->Clone();
				Body* bulletBody = static_cast<Body*> (newBullet->GetComponent(BODY));
				//Body* myBody = static_cast<Body*> (mOwner->GetComponent(BODY));
				float dir = 1.0f;
				if (currentState == DIR_LEFT)
				{
					dir = -1.0f;
				}
				bulletBody->mPosX = pBody->mPosX;
				bulletBody->mPosY = pBody->mPosY + 5;
				bulletBody->mVelX = dir*500.0f;
				static_cast<Bullet*>(newBullet->mScripts[0])->countTime = 0.0f;
			}
			else
			{
				Body* bulletBody = static_cast<Body*> ((*bullet)->GetComponent(BODY));
				Body* myBody = static_cast<Body*> (mOwner->GetComponent(BODY));
				float dir = 1.0f;
				if (currentState == DIR_LEFT)
				{
					dir = -1.0f;
				}
				bulletBody->mPosX = myBody->mPosX;
				bulletBody->mPosY = myBody->mPosY + 5;
				bulletBody->mVelX = dir*500.0f;
				(*bullet)->isShown = true;
				static_cast<Bullet*>((*bullet)->mScripts[0])->countTime = 0.0f;
			}
			
		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_F11)) {
			
			gpProgram->showSprite = !gpProgram->showSprite;
		
		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_F10)) {

			gpProgram->renderDebug = !gpProgram->renderDebug;

		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_F9)) {

			gpProgram->collisionDebug = !gpProgram->collisionDebug;

		}

		if (gpInputManager->IsTriggered(SDL_SCANCODE_W)) {

			gpProgram->eye.z += 10.0f;

		}

		
	}

}


void Controller::Serialize(FILE **file) {
	return;

}

void Controller::Serialize(Json::Value v) {
	speed = v["speed"].asFloat();
	return;
}