#include <path/CatmullRom.h>
#include <path/Waypoint.h>
#define M_PI 3.141592653589
#include <cmath>


CatmullRom::CatmullRom(bool cep, double heading0, double headingf) :
	m_controlEndPoints(cep),
	m_heading0(heading0),
	m_headingf(headingf) {}

void CatmullRom::operator() (std::vector<Waypoint>& waypoints) {
	int endIndex = waypoints.size() - 1;
	if (m_controlEndPoints) {
		waypoints[0].m_gradient = 
			{ std::cos(m_heading0 * M_PI / 180), std::sin(m_heading0 * M_PI / 180) };
		waypoints[endIndex].m_gradient =	
			{ std::cos(m_headingf * M_PI / 180), std::sin(m_headingf * M_PI / 180) };
	}
	else {
		waypoints[0].m_gradient = 0.5 * (waypoints[1].m_coords - waypoints[0].m_coords);
		waypoints[endIndex].m_gradient = 0.5 * (waypoints[endIndex].m_coords - waypoints[endIndex - 1].m_coords);
	}
	for (std::size_t i = 1; i < endIndex; i++) {
		waypoints[i].m_gradient = 0.5 * (waypoints[i + 1].m_coords - waypoints[i - 1].m_coords);
	}

}