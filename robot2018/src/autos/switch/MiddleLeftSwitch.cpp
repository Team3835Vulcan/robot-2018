#include "MiddleLeftSwitch.h"
#include <path/CatmullRom.h>
#include <Constants.h>
#include <Commands/Chassis/DriveTrajectory.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleLeftSwitch::MiddleLeftSwitch() {
	Path p({ {{0,0}}, {{-1.8, 3.15}} });
	CatmullRom pathMaker(true, 90, 180);
	p.SetGradients(pathMaker);
	p.Generate();

	Trajectory t(p, DEFAULT_CONFIG);
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DriveTrajectory(std::move(t)));
	AddSequential(new MoveBelt(Conveyor::SIDE::RIGHT));
	AddSequential(new RotorAction(Collector::ROTOR_POS::UP));
}
