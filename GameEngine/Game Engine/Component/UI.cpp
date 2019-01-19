/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<UI.cpp>
Purpose:<implement all functions of class UserInterface>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"UI.h"
#include"Transform.h"
#include"glm.hpp"
extern Program* gpProgram;


UserInterface::UserInterface():Component(UI){
	originPos = glm::vec2(0);
}


void UserInterface::Update() {
	static_cast<Transform*> (mOwner->GetComponent(TRANSFORM))->mPos = originPos+  glm::vec2(gpProgram->eye.x, gpProgram->eye.y);
}


UserInterface::~UserInterface() {


}
UserInterface*  UserInterface::Clone(GameObject* _owner) {
	return this;
}
void  UserInterface::Serialize(FILE **file) {

}
void  UserInterface::Serialize(Json::Value) {
}

void UserInterface::Init() {
	originPos = static_cast<Transform*> (mOwner->GetComponent(TRANSFORM))->mPos;
}