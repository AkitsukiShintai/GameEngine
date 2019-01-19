/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Number.cpp>
Purpose:<implement all functions of class Number, not used for anything>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Number.h"

Number::Number():Component(NUMBER) {

}
Number::~Number() {


}
void Number::Update() {


}
Number* Number::Clone(GameObject*_owner) {

	Number* newN = new Number();
	newN->number = number;
	newN->mOwner = _owner;
	return newN;
}
void Number::Serialize(FILE **file) {

}
void Number::Serialize(Json::Value) {


}
void Number::HandleEvent(Event* pEvent) {


}