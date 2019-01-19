/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ComponentMap.h>
Purpose:<declare ComponentMap class. For stroaging serializition information>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
-End Header --------------------------------------------------------*/
#pragma once
#include<unordered_map>
#include"Component/Component.h"
#include"Script/Script.h"
#ifndef COMPONENT_MAP_H
#define COMPONENT_MAP_H


class ComponentMap {
public:
	ComponentMap();
	 std::unordered_map<std::string, COMPONENT_TYPE> ComponentTypeMap;
	 std::unordered_map<std::string, ScriptType> ScriptTypeMap;
	 void InitializeMap();
};


#endif // !COMPONENT_MAP_H
