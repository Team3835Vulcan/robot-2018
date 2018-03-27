#include "LeftRightScale.h"
#include <path/CatmullRom.h>
#include <Constants.h>
#include <Commands/Chassis/DriveTrajectory.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/SwitchClawMode.h>
#include <Commands/Elevator/ElevCtrl.h>

LeftRightScale::LeftRightScale() {
	Path p ({ {{7.360, 0.547}} ,{{7.420, 5.687}}, {{2.440, 6.187}}, {{1.52, 8.307}} });
	CatmullRom pathMaker(true, 90, 90);
	p.SetGradients(pathMaker);
	p.Generate();
	MotionProfileConfig config = DEFAULT_CONFIG;
	config.maxVel = 2;
	Trajectory t(p, config);

	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new RotorAction(Collector::ROTOR_POS::DOWN));
	AddParallel(new ElevCtrl(ElevCtrl::ELEVPOS::UP));
	AddParallel(new SwitchClawMode(Collector::CLAWMODE::CLOSE));
	AddSequential(new DriveTrajectory(std::move(t)));
	AddSequential(new MoveBelt(Conveyor::SIDE::RIGHT));
	AddSequential(new ElevCtrl(ElevCtrl::ELEVPOS::DOWN));
}
