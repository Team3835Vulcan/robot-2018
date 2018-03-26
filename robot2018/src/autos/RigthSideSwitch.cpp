#include <autos/RightSideSwitch.h>
#include <Commands/Chassis/DriveStraight.h>
#include <Commands/Chassis/Turn.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>

RightSideSwitch::RightSideSwitch() {
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DriveStraight(4));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
}
