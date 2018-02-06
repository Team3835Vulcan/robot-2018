#ifndef MoveBelt_H
#define MoveBelt_H

#include <Commands/Command.h>

class MoveBelt : public frc::Command {
private:
	double m_val;

public:
	MoveBelt(double val);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // MoveBelt_H
