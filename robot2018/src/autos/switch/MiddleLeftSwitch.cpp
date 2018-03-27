#include "MiddleLeftSwitch.h"
#include <path/CatmullRom.h>
#include <Constants.h>
#include <Commands/Chassis/DriveTrajectory.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleLeftSwitch::MiddleLeftSwitch() {
	Path p({ {{0,0}}, {{-1.6, 2.9}} });
	CatmullRom pathMaker(true, 90, 180);
	p.SetGradients(pathMaker);
	p.Generate();

	MotionProfileConfig config = DEFAULT_CONFIG;
	config.maxVel = 2.3;
	config.maxAcc = 1.25;
	Trajectory t(p, config);
	AddSequential(new DriveTrajectory(std::move(t)));
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new MoveBelt(Conveyor::SIDE::RIGHT));
	AddSequential(new RotorAction(Collector::ROTOR_POS::UP));
}
