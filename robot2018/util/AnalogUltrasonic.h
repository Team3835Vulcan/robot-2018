/*
 * AnalogUltrasonic.h
 *
 *  Created on: 10 בינו׳ 2018
 *      Author: Guy
 */

#ifndef UTIL_ANALOGULTRASONIC_H_
#define UTIL_ANALOGULTRASONIC_H_

#include <AnalogInput.h>

namespace vulcan {

class AnalogUltrasonic {
public:
	AnalogUltrasonic(int channel, double m_belowRange, double m_aboveRange, double m_voltageToDistance);
	double GetDistance();
	double GetVoltage();

private:
	double m_voltageToDistance;
	double m_aboveRange;
	double m_belowRange;
	frc::AnalogInput* analogChannel;
};

} /* namespace vulcan */

#endif /* UTIL_ANALOGULTRASONIC_H_ */
