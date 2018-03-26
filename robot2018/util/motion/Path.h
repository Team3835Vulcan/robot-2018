#pragma once

#include <vector>
#include "Spline.h"

class Path
{
private:
	std::vector<Waypoint> m_waypoints;
	std::vector<Spline> m_splines;
	double m_length;
	double m_dt;

public:
	Path(const std::vector<Vec2D>& waypoints);
	Path(const std::vector<Vec2D>& waypoints, double dt);

	double GetDT() const;

	const std::vector<Waypoint> GetCoords() const;
	const std::vector<Waypoint>& GetWaypoints() const;
	
	const Waypoint GetWaypoint(double d);

	void AddSpline(const Spline& s);
	const double GetLength();
};

void GenerateCatmullRom(Path& p);
void GenerateCatmullRom(Path& p, float heading0);
void GenerateCatmullRom(Path& p, float heading0, float headingf);
