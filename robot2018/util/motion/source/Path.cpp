#define _USE_MATH_DEFINES
#include <cmath>
#include "../Path.h"

Path::Path(const std::vector<Vec2D>& waypoints) : m_waypoints({}), m_splines({}), m_length(-1), m_dt(1e-3) {
	m_waypoints.reserve(waypoints.size());
	for (std::size_t i = 0; i < waypoints.size(); ++i) {
		m_waypoints.emplace_back(Waypoint(waypoints[i]));
	}
}
Path::Path(const std::vector<Vec2D>& waypoints, double dt) : m_waypoints({}), m_splines({}), m_length(-1), m_dt(dt) {
	m_waypoints.reserve(waypoints.size());
	for (std::size_t i = 0; i < waypoints.size(); ++i) {
		m_waypoints.emplace_back(Waypoint(waypoints[i]));
	}
}

double Path::GetDT() const{
	return m_dt;
}

const std::vector<Waypoint> Path::GetCoords() const {
	std::vector<Waypoint> coords;
	coords.reserve(200);

	for (std::size_t i = 0; i < m_splines.size(); i++)
	{
		for (float j = 0; j <= 1; j+=m_dt)
		{
			coords.push_back(m_splines[i].GetPoint(j));
		}
	}

	return coords;
}

const std::vector<Waypoint>& Path::GetWaypoints() const {
	return m_waypoints;
}

const Waypoint Path::GetWaypoint(double d) {
	double prevLen = 0;
	double len = 0;
	auto& splines = m_splines;
	for (std::size_t i = 0; i < splines.size(); ++i) {
		len += splines[i].GetLength();
		if (d >= prevLen && d <= len) {
			return splines[i].GetPointByDist(d - prevLen);
		}
		prevLen = len;
	}
}

void Path::AddSpline(const Spline& s) {
	m_splines.emplace_back(s);
}

const double Path::GetLength() {
	if (m_length <= 0) {
		double length = 0;
		for (auto& spline : m_splines)
		{
			length += spline.GetLength();
		}
		m_length = length;
	}
	return m_length;
}

void GenerateCatmullRom(Path& p) {
	auto points = p.GetWaypoints();
	for (std::size_t i = 0; i < points.size(); i++)
	{
		if (i == 0) {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i].m_coords);
		}
		else if (i == points.size() - 1) {
			points[i].m_gradient = 0.5 * (points[i].m_coords - points[i-1].m_coords);
		}
		else {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i - 1].m_coords);
		}
	}
	for (std::size_t i = 0; i < points.size()-1; i++)
	{
		p.AddSpline(Spline(points[i].m_coords, points[i].m_gradient,
				points[i + 1].m_coords, points[i + 1].m_gradient, p.GetDT()));
	}

	p.GetLength();
}
void GenerateCatmullRom(Path& p, float heading0) {
	auto points = p.GetWaypoints();
	for (std::size_t i = 0; i < points.size(); i++)
	{
		if (i == 0) {
			float headingRad = M_PI / 180 * heading0;
			Vec2D heading = { {cos(headingRad)}, {sin(headingRad)} };
			points[i].m_gradient = heading;
		}
		else if (i == points.size() - 1) {
			points[i].m_gradient = 0.5 * (points[i].m_coords - points[i - 1].m_coords);
		}
		else {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i - 1].m_coords);
		}
	}
	for (std::size_t i = 0; i < points.size() - 1; i++)
	{
		p.AddSpline(Spline(points[i].m_coords, points[i].m_gradient,
				points[i + 1].m_coords, points[i + 1].m_gradient, p.GetDT()));
	}

	p.GetLength();
}
void GenerateCatmullRom(Path& p, float heading0, float headingf) {
	auto points = p.GetWaypoints();
	for (std::size_t i = 0; i < points.size(); i++)
	{
		if (i == 0) {
			float headingRad = M_PI / 180 * heading0;
			Vec2D heading = { { cos(headingRad) },{ sin(headingRad) } };
			points[i].m_gradient = heading;
		}
		else if (i == points.size() - 1) {
			float headingRad = M_PI / 180 * headingf;
			Vec2D heading = { { cos(headingRad) },{ sin(headingRad) } };
			points[i].m_gradient = heading;
		}
		else {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i - 1].m_coords);
		}
	}
	for (std::size_t i = 0; i < points.size() - 1; i++)
	{
		p.AddSpline(Spline(points[i].m_coords, points[i].m_gradient,
				points[i + 1].m_coords, points[i + 1].m_gradient, p.GetDT()));
	}

	p.GetLength();
}
