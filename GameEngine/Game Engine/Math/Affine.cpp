/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Affine.cpp>
Purpose:<implement all functions declared in Affine.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include "glm.hpp"
#include "vec4.hpp"
#include"Affine.h"
#define DEGREE_TO_RADIAN 3.1415927f/180.0f

glm::mat4 scale(float r) {

		glm::mat4 x = glm::mat4(
			r, 0, 0, 0,
			0, r, 0, 0,
			0, 0, r, 0,
			0, 0, 0, 1);
		return x;
	}

	glm::mat4 scale(float rx, float ry, float rz) {

		glm::mat4 x = glm::mat4(
			rx, 0, 0, 0,
			0, ry, 0, 0,
			0, 0, rz, 0,
			0, 0, 0, 1);

		return x;
	}

	glm::mat4 translate(const glm::vec4& v) {
		glm::mat4 x = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			v.x, v.y, v.z, 1);
		return x;
	}

	glm::mat4 rotate(float t, const glm::vec4& v) {
		/// t is degree
		glm::vec4 vv = glm::normalize(v);
		glm::mat4 x = glm::mat4(
			glm::cos(t*DEGREE_TO_RADIAN) + (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.x*vv.x, (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.x * vv.y + glm::sin(t*DEGREE_TO_RADIAN)*vv.z, (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.x * vv.z - glm::sin(t*DEGREE_TO_RADIAN)*vv.y, 0,
			(1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.x * vv.y - glm::sin(t*DEGREE_TO_RADIAN)*vv.z, glm::cos(t*DEGREE_TO_RADIAN) + (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.y*vv.y, (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.y*vv.z + glm::sin(t*DEGREE_TO_RADIAN)*vv.x, 0,
			(1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.x * vv.z + glm::sin(t*DEGREE_TO_RADIAN)*vv.y, (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.y * vv.z - glm::sin(t*DEGREE_TO_RADIAN)*vv.x, glm::cos(t*DEGREE_TO_RADIAN) + (1.0f - glm::cos(t*DEGREE_TO_RADIAN))*vv.z * vv.z, 0,
			0, 0, 0, 1.0f);
		/*glm::mat4 xx = glm::mat4(
			glm::cos(t*DEGREE_TO_RADIAN) + (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.x*v.x, (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.x * v.y - glm::sin(t*DEGREE_TO_RADIAN)*v.z, (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.x * v.z + glm::sin(t*DEGREE_TO_RADIAN)*v.y, 0,
			(1 - glm::cos(t*DEGREE_TO_RADIAN))*v.x * v.y + glm::sin(t*DEGREE_TO_RADIAN)*v.z, glm::cos(t*DEGREE_TO_RADIAN) + (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.y*v.y, (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.y * v.z - glm::sin(t*DEGREE_TO_RADIAN)*v.x, 0,
			(1 - glm::cos(t*DEGREE_TO_RADIAN))*v.x * v.z - glm::sin(t*DEGREE_TO_RADIAN)*v.y, (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.y*v.z + glm::sin(t*DEGREE_TO_RADIAN)*v.x, glm::cos(t*DEGREE_TO_RADIAN) + (1 - glm::cos(t*DEGREE_TO_RADIAN))*v.z * v.z, 0,
			0, 0, 0, 1);*/

		return x;
	}

	glm::mat4 transpose3x3(const glm::mat4& A) {

		glm::mat4 x = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				x[i][j] = A[i][j];
			}
		}
		//delete[]a;
		return x;
	}

	glm::vec4 cross(const glm::vec4 &u, const glm::vec4 &v) {
		float x = -u.z * v.y + u.y * v.z;
		float y = u.z*v.x - u.x*v.z;
		float z = -u.y*v.x + u.x*v.y;
		glm::vec4 xx = glm::vec4(x, y, z, 0);
		return xx;
	}


	glm::mat4 view(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &rup) {
		glm::vec4 w = scale(-1.0f / length(look)) * look;
		glm::vec4 v = scale(1.0f / length(rup)) * rup;
		glm::vec4 u = cross(v, w);
		glm::mat4 rotate = glm::mat4{
			u.x, v.x, w.x, 0.0f,
			u.y, v.y ,w.y, 0.0f,
			u.z, v.z, w.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		glm::mat4 translate = glm::mat4{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f ,0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-eye.x, -eye.y, -eye.z, 1.0f
		};
		glm::mat4 transform = rotate * translate;

		return transform;
	}

	glm::mat4 perspective(float fov, float aspect, float near) {
		//2*near/w
		float t = 1.0f / tanf((0.5f * fov)*DEGREE_TO_RADIAN);
		glm::mat4 perspective = glm::mat4{
			t , 0.0f,0.0f,0.0f,
			0.0f,t * aspect,0.0f,0.0f,
			0.0f,0.0f,-1,-1,
			0.0f,0.0f,-2 * near,0.0f
		};
		return perspective;
	}

	glm::mat4 perspective(float fov, float aspect, float near, float far) {
		//2*near/w
		float t = 1.0f / tanf((0.5f * fov)*DEGREE_TO_RADIAN);
		glm::mat4 perspective = glm::mat4{
			t, 0.0f,0.0f,0.0f,
			0.0f,t*aspect,0.0f,0.0f,
			0.0f,0.0f,(near + far) / (near - far),-1,
			0.0f,0.0f,2 * far*near / (near - far),0.0f
		};
		return perspective;
	}
