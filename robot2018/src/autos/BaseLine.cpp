#include "BaseLine.h"
#include <Commands/Chassis/DriveStraight.h>
#include <iostream>

BaseLine::BaseLine() {
	AddSequential(new DriveStraight(4.3));
}
