/*
 * AnalogUltrasonic.cpp
 *
 *  Created on: 10 בינו׳ 2018
 *      Author: Guy
 */

#include "AnalogUltrasonic.h"

namespace vulcan {

AnalogUltrasonic::AnalogUltrasonic(int channel, double aboveRange, double belowRange, double voltageToDistance)
{
	m_voltageToDistance = voltageToDistance;
	m_aboveRange = aboveRange;
	m_belowRange = belowRange;
	analogChannel = new frc::AnalogInput(channel);
}

double AnalogUltrasonic::GetVoltage()
{
	return analogChannel->GetVoltage();
}

double AnalogUltrasonic::GetDistance()
{
	double distance = analogChannel->GetVoltage() * m_voltageToDistance;

	if(distance > m_aboveRange || distance < m_belowRange)
		return -1;

	return distance;
}

} /* namespace vulcan */
