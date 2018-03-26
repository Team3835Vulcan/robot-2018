#pragma once

#include "Waypoint.h"

/*
Spline defines a 2d parametric curve of a hermite cubic polynomial
between two distinct points
*/

class Spline
{
private:
	Vec2D m_p0, m_g0, m_p1, m_g1;
	double m_dt;
	double m_length;
public:
	Spline(Vec2D p0, Vec2D g0, Vec2D p1, Vec2D g1, double dt = 1e-3);

	//get a 2d point on the spline
	const Waypoint GetPoint(double t) const;
	const Waypoint GetPointByDist(double d);
	const double GetLength();
};
