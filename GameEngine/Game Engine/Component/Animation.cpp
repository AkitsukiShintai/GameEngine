/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Animation.cpp>
Purpose:<implement all functions of class Animation>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Animation.h"
#include"Sprite.h"
#include"../ResourceManager.h"
#include"../FrameController.h"
extern ResourceManager* gpResourceManager;
extern FrameController* gpFrameController;
Animation::Animation() :Component(ANIMATION), run(true), currentIndex(0), currentState(""), time(0.0f), duringTime(0){


}

Animation* Animation::Clone(GameObject*_owner) {

	Animation* a = new Animation();
	a->run = run;
	a->currentIndex = currentIndex;
	a->currentState = currentState;
	a->time = time;
	a->duringTime = duringTime;
	a->imgType = imgType;
	a->mOwner = _owner;
	for (auto it = stateIndex.begin();it!=stateIndex.end();++it)
	{
		a->stateIndex[(*it).first] = (*it).second;
	}


	return a;
}


Animation::~Animation() {

}

void Animation::Update() {
	if (run)
	{
		if (time< duringTime)
		{
			time += gpFrameController->DeltaTime();
			return;
		}
		std::string filep = "../Resource/Image/" + currentState +"_"+ std::to_string(currentIndex) + "." + imgType;
		static_cast<Sprite*> (mOwner->GetComponent(SPRITE))->texture = gpResourceManager->LoadTexture((filep.c_str()));
		//mOwner->GetComponent<Sprite>()->texture = gpResourceManager->LoadTexture((filep.c_str()));
		currentIndex++;
		if (currentIndex > stateIndex[currentState])
		{
			currentIndex = 0;
		}
		time = 0.0f;
	}
	
}

void Animation::Serialize(FILE **file) {



}
void Animation::Serialize(Json::Value root) {

	duringTime = root["during"].asFloat();
	imgType = root["type"].asString();
	root = root["sprites"];
	int a = root.size();
	for (size_t i = 0; i < root.size(); i++)
	{
		stateIndex[root[i]["sprite"].asString()] = root[i]["index"].asInt();

	}
	//index = val["index"].asInt();
	currentState = root[0]["sprite"].asString();
}
void Animation::HandleEvent(Event* pEvent) {



}