#include "../Waypoint.h"
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

Waypoint::Waypoint(const Vec2D& coords) : m_coords(coords), m_gradient({ 0,0 }) {}
Waypoint::Waypoint(const Vec2D& coords, const Vec2D& gradient) : m_coords(coords), m_gradient(gradient) {}

const float Waypoint::GetHeading() const {
	return atan2(m_gradient.GetY(), m_gradient.GetX());
}

const float Waypoint::GetHeadingInDegrees() const {
	return 180/M_PI * atan2(m_gradient.GetY(), m_gradient.GetX());
}
