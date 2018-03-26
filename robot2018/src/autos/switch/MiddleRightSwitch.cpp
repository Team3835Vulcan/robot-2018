#include "MiddleRightSwitch.h"
#include <path/CatmullRom.h>
#include <Constants.h>
#include <Commands/Chassis/DriveTrajectory.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleRightSwitch::MiddleRightSwitch() {
	Path p({ {{0,0}}, {{1.85, 2.65}} });
	CatmullRom pathMaker(true, 90, 0);
	p.SetGradients(pathMaker);
	p.Generate();

	Trajectory t(p, DEFAULT_CONFIG);
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DriveTrajectory(std::move(t)));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
	AddSequential(new RotorAction(Collector::ROTOR_POS::UP));

}
