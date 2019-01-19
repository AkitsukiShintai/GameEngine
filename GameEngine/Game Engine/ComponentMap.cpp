/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ComponentMap.cpp>
Purpose:<implement all functions of class ComponentMap>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"ComponentMap.h"

ComponentMap::ComponentMap(){

	InitializeMap();
}


void ComponentMap::InitializeMap(){
std::string t[] = {"number","ui","animation", "body","updown","sprite","transform" ,"controller" };
	for (size_t i = 0; i < MAX_COUNT; ++i)
	{
		ComponentTypeMap[t[i]] = static_cast<COMPONENT_TYPE>(i);
	}
	std::string t1[] = {"game_over", "enemy3","enemy2","start_menu","hell","blood","electric_shield","bullet","enemy1", "wall","ground","player_script" };

	for (size_t i = 0; i < SCRITP_NUM; ++i)
	{
		ScriptTypeMap[t1[i]] = static_cast<ScriptType>(i);
	}
}
