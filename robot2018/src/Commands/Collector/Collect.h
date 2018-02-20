#ifndef Collect_H
#define Collect_H

#include <Commands/Command.h>
#include <Subsystems/Collector/Collector.h>

class Collect : public frc::Command {
private:
	Collector::COLLECTMODE m_mode;

public:
	Collect(Collector::COLLECTMODE mode);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Collect_H
