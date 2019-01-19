/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<PhysicsManager.h>
Purpose:<declare PhysicsManager class. For determining game objects collision>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include"EventManager.h"
#include"Math/q_tree.h"

class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();
	void Update(float framTime);
public:
	Q_TREE::Quadtree<GameObject*> a;
};