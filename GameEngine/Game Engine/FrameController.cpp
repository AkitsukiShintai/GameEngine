/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<FrameController.cpp>
Purpose:<implement functions in FrameController.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#include "FrameController.h"
#include "stdio.h"
FrameController::FrameController(Uint32 maxFram)
{
	if (maxFram == 0)
	{
		maxFramTime = -1;
	}
	else
	{
		maxFramTime = 1000 / maxFram;
	}
	 TickStart=0;
	 TickEnd =0;
	 framTime = 0;
	 passedTime = 0;
}

FrameController::~FrameController()
{
}

void FrameController:: FramStart() {
	TickStart = SDL_GetTicks();
};
void FrameController:: FramEnd() {
	TickEnd = SDL_GetTicks();

	while (TickEnd - TickStart < maxFramTime)
	{
		TickEnd = SDL_GetTicks();
	}
	framTime = TickEnd - TickStart;
	passedTime += framTime;
};

Uint32 FrameController::CurrentFramTime() {
	return framTime;
}

float  FrameController::DeltaTime() {

	printf("Current Frame Time%f  ms\n", framTime * 0.001f);
	return framTime * 0.001f;
}


Uint32 FrameController::passedFramTime() {
	return passedTime;

}