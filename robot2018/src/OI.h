/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Constants.h"
#include <memory>
#include <Joystick.h>

class OI {
private:
	OI();

	std::unique_ptr<frc::Joystick> m_left;
	std::unique_ptr<frc::Joystick> m_right;

public:
	static OI& GetInstance();

	const float GetRightY() const;
	const float GetLeftY() const;
};
