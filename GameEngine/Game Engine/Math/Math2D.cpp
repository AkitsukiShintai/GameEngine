/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Math2D.cpp>
Purpose:<implement all functions declared in Math2D.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Math2D.h"
#include"Vector2D.h"
#include"../Component/Shape.h"

#define EPSILON 0.000001
/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(const glm::vec2& point, glm::vec2&  circle, float Radius)
{
	float dis = Vector2DSquareDistance(point, circle);
	if (dis > Radius*Radius)
	{
		return 0;
	}
	return 1;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(const glm::vec2& point, glm::vec2&  rect, float Width, float Height)
{
	float dx = fabs(rect.x - point.x);
	float dy = fabs(rect.y - point.y);
	if ((dx - Width / 2.0f) < EPSILON && (dy - Height / 2.0f) < EPSILON)
	{
		return 1;
	}
	return 0;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(const glm::vec2& circle0, float Radius0, const glm::vec2& circle1, float Radius1)
{
	float dis = Vector2DDistance(circle0, circle1);
	if (Radius1 + Radius0 < dis)
	{
		return 0;
	}
	return 1;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(const glm::vec2& pRect0, float Width0, float Height0, const glm::vec2& pRect1, float Width1, float Height1)
{
	float x0 = pRect0.x - Width0 / 2.0f; // R0 Left
	float x1 = pRect0.x + Width0 / 2.0f; // R0 Right
	float y0 = pRect0.y - Height0 / 2.0f;//R0 Botton
	float y1 = pRect0.y + Height0 / 2.0f;//R0 Top
	float x2 = pRect1.x - Width1 / 2.0f;//R1Left
	float x3 = pRect1.x + Width1 / 2.0f;// R1 Right
	float y2 = pRect1.y - Height1 / 2.0f;// R1 Botton
	float y3 = pRect1.y + Height1 / 2.0f;// R1 Top
	if (x0 > x3 || x1< x2 || y0>y3 || y1 < y2 || x0 == x3 || x1== x2 || y0==y3 || y1 == y2)
	{
		return 0;
	}
	return 1;
}

/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(const glm::vec2& point, LineSegment2D *LS) {
	float a = glm::dot((LS->mN), point) - LS->mNdotP0;
	if (a < EPSILON)
	{
		return 0;
	}
	else
	{
		return a;
	}
}

/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(const glm::vec2& Ps, const glm::vec2& Pe, LineSegment2D *LS, glm::vec2 * Pi) {
	return 1.0f;
	float	t;
	glm::vec2 v = Pe - Ps;
	t = (LS->mNdotP0 - glm::dot(LS->mN, Ps)) / glm::dot(LS->mN, v);

	if (t < 1 && t >0)
	{
		v = v * t;
		*Pi = Ps + v;
		//test if Pi is on the segment
		glm::vec2 i;
		glm::vec2 r;
		i = *Pi - LS->mP0;
		r = *Pi - LS->mP1;
		float dot = glm::dot(r, i);
		if (dot > 0)//ti is not on the segment
		{
			return -1.0f;
		}

		return t;
	}
	else
	{
		return -1.0f;
	}
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(const glm::vec2& Ps, const glm::vec2& Pe, float Radius, LineSegment2D *LS, glm::vec2 *Pi) {
	float	t;
	glm::vec2 v;
	v = Pe - Ps;

	float f = glm::dot(LS->mN, Ps) - LS->mNdotP0;

	float newNP0;

	if (f > 0.0f) {/*outside*/
		newNP0 = LS->mNdotP0 + Radius;

	}
	else if (f < 0.0f)/*inside*/
	{
		newNP0 = LS->mNdotP0 - Radius;
	}

	float NV = glm::dot(LS->mN, v);
	if (fabsf(NV - 0.0f) < EPSILON)
	{
		return -1.0f;
	}
	t = (newNP0 - glm::dot(LS->mN, Ps)) / NV;

	if (t >= 0.0f && t <= 1.0f)
	{
		v = v * t;
		*Pi = Ps + v;
		//test if Pi is on the segment
		glm::vec2  i;
		glm::vec2  r;
		i = *Pi - LS->mP0;
		r = *Pi - LS->mP1;
		float dot = glm::dot(r, i);
		if (dot > 0.0f)//ti is not on the segment
		{
			Pi = NULL;
			return -1.0f;
		}

		return t;
	}
	else
	{
		return -1.0f;
	}

}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(const glm::vec2& Ps, const glm::vec2& Pe, LineSegment2D *LS, glm::vec2 *Pi, glm::vec2 *R) {

	return 1.0f;
	float t;
	t = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);
	if (1.0f > t && t > 0)
	{
		glm::vec2 i;
		glm::vec2 r;
		i = Pe - *Pi;
		float dot = glm::dot(i, LS->mN);
		r = LS->mN * 2.0f*dot;
		r = i - r;
		*R = *Pi + r;
		*R = *R + *Pi;
		return t;
	}
	else
	{
		return -1.0f;
	}
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(const glm::vec2& Ps, const glm::vec2&Pe, float Radius, LineSegment2D *LS, glm::vec2 *Pi, glm::vec2 *R) {
	float t;
	t = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);
	if (t > 0.0f && t < 1.0f) /*intersection*/
	{
		glm::vec2 i; //i=Pe - Pi
		glm::vec2 r;//n * 2(i*n)
		i = Pe - *Pi;
		float dot = glm::dot(i, LS->mN);// i*n
		r = LS->mN * 2.0f*dot;
		//Vector2DScale(&r, &LS->mN, 2.0f*dot); //n * 2(i*n)
		*R = i - r;
		//Vector2DSub(R, &i, &r);//R = i -2(i*n)n
		//Vector2DAdd(Pe, Pi, &R);// b' = bi  + r
		//Vector2DNormalize();
		return t;
	}
	else
	{
		return -1.0f;
	}
}



/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(const glm::vec2& Ps, const glm::vec2& Pe, const glm::vec2& Center, float Radius, glm::vec2 *Pi) {

	glm::vec2 v;
	//Vector2D m;
	glm::vec2 PsC;
	PsC = Center - Ps;
	//Vector2DSub(&PsC, Center, Ps);
	v = Pe - Ps;
	//Vector2DSub(&v, Pe, Ps);//v = pe -ps
	float delta;
	float a = glm::dot(v, v);//a= v *v
	float b = -2.0f* glm::dot(PsC, v);//b = -2PsC*v
	float c = glm::dot(PsC, PsC) - Radius * Radius; //c = PsC*PsC - r*r
	delta = b * b - 4.0f * a*c;//delta = b^2 -4ac

	if (delta <= 0.0f)
	{
		return -1.0f;
	}

	float sqrDelta = sqrtf(delta);
	float t0 = (-b + sqrDelta) / (2.0f*a);
	float t1 = (-b - sqrDelta) / (2.0f*a);
	float ti = fminf(t0, t1);

	if (ti > 0.0f && ti < 1.0f)
	{
		*Pi = v * ti;
		//Vector2DScale(Pi, &v, ti);
		*Pi = *Pi + Ps;
		//Vector2DAdd(Pi, Pi, Ps);

		//test if Pi is on the segment
		glm::vec2 i;
		glm::vec2 r;
		i = *Pi - Ps;
		//Vector2DSub(&i, Pi, Ps);
		r = *Pi - Pe;
		//Vector2DSub(&r, Pi, Pe);
		float dot = glm::dot(r, i);
		if (dot > 0.0f)//Pi is not on the segment
		{
			Pi = NULL;
			return -1.0f;
		}
		return ti;

	}
	else
	{
		return -1.0f;
	}
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center
	- Center0e:		The ending position of the animated circle's center
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(const glm::vec2& Center0s, const glm::vec2& Center0e, float Radius0, const glm::vec2&Center1, float Radius1, glm::vec2 *Pi) {
	float t = AnimatedPointToStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi);
	return t;
}

/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(const glm::vec2& Ps, const glm::vec2&Pe, const glm::vec2&Center, float Radius, glm::vec2 *Pi, glm::vec2 *R) {
	float t = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);
	if (t >= 0.0f && t <= 1.0f)
	{
		glm::vec2 n;
		glm::vec2 m;
		glm::vec2 r;
		n = *Pi - Center;
		//Vector2DSub(&n, Pi, Center);
		n = glm::normalize(n);
		//Vector2DScale(&n, &n, 1.0f / Vector2DLength(&n));//n normalized
		m = Ps - *Pi;
		//Vector2DSub(&m, Ps, Pi);
		r = n * 2.0f *glm::dot(m, n);
		//Vector2DScale(&r, &n, 2.0f * Vector2DDotProduct(&m, &n));//2(m¡¤n)n
		*R = r - m;
		//Vector2DSub(R, &r, &m);//r = 2(m¡¤n)n-m
		//Vector2DNormalize(R, R);
		n = Pe - *Pi;
		//Vector2DSub(&n, Pe, Pi);//PiBe
		float nL = n.length();
		float mL = m.length();
		*R = *R * nL / mL;
		//Vector2DScale(R, R, Vector2DLength(&n) / Vector2DLength(&m));

		return t;

	}
	else
	{
		return -1.0f;
	}


}


float ReflectAnimatedCircleOnStaticCircle(const glm::vec2& Center0s, const glm::vec2& Center0e, float Radius0, const glm::vec2& Center1, float Radius1, glm::vec2 *Pi, glm::vec2 *R) {
	float t = ReflectAnimatedPointOnStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi, R);
	return t;
}



//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------




/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
bool StaticPointToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	glm::vec2 a(pos1X, pos1Y);
	glm::vec2 b(pos2X, pos2Y);
	ShapeCircle* p = static_cast<ShapeCircle*>(Shape2);
	if (StaticPointToStaticCircle(a, b, p->mRadius) == 1) {

		Contact* pNewContact = new Contact();
		pNewContact->mpBody[0] = Shape1->mBody;
		pNewContact->mpBody[2] = Shape2->mBody;
		contacts->push_back(pNewContact);
		return true;
	}
	return false;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
bool StaticPointToStaticRect(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	glm::vec2 a(pos1X, pos1Y);
	glm::vec2 b(pos2X, pos2Y);
	ShapeAABB* p = static_cast<ShapeAABB*>(Shape2);

	if (StaticPointToStaticRect(a, b, p->mRight - p->mLeft, p->mTop - p->mBottom) == 1) {

		Contact* pNewContact = new Contact();
		pNewContact->mpBody[0] = Shape1->mBody;
		pNewContact->mpBody[2] = Shape2->mBody;
		contacts->push_back(pNewContact);
		return true;
	}
	return false;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
bool StaticCircleToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	glm::vec2 a(pos1X, pos1Y);
	glm::vec2 b(pos2X, pos2Y);
	ShapeCircle* p1 = static_cast<ShapeCircle*>(Shape1);
	ShapeCircle* p2 = static_cast<ShapeCircle*>(Shape2);

	if (StaticCircleToStaticCircle(a, p1->mRadius, b, p2->mRadius) == true) {

		Contact* pNewContact = new Contact();
		pNewContact->mpBody[0] = Shape1->mBody;
		pNewContact->mpBody[1] = Shape2->mBody;
		contacts->push_back(pNewContact);
		return true;
	}
	return false;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
bool StaticRectToStaticRect(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	
	ShapeAABB* p1 = static_cast<ShapeAABB*>(Shape1);
	ShapeAABB* p2 = static_cast<ShapeAABB*>(Shape2);
	glm::vec2 a(pos1X +(p1->mLeft+p1->mRight)/2.0f , pos1Y+(p1->mTop + p1->mBottom) / 2.0f);
	glm::vec2 b(pos2X + (p2->mLeft + p2->mRight) / 2.0f, pos2Y+(p2->mTop + p2->mBottom) / 2.0f);
	if (StaticRectToStaticRect(a, p1->mRight - p1->mLeft, p1->mTop - p1->mBottom, b, p2->mRight - p2->mLeft, p2->mTop - p2->mBottom) == 1) {
		Contact* pNewContact = new Contact();
 		pNewContact->mpBody[0] = Shape1->mBody;
		pNewContact->mpBody[1] = Shape2->mBody;
		contacts->push_back(pNewContact);	
		return true;
	}
	return false;
}


bool StaticCircleToStaticRect(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	
	glm::vec2 a(pos1X, pos1Y);
	glm::vec2 b(pos2X, pos2Y);
	ShapeCircle* p1 = static_cast<ShapeCircle*>(Shape1);
	ShapeAABB* p2 = static_cast<ShapeAABB*>(Shape2);
	if (StaticRectToStaticRect(a, p1->mRadius*2.0f , p1->mRadius*2.0f, b, p2->mRight - p2->mLeft, p2->mTop - p2->mBottom) == true) {
		Contact* pNewContact = new Contact();
		pNewContact->mpBody[0] = Shape1->mBody;
		pNewContact->mpBody[1] = Shape2->mBody;
		contacts->push_back(pNewContact);
		return true;
	}
	return false;
}
bool StaticRectToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {

	return StaticCircleToStaticRect(Shape2, pos2X, pos2Y, Shape1, pos1X, pos1Y,  contacts);

}

/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
bool StaticPointToStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	
	return false;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool AnimatedPointToStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool AnimatedCircleToStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool ReflectAnimatedPointOnStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool ReflectAnimatedCircleOnStaticLineSegment(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool AnimatedPointToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool ReflectAnimatedPointOnStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center
	- Center0e:		The ending position of the animated circle's center
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool AnimatedCircleToStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one

 - Parameters
	- Center0s:		The starting position of the animated circle's center
	- Center0e:		The ending position of the animated circle's center
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
bool ReflectAnimatedCircleOnStaticCircle(Shape* Shape1, float pos1X, float pos1Y, Shape *Shape2, float pos2X, float pos2Y, std::list<Contact*>* contacts) {
	return false;
}





