#ifndef ManualElevator_H
#define ManualElevator_H

#include <Commands/Command.h>

class ManualElevator : public frc::Command {
public:
	ManualElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ManualElevator_H
