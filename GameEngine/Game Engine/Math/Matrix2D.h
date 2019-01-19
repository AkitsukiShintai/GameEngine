/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Matrix2D.h>
Purpose:<declare some functions for 2D transformation>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#ifndef MATRIX2D_H
#define MATRIX2D_H
#include"glm.hpp"


/*
This function sets the matrix Result to the identity matrix
*/
glm::mat3  Matrix2DIdentity();

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
glm::mat3 Matrix2DTranspose(const glm::mat3& pMtx);



/*
This function creates a translation matrix from x & y and saves it in Result
*/
glm::mat3 Matrix2DTranslate( float x, float y);

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
glm::mat3 Matrix2DScale(  float x, float y);
glm::mat3 Matrix2DScale(float s);
/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
glm::mat3 Matrix2DRotDeg(float Angle);

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
glm::mat3 Matrix2DRotRad( float Angle);


glm::mat4 view2D(const glm::vec4 & eye);

glm::mat4 perspective2D(float w, float h);

#endif