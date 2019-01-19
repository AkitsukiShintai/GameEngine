/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Vector2D.cpp>
Purpose:<implement all functions declared in Vector2D.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Vector2D.h"
#define EPSILON 0.0001
#define DegreeToRad (3.1415926f/180.0f)
/*
In this function, pVec0 and pVec1 are considered as 2D points.
The distance between these 2 2D points is returned
*/
float Vector2DDistance(const glm::vec2& a, const glm::vec2& b) {
	glm::vec2 t = a - b;
	return sqrtf(t.x * t.x + t.y* t.y);

}

/*
In this function, pVec0 and pVec1 are considered as 2D points.
The squared distance between these 2 2D points is returned. Avoid the square root
*/
float Vector2DSquareDistance(const glm::vec2& a, const glm::vec2& b) {
	glm::vec2 t = a - b;
	return t.x * t.x + t.y* t.y;
}


/*
This function computes the coordinates of the vector represented by the angle "angle", which is in Degrees
*/
glm::vec2  Vector2DFromAngleDeg(float angle) {

	return glm::vec2(cosf(angle * DegreeToRad), sinf(angle*  DegreeToRad));

}

/*
This function computes the coordinates of the vector represented by the angle "angle", which is in Radian
*/
glm::vec2  Vector2DFromAngleRad(float angle) {

	return glm::vec2(cosf(angle ), sinf(angle));
}