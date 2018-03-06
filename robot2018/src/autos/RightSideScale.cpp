#include "RightSideScale.h"
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>
#include <Commands/Elevator/ElevCtrl.h>

RightSideScale::RightSideScale() {
	Path p ({ { 0,0 },{ 0.12,3.5 }, {0.3,5.1},{ 0.5,8.35 } });
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new ElevCtrl(ElevCtrl::ELEVPOS::UP));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DrivePath(std::move(p),90));
	AddSequential(new MoveBelt(Conveyor::SIDE::LEFT));
	AddSequential(new ElevCtrl(ElevCtrl::ELEVPOS::DOWN));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new RotorAction(Collector::ROTOR_POS::UP));
}
