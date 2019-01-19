/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Plane.cpp>
Purpose:<implement all functions declared in Plane.h, generate  plane points, (-1,-1)(1,-1)(1,1)(-1,1)>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include "Plane.h"
#include"../Math/Affine.h"
#include "Math.h"

Plane::Plane()
    : vertices(0),
      normals(0),
      faces(2) {
	glm::vec4 a(-1,-1,0,1);
	glm::vec4 b(1, -1, 0, 1);
	glm::vec4 c(1, 1, 0, 1);
	glm::vec4 d(-1, 1, 0, 1);
	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);
	vertices.push_back(d);
	glm::vec4 normal(0, 0, 1, 0);
	for (size_t i = 0; i < vertices.size(); i++)
	{
		normals.push_back(normal);
	}
	
	//Face face1 = { 0,1,3 };
	//Face face2 = { 0,3,2 };
	//faces.push_back(face1);
	//faces.push_back(face2);

	unsigned int face1[3] = { 0,1,2 };
	unsigned int face2[3] = { 0,2,3 };
	for (size_t i = 0; i < 3; i++)
	{
		faces[0][i]=(face1[i]);
	}
	
	for (size_t i = 0; i < 3; i++)
	{
		faces[1][i] = (face2[i]);
	}
}

