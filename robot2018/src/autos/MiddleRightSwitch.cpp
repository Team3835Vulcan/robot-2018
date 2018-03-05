#include "MiddleRightSwitch.h"
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleRightSwitch::MiddleRightSwitch() {
	Path p({ {5.02, 0.167},{5.12,0.907},{5.54,1.907},{6.64,3.3} });
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddParallel(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddSequential(new DrivePath(std::move(p),0));
	AddSequential(new Turn(30));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
}
