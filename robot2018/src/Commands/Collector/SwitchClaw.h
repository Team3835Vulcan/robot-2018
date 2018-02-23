#ifndef SwitchClaw_H
#define SwitchClaw_H

#include "Commands/Command.h"

class SwitchClaw : public frc::Command {
public:
	SwitchClaw();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SwitchClaw_H
