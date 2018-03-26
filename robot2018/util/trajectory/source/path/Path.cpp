#include <path/Path.h>
#include <path/IPathMaker.h>

Path::Path(const std::vector<Waypoint>& waypoints, double dt) : 
	m_waypoints({}), 
	m_splines({}),
	m_length(-1), 
	m_dt(dt) 
{
	m_waypoints.reserve(waypoints.size());
	for (std::size_t i = 0; i < waypoints.size(); ++i) {
		m_waypoints.emplace_back(Waypoint(waypoints[i]));
	}	
}

const std::vector<Waypoint> Path::GetCoords() const {
	std::vector<Waypoint> coords;
	coords.reserve(m_splines.size()/m_dt);

	for (std::size_t i = 0; i < m_splines.size(); i++) {
		for (float j = 0; j <= 1; j+=m_dt) {
			coords.push_back(m_splines[i].GetPoint(j));
		}
	}
	return coords;
}

const std::vector<Waypoint>& Path::GetWaypoints() const{
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

const double Path::GetLength() {
	if (m_length <= 0) {
		double length = 0;
		for (auto& spline : m_splines) {
			length += spline.GetLength();
		}
		m_length = length;
	}
	return m_length;
}

void Path::SetGradients(IPathMaker& pathMaker) {
	pathMaker(m_waypoints);
}
void Path::Generate() {
	m_splines.clear();

	const auto& points = GetWaypoints();
	for (std::size_t i = 0; i < points.size() - 1; i++) {
		m_splines.push_back({ points[i].m_coords, points[i].m_gradient, 
			points[i + 1].m_coords, points[i + 1].m_gradient });
	}

	GetLength();
}