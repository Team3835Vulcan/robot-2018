#include <path/TankFitter.h>
#include <cmath>
#include "Trajectory.h"

TankFitter::TankFitter(double wheelbase) : m_wheelbase(wheelbase) { }

void TankFitter::Fit(const Trajectory& traj) {
	std::vector<Waypoint> leftWP;
	std::vector<Waypoint> rightWP;

	const auto& waypoints = traj.GetWaypoints();

	for (const auto& wp : waypoints) {
		double heading = wp.GetHeading();
		double headingDeg = wp.GetHeadingInDegrees();

		const auto& coords = wp.m_coords;

		double w = m_wheelbase / 2;
		double leftX = coords.GetX() - w * std::sin(heading);
		double leftY = coords.GetY() + w * std::cos(heading);

		double rightX = coords.GetX() + w * std::sin(heading);
		double rightY = coords.GetY() - w * std::cos(heading);
	
		leftWP.push_back({ {leftX, leftY}, headingDeg });
		rightWP.push_back({ {rightX, rightY}, headingDeg });
	}

	Path lp(leftWP);
	Path rp(rightWP);

	lp.Generate();
	rp.Generate();

	bool isReversed = traj.IsReversed();

	m_left = new Trajectory(lp, traj.GetConfig(), 0, isReversed);
	m_right = new Trajectory(rp, traj.GetConfig(), 0 , isReversed);

	double leftTime = m_left->GetProfile().GetTime();
	double rightTime = m_right->GetProfile().GetTime();

	if (leftTime > rightTime) {
		delete m_right;
		m_right = new Trajectory(rp, traj.GetConfig(), leftTime, isReversed);
	}
	else {
		delete m_left;
		m_left = new Trajectory(lp, traj.GetConfig(), rightTime, isReversed);
	}
}
const Trajectory& TankFitter::GetLeft() const {
	return *m_left;
}
const Trajectory& TankFitter::GetRight() const {
	return *m_right;
}


