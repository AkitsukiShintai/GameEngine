/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Renderer.h>
Purpose:<declared class Renderer.h, for storaging openGL program>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"glew.h"
#include <iostream>
#include <fstream>
//#include <algorithm>
#include <string>

using namespace std;

class Renderer
{
public:
	Renderer();
	Renderer(std::string);
	~Renderer();

public:
	GLint mGLProgram,

		aposition,
		anormal,
		atexturecoord,

		ulight_color,
		upersp_matrix,
		uview_matrix,
		umodel_matrix,
		unormal_matrix,
		ulight_position,
		ucolor;
};

