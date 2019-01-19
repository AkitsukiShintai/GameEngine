/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Shape.cpp>
Purpose:<implement all functions of class Shape>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Shape.h"
#include"../Math/Math2D.h"
#include"../GameObjectManager.h"
extern GameObjectManager* gpGameObjectManager;

Shape::Shape(unsigned int t):mType(t), collisionList(0){
	//mType = t;
	mBody = nullptr;
	
}
Shape::~Shape() {
	//mType = SHAPE_NUM;
	mBody = nullptr;

}

bool Shape::TestPoint(float posX, float posY) {
	return false;
}


//---------------------------------------------------------------------------
ShapeCircle::ShapeCircle() : Shape(SHAPE_CIRCLE), mRadius(0)
{

}
ShapeCircle* ShapeCircle::Clone(Body* _body) {
	ShapeCircle* a = new ShapeCircle();
	a->mBody = _body;
	a->mRadius = mRadius;
	return a;
}
ShapeCircle::~ShapeCircle()
{
}


bool ShapeCircle::TestPoint(float posX, float posY) {
	return false;
}

//-------------------------------------------------------------------------------------------
ShapeAABB::ShapeAABB():Shape(SHAPE_AABB) ,mTop(0.0f), mBottom(0.0f), mLeft(0.0f), mRight(0.0f) {


}

ShapeAABB* ShapeAABB::Clone(Body* _body) {
	ShapeAABB* a = new ShapeAABB();
	a->mBody = _body;
	a->mTop = mTop;
	a->mBottom = mBottom;
	a->mLeft = mLeft;
	a->mRight = mRight;
	return a;
}
ShapeAABB::~ShapeAABB() {

}
bool ShapeAABB::TestPoint(float posX, float posY) {

	return false;
}

//----------------------------------------------------------------------------
ShapePoint::ShapePoint():Shape(SHAPE_POINT), mPos(0)
{
	
}

ShapePoint* ShapePoint::Clone(Body* _body) {
	ShapePoint* a = new ShapePoint();
	a->mBody = _body;
	a->mPos = mPos;
	return a;
}
ShapePoint::~ShapePoint() {



}

bool ShapePoint::TestPoint(float posX, float posY) {
	return false;
}