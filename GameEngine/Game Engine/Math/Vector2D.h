/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Vector2D.h>
Purpose:<head file of Vector2D.c>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_1_Part1>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<9/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H

#include "math.h"
#include"glm.hpp"


/*
In this function, pVec0 and pVec1 are considered as 2D points.
The distance between these 2 2D points is returned
*/
float Vector2DDistance(const glm::vec2&, const glm::vec2&);

/*
In this function, pVec0 and pVec1 are considered as 2D points.
The squared distance between these 2 2D points is returned. Avoid the square root
*/
float Vector2DSquareDistance(const glm::vec2&, const glm::vec2&);


/*
This function computes the coordinates of the vector represented by the angle "angle", which is in Degrees
*/
glm::vec2  Vector2DFromAngleDeg(float);

/*
This function computes the coordinates of the vector represented by the angle "angle", which is in Radian
*/
glm::vec2  Vector2DFromAngleRad( float);

#endif