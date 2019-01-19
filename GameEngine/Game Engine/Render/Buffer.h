/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Buffer.h>
Purpose:<declared class Buffer.h, for getting openGL buffers>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include "glew.h"
#include"glm.hpp"
#include<string>

class Buffer {
public:
	Buffer();
	Buffer(std::string);
	~Buffer();
	 void Create();
public:
	GLuint mVertexBuffer;
	GLuint mNormalBuffer;
	GLuint mFaceBuffer;
	GLuint mTextureCoordBuffer;
	int mFaceCount;
};