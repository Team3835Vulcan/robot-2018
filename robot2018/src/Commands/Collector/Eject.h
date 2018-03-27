#ifndef Eject_H
#define Eject_H

#include <Commands/TimedCommand.h>

class Eject : public frc::TimedCommand{
public:
	Eject();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif  // Eject_H
