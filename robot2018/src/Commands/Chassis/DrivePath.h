#ifndef DrivePath_H
#define DrivePath_H

#include <memory>
#include "Commands/Command.h"
#include <Subsystems/Chassis/Controllers/TrajectoryController.h>

/*
 * Drive an arbitrary path received as input.
 * Path is generated according to initial angle.
 * Optional parameter for final heading
 */

class DrivePath : public frc::Command {
private:
	Path m_path; //path to drive
	double m_headingf; //final heading
	TrajectoryController m_controller;
public:
	DrivePath(const Path& path, double headingf = 999);
	DrivePath(const Path&& path, double headingf = 999);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DrivePath_H
