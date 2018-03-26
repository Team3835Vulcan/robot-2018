#include "MiddleLeftSwitch.h"
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleLeftSwitch::MiddleLeftSwitch() {
	Path p({ {4.92, 0.507}, {4.86, 1.2}, {3.96, 1.95}, {3.8, 3.1}, {3.5, 3.1}});
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DrivePath(std::move(p),180));
	AddSequential(new MoveBelt(Conveyor::SIDE::RIGHT));
}
