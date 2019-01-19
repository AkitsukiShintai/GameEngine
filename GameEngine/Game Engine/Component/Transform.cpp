/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Transform.cpp>
Purpose:<implement all functions in class Transform>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/19/2018>
History:

-End Header --------------------------------------------------------*/
#include "Transform.h"
#include"Component.h"
Transform::Transform():Component(TRANSFORM) {
	mPos = glm::vec2(0);
	mScale = glm::vec2(0);
	mRotate = glm::vec2(0);
}

Transform::~Transform() {

}

void Transform::Update() {

}
Transform* Transform::Clone(GameObject* _owner) {
	Transform* a = new Transform();
	a->mOwner = _owner;
	a->mPos = mPos;
	a->mRotate = mRotate;
	a->mScale = mScale;
	return a;
}

void Transform::Serialize(FILE **file) {
	//memset(imageName, 0, 256 * sizeof(char));
	//std::string filep = "";
	//fscanf_s(*file, "%f %f\n", &posX,&posY);
}

void Transform::Serialize(Json::Value value) {
	mPos.x = value["posx"].asInt();
	mPos.y = value["posy"].asInt();
	mScale.x = value["scalex"].asFloat();
	mScale.y = value["scaley"].asFloat();
	mRotate.x = value["rotatex"].asFloat();
	mRotate.y = value["rotatey"].asFloat();
}
