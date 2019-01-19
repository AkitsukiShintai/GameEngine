/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Animation.h>
Purpose:<declare class Animation as a part of Body>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
//#include"Body.h"
#ifndef SHAPE_H
#define SHAPE_H
#include"glm.hpp"
#include<vector>
#include<string>
class Body;

enum SHAP_TYPE {
	SHAPE_CIRCLE,
	SHAPE_POINT,
	SHAPE_AABB,
	SHAPE_NUM
};


class Shape {
public:
	

	Shape(unsigned int);
	virtual ~Shape();
	virtual bool TestPoint(float posX, float posY);
	virtual Shape* Clone(Body* _body) = 0;
public:
	Body* mBody;
    const unsigned int mType;
	std::vector<std::string> collisionList;
};

//----------------------------------------------------------------------------
//Circle
class ShapeCircle:public Shape
{
public:
	ShapeCircle();
	~ShapeCircle();
	ShapeCircle* Clone(Body* _body);
	bool TestPoint(float posX, float posY);
public:
	float mRadius;
	
private:

};


//----------------------------------------------------------------------------
//class ShapeRectangle :public Shape
//{
//public:
//	ShapeRectangle();
//	~ShapeRectangle();
//	bool TestPoint(float posX, float posY) ;
//private:
//
//};

//AABB
class ShapeAABB :public Shape
{
public:
	ShapeAABB();
	~ShapeAABB();
	ShapeAABB* Clone(Body* _body);
	bool TestPoint(float posX,float posY) ;
public:
	float mTop;
	float mBottom;
	float mLeft;
	float mRight;
};

//----------------------------------------------------------------------------
class ShapePoint :public Shape
{
public:
	ShapePoint();
	~ShapePoint();
	ShapePoint* Clone(Body* _body);
	bool TestPoint(float posX, float posY);

public:
	glm::vec2 mPos;
};

#endif // !SHAPE_H
