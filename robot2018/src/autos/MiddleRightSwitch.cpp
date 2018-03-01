#include "MiddleRightSwitch.h"
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleRightSwitch::MiddleRightSwitch() {
	Path p({ {4.82, 0.167},{4.76,1.907},{5.54,3.107},{6.64,3.407} });
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddParallel(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddSequential(new DrivePath(std::move(p),0));
	AddSequential(new Turn(30));
	AddSequential(new MoveBelt(Conveyor::SIDE::RIGHT));
}
