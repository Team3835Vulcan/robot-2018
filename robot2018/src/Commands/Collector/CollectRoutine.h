#ifndef CollectRoutine_H
#define CollectRoutine_H

#include <Commands/CommandGroup.h>

class CollectRoutine : public frc::CommandGroup {
public:
	CollectRoutine();

	void End() override;
	void Interrupted() override;
};

#endif  // CollectRoutine_H
