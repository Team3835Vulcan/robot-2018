#ifndef ManualRotor_H
#define ManualRotor_H

#include "Commands/Command.h"

class ManualRotor : public frc::Command {
public:
	ManualRotor();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ManualRotor_H
