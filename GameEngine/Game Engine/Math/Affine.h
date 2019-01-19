/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Affine.h>
Purpose:<declare some functions for rendering>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/19/2018>
History:

-End Header --------------------------------------------------------*/
#ifndef AFFINE_H
#define AFFINE_H
#include "glm.hpp""

glm::mat4 scale(float r);

glm::mat4 scale(float rx, float ry, float rz);

glm::mat4 translate(const glm::vec4& v);

glm::mat4 rotate(float t, const glm::vec4& v);

glm::mat4 transpose3x3(const glm::mat4& A);

glm::vec4 cross(const glm::vec4 &u, const glm::vec4 &v);

glm::mat4 view(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &rup);

glm::mat4 perspective(float fov, float aspect, float near);

glm::mat4 perspective(float fov, float aspect, float near, float far);


#endif

