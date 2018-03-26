#include <path/Waypoint.h>
#define _USE_MATH_DEFINES
#include <cmath>

Vec2D::Vec2D() : m_x(0), m_y(0) {}
Vec2D::Vec2D(double x, double y) : m_x(x), m_y(y) {}

double Vec2D::GetX() const {
	return m_x;
}
double Vec2D::GetY() const {
	return m_y;
}

Vec2D& Vec2D::operator+=(const Vec2D& vc){
	m_x += vc.m_x;
	m_y += vc.m_y;

	return *this;
}
Vec2D& Vec2D::operator*=(const double k) {
	m_x *= k;
	m_y *= k;

	return *this;
}

Vec2D operator+(Vec2D lv, const Vec2D& rv) {
	lv += rv;
	return lv;
}
Vec2D operator-(Vec2D lv, const Vec2D& rv) {
	lv += -1 * rv;
	return lv;
}
Vec2D operator*(double k, Vec2D rv) {
	rv *= k;
	return rv;
}
const bool Vec2D::operator==(const Vec2D& rh) {
	return m_x == rh.m_x && m_y == rh.m_y;
}

Waypoint::Waypoint(const Vec2D& coords, const Vec2D& gradient) :
	m_coords(coords),
	m_gradient(gradient) {}
Waypoint::Waypoint(const Vec2D& coords, double heading) :
	m_coords(coords),
	m_gradient({ std::cos(M_PI/180*heading), std::sin(M_PI/180*heading) }) {}

const double Waypoint::GetHeading() const {
	return std::atan2(m_gradient.GetY(), m_gradient.GetX());
}

const double Waypoint::GetHeadingInDegrees() const {
	double res = 180/M_PI * std::atan2(m_gradient.GetY(), m_gradient.GetX());
	if (res < 0)
		res += 360;
	return res;
}
