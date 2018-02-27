#include "LeftSideSwitch.h"
#include <Commands/Chassis/DriveStraight.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

LeftSideSwitch::LeftSideSwitch() {
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddSequential(new DriveStraight(4.15));
	AddSequential(new Turn(-30));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
}
