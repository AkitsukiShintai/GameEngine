///* Start Header -------------------------------------------------------
//Copyright (C) 2018
//DigiPen Institute of Technology.
//Reproduction or disclosure of this file or its contents without the prior
//written consent of DigiPen Institute
//of Technology is prohibited.
//File Name:<Main.cpp>
//Purpose:<the main file of this application>
//Language:<C++>
//Platform:<windows 10>
//Project:<CS529_w.zhongqiu_2_GameEngine>
//Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
//Creation date:<10/16/2018>
//History:
//<10/26/2018>
//modify the framework of the main function
//-End Header --------------------------------------------------------*/
#include <SDL.h>
#include "stdio.h"
#include "InputManager.h"
#include "FrameController.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include"Render/Program.h"
#include"ComponentMap.h"
#include "Component/Component.h"
#include "Component/Controller.h"
#include "Component/Transform.h"
#include "Component/Sprite.h"
#include"CollisionManager.h"
#include "ObjectFactory.h"
#include <Windows.h>
#include"PhysicsManager.h"
#include"EventManager.h"
#include"SceneManager.h"
#include<iostream>
#include"Render/Plane.h"
#include"Math/Affine.h"
#include"glew.h"

# define TEST true
# define Frame 60
#define Windows_Width 800
#define Windows_Heigh 600
InputManager * gpInputManager;
FrameController* gpFrameController;
GameObjectManager* gpGameObjectManager;
ResourceManager* gpResourceManager;
ObjectFactory* gpObjectFactory;
ComponentMap* gpComponentMap;
CollisionManager* gpCollisionManager;
PhysicsManager* gpPhysicsManager;
EventManager* gpEventManager;
Program* gpProgram;
SceneManager * gpSceneManager;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#pragma comment(lib, "legacy_stdio_definitions.lib")


int main(int argc, char* args[])
{
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}

	int w = Windows_Width, h = Windows_Heigh;
	SDL_Window *pWindow;
	int error = 0;
	bool appIsRunning = true;
	// Initialize SDL
	error = SDL_Init(SDL_INIT_VIDEO);
	if (error < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}
	pWindow = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		w,										// width, in pixels
		h,										// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);


	// SDL: initialize and create a window
	//bool appIsRunning = true;
	//SDL_Init(SDL_INIT_VIDEO);
	//const char *title = "Window Title";
	//int width = 500,
	//	height = 500;
	//SDL_Window *pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
	//	SDL_WINDOWPOS_UNDEFINED, width, height,
	//	SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(pWindow);


	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	//SDL_GLContext context = SDL_GL_CreateContext(pWindow);
	//glewExperimental = GL_TRUE;
	// GLEW: get function bindings (if possible)
	glewInit();
	glEnable(GL_TEXTURE);
	if (!GLEW_VERSION_2_0) {

		std::cout << "needs OpenGL version 2.0 or better" << std::endl;
		//return -1;
	}

	//SDL_Surface* pImage = NULL;
	//pImage = SDL_LoadBMP("..//hello.bmp");

	SDL_Surface* pWinSurface = SDL_GetWindowSurface(pWindow);

	gpInputManager = new InputManager();
	gpObjectFactory = new ObjectFactory();
	gpFrameController = new FrameController(Frame);
	gpGameObjectManager = new GameObjectManager();
	gpResourceManager = new ResourceManager();
	gpComponentMap = new ComponentMap();
	//gpComponentMap->InitializeMap();
	gpCollisionManager = new CollisionManager();
	gpPhysicsManager = new PhysicsManager();
	gpEventManager = new EventManager();
	gpSceneManager = new SceneManager();
	bool flag = true;
	//gpObjectFactory->LoadLevelFromTxt("scene1");
	//gpObjectFactory->LoadLevelFromJson("test");
	//gpObjectFactory->LoadScript("scene1");
	gpProgram = new Program(w, h);
	gpProgram->Init();
	//program->resize(w, h);

	// Game loop
	while (true == appIsRunning)
	{
		gpSceneManager->Update();
		gpFrameController->FramStart();
		gpInputManager->Update();
		if (!gpProgram->pause) {
					
			gpEventManager->Update(gpFrameController->DeltaTime());
			gpPhysicsManager->Update(gpFrameController->DeltaTime());
		
		}
		
		if (TEST)
		{
			gpProgram->draw();
			SDL_GL_SwapWindow(pWindow);
		}
		if (!TEST)
		{
			//Draw all gameObjects		
			SDL_FillRect(pWinSurface, NULL, 0);

			SDL_Rect re;
			re.h = 0;
			re.w = 0;
			for (auto go : gpGameObjectManager->GameObjects)
			{
				go->Update();
				if (go->GetComponent(TRANSFORM) != nullptr &&go->GetComponent(SPRITE))
				{
					Sprite* pS = static_cast<Sprite*> (go->GetComponent(SPRITE));
					Transform* pT = static_cast<Transform*> (go->GetComponent(TRANSFORM));
					re.x = pT->mPos.x;
					re.y = pT->mPos.y;
					SDL_BlitSurface(pS->sprite, NULL, pWinSurface, &re);
				}
			}
			SDL_UpdateWindowSurface(pWindow);
		}

		
		gpGameObjectManager->Update();
		if (gpInputManager->IsTriggered(SDL_SCANCODE_ESCAPE))
		{
			appIsRunning = false;
		}

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type) {
			case SDL_QUIT:
				appIsRunning = false;
				break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					gpProgram->resize(e.window.data1, e.window.data2);
				break;
			}
		}
		gpFrameController->FramEnd();
	}

	delete(gpFrameController);
	delete(gpInputManager);
	delete(gpGameObjectManager);
	delete(gpResourceManager);
	delete(gpObjectFactory);
	delete(gpComponentMap);
	delete gpCollisionManager;
	delete gpPhysicsManager;
	delete gpEventManager;
	delete gpSceneManager;
	// Close and destroy the window
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(pWindow);
	
	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}