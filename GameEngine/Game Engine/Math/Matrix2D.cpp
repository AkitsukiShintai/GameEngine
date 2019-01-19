/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Matrix2D.cpp>
Purpose:<implement all functions declared in Matrix2D.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include "Matrix2D.h"
#define DegreeToRad (3.1415926f/180.0f)

glm::mat3  Matrix2DIdentity() {

	return glm::mat3(1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f);
}

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
glm::mat3 Matrix2DTranspose(const glm::mat3& pMtx) {
	glm::mat3 x(0);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			x[i][j] = pMtx[j][i];
		}
	}
	return x;
}

/*
This function creates a translation matrix from x & y and saves it in Result
*/
glm::mat3 Matrix2DTranslate(float x, float y) {
	glm::mat3 pResult(0);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			pResult[i][j] = 0;
		}
	}
	pResult[1][1] = 1;
	pResult[2][2] = 1;
	pResult[0][0] = 1;
	pResult[0][2] = x;
	pResult[1][2] = y;

	pResult = Matrix2DTranspose(pResult);
	return pResult;
}

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
glm::mat3 Matrix2DScale(float x, float y) {
	glm::mat3 pResult(0);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			pResult[i][j] = 0;
		}
	}
	pResult[0][0] = x;
	pResult[1][1] = y;
	pResult[2][2] = 1;
	return pResult;
}


glm::mat3 Matrix2DScale(float s) {

	return Matrix2DScale(s, s);
}

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
glm::mat3 Matrix2DRotDeg(float Angle) {
	
	Angle = Angle * DegreeToRad;
	glm::mat3 pResult(0);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			pResult[i][j] = 0;
		}
	}
	pResult[0][0] = cosf(Angle);
	pResult[0][1] = -sinf(Angle);
	pResult[1][0] = sinf(Angle);
	pResult[1][1] = cosf(Angle);
	pResult[2][2] = 1;

	pResult = Matrix2DTranspose(pResult);
	return pResult;
}

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
glm::mat3 Matrix2DRotRad(float Angle) {

	glm::mat3 pResult(0);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			pResult[i][j] = 0;
		}
	}
	pResult[0][0] = cosf(Angle);
	pResult[0][1] = -sinf(Angle);
	pResult[1][0] = sinf(Angle);
	pResult[1][1] = cosf(Angle);
	pResult[2][2] = 1;

	pResult = Matrix2DTranspose(pResult);
	return pResult;

}


glm::mat4 view2D(const glm::vec4 & eye) {
	glm::mat4 result(0.0f);

	result[0][0] = result[1][1] = result[2][2] = result[3][3] = 1.0f;
	result[3][0] = -eye.x;
	result[3][1] = -eye.y;

	return result;
}

glm::mat4 perspective2D(float w, float h) {

	glm::mat4 result(0.0f);

	result[0][0] = 2.0f / w;
	result[1][1] = 2.0f / h;
	result[2][2] = 1.0f ;
	result[3][3] = 1.0f;
	return result;
}
