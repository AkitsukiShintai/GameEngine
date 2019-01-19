/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<FrameController.h>
Purpose:<declare functions of FrameController class>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#include"SDL_timer.h"
#pragma once
#ifndef FRC_H
#define FRC_H
class FrameController
{
public:
	FrameController(Uint32 framTime);
	~FrameController();

	void FramStart();
	void FramEnd();
	float DeltaTime();
	Uint32 CurrentFramTime();
	Uint32 passedFramTime();
private:
	Uint32 TickStart;
	Uint32 TickEnd;
	Uint32 framTime;
	Uint32 maxFramTime;
	Uint32 passedTime;

	float currentFramTime;
	float privousFramTime;
};
#endif