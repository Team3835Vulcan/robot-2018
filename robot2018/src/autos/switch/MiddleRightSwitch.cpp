#include "MiddleRightSwitch.h"
#include <path/CatmullRom.h>
#include <Constants.h>
#include <Commands/Chassis/DriveTrajectory.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleRightSwitch::MiddleRightSwitch() {
	Path p({ {{0,0}}, {{1.8, 2.9}} });
	CatmullRom pathMaker(true, 90, 0);
	p.SetGradients(pathMaker);
	p.Generate();

	MotionProfileConfig config = DEFAULT_CONFIG;
	config.maxVel = 2.6;
	config.maxAcc = 1.4;
	Trajectory t(p, config);
	AddSequential(new DriveTrajectory(std::move(t)));
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
	AddSequential(new RotorAction(Collector::ROTOR_POS::UP));

}
