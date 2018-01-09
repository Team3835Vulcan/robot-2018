/*
 * PIDController.h
 *
 *  Created on: 9 בינו׳ 2018
 *      Author: Coding Monkeys
 */

#ifndef UTIL_PIDCONTROLLER_H_
#define UTIL_PIDCONTROLLER_H_

namespace vulcan {

class PIDController {
public:
	PIDController();
	void Calculate(double input);
};

} /* namespace vulcan */

#endif /* UTIL_PIDCONTROLLER_H_ */
