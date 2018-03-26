#pragma once

#include <vector>
#include "Spline.h"

class IPathMaker;

class Path
{
private:
	std::vector<Waypoint> m_waypoints;
	std::vector<Spline> m_splines;
	double m_length;
	double m_dt;

public:
	Path(const std::vector<Waypoint>& waypoints, double dt = 1e-3);

	const std::vector<Waypoint> GetCoords() const;
	const std::vector<Waypoint>& GetWaypoints() const;
	
	const Waypoint GetWaypoint(double d);
	
	//supply a pathmaker object to set gradient values across the waypoints
	void SetGradients(IPathMaker& pathMaker);

	//generates the splines in the path according to the gradients specified.
	//IT IS THE USER'S RESPONSIBILITY TO SUPPLY THE GRADIENTS.
	void Generate();

	const double GetLength();
};
