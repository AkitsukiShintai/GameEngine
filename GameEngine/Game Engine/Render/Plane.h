/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Plane.h>
Purpose:<declared class Plane.h, for get vertex buffer of plane>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include <vector>
#include"glm.hpp"
class Plane  {
  public:
    Plane();
  public:
    std::vector<glm::vec4> vertices,
                           normals;
   std::vector<unsigned int[3]> faces;
};
