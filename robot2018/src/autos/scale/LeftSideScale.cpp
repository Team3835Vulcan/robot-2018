#include "LeftSideScale.h"
#include <path/CatmullRom.h>
#include <Constants.h>
#include <Commands/Chassis/DriveTrajectory.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>
#include <Commands/Elevator/ElevCtrl.h>

LeftSideScale::LeftSideScale() {
	Path p ({ {{ 0,0 }} ,{{ -0.12,3.5 }}, {{-0.3,5.1}}, {{ -0.5,7.8 }} });
	CatmullRom pathMaker(true, 90, 90);
	p.SetGradients(pathMaker);
	p.Generate();
	MotionProfileConfig config = DEFAULT_CONFIG;
	config.maxAcc = 1;

	Trajectory t(p, config);
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new ElevCtrl(ElevCtrl::ELEVPOS::UP));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DriveTrajectory(std::move(t)));
	AddSequential(new MoveBelt(Conveyor::SIDE::RIGHT));
	AddSequential(new ElevCtrl(ElevCtrl::ELEVPOS::DOWN));
}
