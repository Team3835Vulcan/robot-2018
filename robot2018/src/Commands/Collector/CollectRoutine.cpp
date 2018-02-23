#include "CollectRoutine.h"
#include "Collect.h"
#include "SwitchClaw.h"

CollectRoutine::CollectRoutine() : CommandGroup("collect routine") {
	AddSequential(new SwitchClaw(Collector::CLAWMODE::OPEN));
	AddSequential(new Collect(Collector::COLLECTMODE::COLLECT));
}

void CollectRoutine::End(){
	Collector::GetInstance().SwitchClaw(Collector::CLAWMODE::OPEN);
}

void CollectRoutine::Interrupted(){
	Collector::GetInstance().SwitchClaw(Collector::CLAWMODE::OPEN);
}

