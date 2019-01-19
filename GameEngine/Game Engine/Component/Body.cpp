/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Body.cpp>
Purpose:<implement all functions of class Body>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Body.h"
#include"Transform.h"
#include"Component.h"
#include"Sprite.h"
//#include"GameObject.h"
#include<algorithm>
#define EPSILEN 0.00001f
Body::Body() :Component(BODY) {
	mPosX = mPosY = 0;
	mPreviousX = mPreviousY = 0;
	mVelX = mVelY = 0;
	mAccX = mAccY = 0;
	mTotalForceX = mTotalForceY = 0;
	mMass = mInvMass = 0.0f;
	mpShape = nullptr;
	mRotate = glm::vec2(0);
}
Body*  Body::Clone(GameObject*_owner) {
	
	Body* a = new Body();
	a->mOwner = _owner;
	a->mPosX = mPosX; a->mPosY = mPosY;
	a->mPreviousX = mPreviousX;
	a->mPreviousY = mPreviousY;
	a->mVelX = mVelX;
	a->mVelY = mVelY;
	a->mAccX = mAccX;
	a->mAccY = mAccY;
	a->mTotalForceX = mTotalForceX;
	a->mTotalForceY = mTotalForceY;
	a->mMass = mMass;
	a->mInvMass = mInvMass;
	a->mpShape = mpShape->Clone(a);
	a->mRotate = mRotate;
	for (size_t i = 0; i < mpShape->collisionList.size(); i++)
	{
		a->mpShape->collisionList.push_back(mpShape->collisionList[i]);
	}
	return a;
}

Body::~Body() {
	if (mpShape != nullptr)
	{
		delete mpShape;
		mpShape = nullptr;
	}
	
}

void Body::Update() {


}

void Body::Serialize(FILE **file) {


}


void Body::Init() {
	Transform* pTr = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM));
	if (pTr != nullptr)
	{
		mPreviousX = mPosX = pTr->mPos.x;
		mPreviousY = mPosY = pTr->mPos.y;
		mRotate = pTr->mRotate;
	}


	if (mpShape != nullptr)
	{

		if (mpShape->mType == SHAPE_CIRCLE)
		{
			if (static_cast<ShapeCircle*>(mpShape)->mRadius - 0.0f < EPSILEN)
			{
				static_cast<ShapeCircle*>(mpShape)->mRadius = (static_cast<Transform*>(mOwner->GetComponent(TRANSFORM)))->mScale.y / 2.0f;
			}
		}
		else if (mpShape->mType == SHAPE_AABB)
		{
			if (static_cast<ShapeAABB*>(mpShape)->mTop - 0.0f < EPSILEN)
			{
				ShapeAABB* p = static_cast<ShapeAABB*>(mpShape);
				Sprite* pS = static_cast<Sprite*>(mOwner->GetComponent(SPRITE));
				p->mTop = pS->size.y / 2.0f;
				p->mBottom = -pS->size.y / 2.0f;
				p->mLeft = -pS->size.x / 2.0f;
				p->mRight = pS->size.x / 2.0f;
			}
		}
	}
}


void Body::Intergrate(float gravity, float framtime) {
	//save current position
	mPreviousX = mPosX;
	mPreviousY = mPosY;

	//compute accaleration
	mTotalForceY -= gravity;

	//compute accelerate
	mAccX = mTotalForceX * mInvMass;
	mAccY = mTotalForceY * mInvMass;

	//compute velocity
	mVelX += mAccX * framtime;
	mVelY += mAccY * framtime;

	mPosX += mVelX * framtime;
	mPosY += mVelY * framtime;

	mTotalForceX = 0.0f;
	mTotalForceY = 0.0f;

	//mVelX *= 0.95f;
	//mVelY *= 0.95f;

	Transform* pTr = static_cast<Transform*>(mOwner->GetComponent(TRANSFORM));
	if (pTr != nullptr)
	{
		pTr->mPos = glm::vec2(mPosX, mPosY);
		pTr->mRotate = mRotate;
	}
}



void Body::Serialize(Json::Value value) {

	Json::Value::Members m = value.getMemberNames();

	for (auto i : m)
	{
		if (i == "mass")
		{
			mMass = value[i].asFloat();
		}
		else if (i == "shape")
		{
			std::string shapetype = value[i]["type"].asString();
			if (shapetype == "circle")
			{
				mpShape = new ShapeCircle();
				mpShape->mBody = this;
				static_cast<ShapeCircle*>(mpShape)->mRadius = value[i]["radius"].asFloat();
			}
			else if (shapetype == "AABB")
			{
				mpShape = new ShapeAABB();
				mpShape->mBody = this;
				ShapeAABB* p = static_cast<ShapeAABB*>(mpShape);

				p->mTop = value[i]["top"].asFloat();
				p->mBottom = value[i]["bottom"].asFloat();
				p->mLeft = value[i]["left"].asFloat();
				p->mRight = value[i]["right"].asFloat();
			}
			else if (shapetype == "point")
			{
				mpShape = new ShapePoint();
				mpShape->mBody = this;
			}

			int dd = value[i]["collision"].size();
			for (size_t j = 0; j < value[i].size(); j++)
			{
				std::string x = value[i]["collision"][j].asString();
				if (x == "")
				{
					continue;
				}
				// x = x+".*";

				mpShape->collisionList.push_back(x);

			}
		}
	}

	if (mMass != 0.0f)
	{
		mInvMass = 1.0f / mMass;
	}
	else
	{
		mInvMass = 0.0f;
	}

}