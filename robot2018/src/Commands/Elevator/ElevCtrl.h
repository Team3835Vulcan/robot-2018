#ifndef ElevCtrl_H
#define ElevCtrl_H

#include <Commands/Command.h>

class ElevCtrl : public frc::Command {
public: enum ELEVPOS {UP, DOWN};
private:
	ELEVPOS m_pos;

public:

	ElevCtrl(ELEVPOS pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevCtrl_H
