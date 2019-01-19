/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<LineSegment2D.h>
Purpose:<declare a class LineSegment2D for simulating line struct>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/19/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"glm.hpp"
#ifndef LINESEGMENT2D_H
#define LINESEGMENT2D_H

class LineSegment2D {
public:
	LineSegment2D(glm::vec2 Point0, glm::vec2 Point1);
	~LineSegment2D();
	glm::vec2 mP0;
	glm::vec2 mP1;
	glm::vec2 mN;
	float mNdotP0;
};

#endif