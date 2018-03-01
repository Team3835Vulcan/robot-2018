#include "BaseLine.h"
#include <Commands/Chassis/DriveStraight.h>

BaseLine::BaseLine() {
	AddSequential(new DriveStraight(4.3));
}
