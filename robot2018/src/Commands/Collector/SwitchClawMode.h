#ifndef SwitchClaw_H
#define SwitchClaw_H

#include <Commands/Command.h>
#include <Subsystems/Collector/Collector.h>

class SwitchClawMode : public frc::Command {
private:
	Collector::CLAWMODE m_mode;
public:
	SwitchClawMode(Collector::CLAWMODE);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SwitchClaw_H
