/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<LineSegment2D.cpp>
Purpose:<implement class LineSegment2D>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Affine.h"
#include"LineSegment2D.h"
#include"Matrix2D.h"

LineSegment2D::LineSegment2D(glm::vec2 Point0, glm::vec2 Point1):mP0(Point0), mP1(Point1) {
	
	mN = Point1 - Point0; 
	glm::mat2 r = Matrix2DRotDeg(-90.0f);
	mN = r * mN;
	mN = glm::normalize(mN);
	mNdotP0 = glm::dot(mN, mP0);
}


LineSegment2D::~LineSegment2D() {




}