#include "MiddleLeftSwitch.h"
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleLeftSwitch::MiddleLeftSwitch() {
	Path p({ {5.02, 0.487}, {4.88, 1.407}, {4, 2.347}, {3.64, 3.027}, {2.72, 3.107} });
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DrivePath(std::move(p),0));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
}
