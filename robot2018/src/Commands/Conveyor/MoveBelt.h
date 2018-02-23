#ifndef MoveBelt_H
#define MoveBelt_H

#include <Commands/TimedCommand.h>
#include <Subsystems/Conveyor/Conveyor.h>

class MoveBelt : public frc::TimedCommand {
private:
	Conveyor::SIDE m_side;

public:
	MoveBelt(Conveyor::SIDE s);
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif  // MoveBelt_H
