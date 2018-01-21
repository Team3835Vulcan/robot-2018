#ifndef TankDrive_H
#define TankDrive_H

#include "../Robot.cpp"
#include "../CommandBase.h"

class TankDrive : public CommandBase {
public:
	TankDrive();
	void Execute();
	bool IsFinished();
	void End();
};

#endif  // TankDrive_H
