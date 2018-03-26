#pragma once

#include <vector>

/*
interface for classes which are to be passed
to a path object for gradienizing the waypoints
*/

class Waypoint;

class IPathMaker {
public:
	
	//this function should apply a gradient across
	//all the waypoints in the path
	virtual void operator() (std::vector<Waypoint>& waypoints) = 0;

	virtual ~IPathMaker() {}
};