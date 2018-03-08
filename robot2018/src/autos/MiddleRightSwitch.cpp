#include "MiddleRightSwitch.h"
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

MiddleRightSwitch::MiddleRightSwitch() {
	Path p({{ 5.02,0.487 }, { 5.04, 1.407 }, { 5.56, 1.807 }, { 5.84, 3.1 }, { 6.88,3.23 }});
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DrivePath(std::move(p),0));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
}
