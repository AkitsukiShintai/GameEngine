/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<InputManager.cpp>
Purpose:<implement functions in InputManager.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#include "InputManager.h"
#include "SDL_keyboard.h"

InputManager::InputManager() {	
		
		SDL_memset(mCurrentState, 0, 512 * sizeof(Uint8));
		SDL_memset(mPreviousState, 0, 512 * sizeof(Uint8));
	
};


InputManager::~InputManager() {
	//delete(_instance);
};

void InputManager::Update() {
	int numberOfKey = 0;
	const Uint8* pCurrentKeyState = SDL_GetKeyboardState(&numberOfKey);
	if (numberOfKey > 512)
	{
		numberOfKey = 512;
	}
	SDL_memcpy(mPreviousState, mCurrentState, numberOfKey * sizeof(Uint8));
	SDL_memcpy(mCurrentState, pCurrentKeyState, numberOfKey * sizeof(Uint8));

}
	

bool InputManager::IsPressed(unsigned int KeyScaneCode) {
	if (mCurrentState[KeyScaneCode] == 1 )
	{
		return true;
	}
	return false;

}


bool InputManager::IsReleased(unsigned int KeyScaneCode) {

	if (mCurrentState[KeyScaneCode] == 0 && mPreviousState[KeyScaneCode] == 1)
	{
		return true;
	}
	return false;

}


bool InputManager::IsTriggered(unsigned int KeyScaneCode) {
	if (mCurrentState[KeyScaneCode] == 1 && mPreviousState[KeyScaneCode] == 0)
	{
		return true;
	}
	return false;

}