/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<InputManager.h>
Purpose:<declare functions of InputManager class>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#include"SDL_timer.h"
#include"SDL_stdinc.h"
#ifndef IMPUTMANAGER
#define IMPUTMANAGER

class InputManager {

public:
	InputManager() ;
	~InputManager();
public:
	void Update();

	bool IsPressed(unsigned int KeyScaneCode);
	bool IsReleased(unsigned int KeyScaneCode);
	bool IsTriggered(unsigned int KeyScaneCode);


private:
	Uint8 mCurrentState[512] = {0};
	Uint8 mPreviousState[512] = { 0 };
};











#endif // !InputManager