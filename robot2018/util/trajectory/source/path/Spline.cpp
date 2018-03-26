#include <path/Spline.h>
#include <cmath>

Spline::Spline(Vec2D p0, Vec2D g0, Vec2D p1, Vec2D g1, double dt) :
	m_p0(p0), m_g0(g0), m_p1(p1), m_g1(g1), m_dt(dt), m_length(-1) {
	GetLength();
}

const Waypoint Spline::GetPoint(double t) const {
	double tt = t * t;
	double ttt = tt * t;

	double h0 = 2*ttt - 3*tt + 1;
	double h1 = ttt - 2 * tt + t;
	double h2 = -2 * ttt + 3*tt;
	double h3 = ttt - tt;

	Vec2D coords = h0 * m_p0 + h1 * m_g0 + h2 * m_p1 + h3 * m_g1;

	double dh0 = 6*tt - 6*t;
	double dh1 = 3*tt - 4*t + 1;
	double dh2 = -6*tt + 6*t;
	double dh3 = 3*tt - 2*t;

	Vec2D gradient = dh0 * m_p0 + dh1 * m_g0 + dh2 * m_p1 + dh3 * m_g1;

	return{ coords, gradient };
}

const Waypoint Spline::GetPointByDist(double d) {
	return GetPoint(d / m_length);
}

const double Spline::GetLength() {
	if (m_length < 0) {
		double length = 0;
		for (double i = 0; i <= 1; i += m_dt)
		{
			auto point = GetPoint(i);
			double dx = point.m_gradient.GetX();
			double dy = point.m_gradient.GetY();
			length += sqrt((dx*dx) + (dy*dy)) * m_dt;
		}
		m_length = length;
	}
	return m_length;
}
