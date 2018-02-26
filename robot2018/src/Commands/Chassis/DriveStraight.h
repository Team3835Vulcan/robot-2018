#ifndef DriveStraight_H
#define DriveStraight_H

#include "Commands/Command.h"

class DriveStraight : public frc::Command {
private:
	double m_dist;

public:
	DriveStraight(double dist);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveStraight_H
