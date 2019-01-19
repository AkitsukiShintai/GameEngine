#pragma once
/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Math2D.h>
Purpose:<header of Math2D.c. Implement some static collision in 2D>
Language:<C>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_1_Part1>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<9/15/2018>
History:
<10/1/2018 Wang Zhongqiu CS529_w.zhongqiu_2_Part1>
define functions AnimatedCircleToStaticLineSegment, AnimatedPointToStaticLineSegment,
ReflectAnimatedCircleToStaticLineSegment and ReflectAnimatedCircleToStaticLineSegment.
-End Header --------------------------------------------------------*/
#ifndef MATH2D_H
#define MATH2D_H

#include"../Component/Shape.h"
#include"../CollisionManager.h"
#include "LineSegment2D.h"
#include<list>
////////////////////
// From Project 1 //
////////////////////

class Contact;
/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
bool StaticPointToStaticCircle(Shape* Shape1, float pos1X ,float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
bool StaticPointToStaticRect(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
bool StaticCircleToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
bool StaticRectToStaticRect(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


bool StaticCircleToStaticRect(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);

bool StaticRectToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);
//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line


*/
bool StaticPointToStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function checks whether an animated point is colliding with a line segment

 
*/
bool AnimatedPointToStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function checks whether an animated circle is colliding with a line segment


*/
bool AnimatedCircleToStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line

*/
bool ReflectAnimatedPointOnStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line
*/
bool ReflectAnimatedCircleOnStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function checks whether an animated point is colliding with a static circle

*/
bool AnimatedPointToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle
*/
bool ReflectAnimatedPointOnStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function checks whether an animated circle is colliding with a static circle
*/
bool AnimatedCircleToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one
*/
bool ReflectAnimatedCircleOnStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts);


#endif