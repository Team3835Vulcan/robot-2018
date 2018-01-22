#ifndef JoystickTankDrive_H
#define JoystickTankDrive_H

#include <Commands/Command.h>

class JoystickTankDrive : public frc::Command {
public:
	JoystickTankDrive();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // JoystickTankDrive_H
