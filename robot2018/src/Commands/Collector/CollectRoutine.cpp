#include <Commands/Collector/SwitchClawMode.h>
#include "CollectRoutine.h"
#include "Collect.h"

CollectRoutine::CollectRoutine() : CommandGroup("collect routine") {
	AddSequential(new SwitchClawMode(Collector::CLAWMODE::OPEN));
	AddSequential(new Collect(Collector::COLLECTMODE::COLLECT));
}

void CollectRoutine::End(){
	Collector::GetInstance().SwitchClaw(Collector::CLAWMODE::CLOSE);
}

void CollectRoutine::Interrupted(){
	Collector::GetInstance().SwitchClaw(Collector::CLAWMODE::CLOSE);
}

