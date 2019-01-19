/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<UpDown.cpp>
Purpose:<implement all functions in class UpDown>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#include"UpDown.h"
#include"Body.h"
#include"../FrameController.h"
extern  FrameController* gpFrameController;

UpDown::UpDown():Component(UPDOWN) {
	speed = 3.0f;
	dis = 500.0f;
	upFlag = true;
	passedTime = 0.0f;
	origionY = 0;
	InitOrigionY = false;
}
UpDown::~UpDown() {}

UpDown* UpDown::Clone(GameObject* _owners) {

	UpDown* a = new UpDown();
	a->dis = dis;
	a->InitOrigionY = InitOrigionY;
	a->speed = speed;
	a->upFlag = upFlag;
	a->origionY = origionY;
	a->passedTime = passedTime;
	return a;
}




void UpDown::Update() {
	Body* pT = static_cast<Body*> (this->mOwner->GetComponent(BODY));
	if (pT == nullptr)
	{
		return;
	}
	if (!InitOrigionY) {
		origionY = pT->mPosY;
		InitOrigionY = true;
	}	
	float t = -1.0f;
	if (pT->mPosY > origionY+dis|| pT->mPosY < origionY - dis)
	{
		//passedTime = 0.0f;
		upFlag = !upFlag;
	}

	if (!upFlag)
	{
		t = 1.0f;
	}

	pT->mPosY += t * float(speed) * gpFrameController->DeltaTime();
	//printf("current per fram %f", gpFrameController->DeltaTime());
	//printf("current img %s pos: x = %f, y = %f \n", pT->mOwner->name.c_str(), pT->mPosY, pT->mPosY);

	//passedTime += gpFrameController->DeltaTime();
}
void UpDown::Serialize(FILE **file){

	fscanf_s(*file, "%f %f\n", &speed, &dis);
}

void UpDown::Serialize(Json::Value value) {
	speed = value["speed"].asInt();
	dis = value["distance"].asInt();;
}


void UpDown::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == EVENT_COLLIDE)
	{
		Body* pB =static_cast<Body*> (this->mOwner->GetComponent(BODY));

		if (pB != nullptr)
		{
			pB->mPosX += 100.0f;
		}
	}



}