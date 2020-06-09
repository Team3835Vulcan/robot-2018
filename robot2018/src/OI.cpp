/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

OI::OI() : m_left(std::make_unique<frc::Joystick>(LEFT_JOYSTICK)), m_right(std::make_unique<frc::Joystick>(RIGHT_JOYSTICK)){
}

OI& OI::GetInstance()
{
	static OI instance;
	return instance;
}

const float OI::GetLeftY() const
{
	return m_left->GetY();
}

const float OI::GetRightY() const
{
	return m_right->GetY();
}
