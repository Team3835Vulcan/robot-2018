
/*
 * XboxController.cpp
 *
 *  Created on: 18 áôáø× 2018
 *      Author: Guy
 */

#include <util/XboxController.h>

namespace vulcan {

XboxTrigger::XboxTrigger(XboxController* controller, SIDE s) : m_controller(controller), m_side(s)
		{
				if(m_side == LEFT)
					m_axis = 2;
				else
					m_axis = 3;
		}

bool XboxTrigger::Get() {
	return m_controller->GetRawAxis(m_axis) > 0.75;
}

XboxController::XboxController(int port) : Joystick(port),
		m_aButton(std::make_unique<JoystickButton>(this, 1)),
		m_bButton(std::make_unique<JoystickButton>(this, 2)),
		m_xButton(std::make_unique<JoystickButton>(this, 3)),
		m_yButton(std::make_unique<JoystickButton>(this, 4)),
		m_lButton(std::make_unique<JoystickButton>(this, 5)),
		m_rButton(std::make_unique<JoystickButton>(this, 6)),
		m_backButton(std::make_unique<JoystickButton>(this, 7)),
		m_startButton(std::make_unique<JoystickButton>(this, 8)),
		m_lTrigger(std::make_unique<XboxTrigger>(this, XboxTrigger::SIDE::LEFT)),
		m_rTrigger(std::make_unique<XboxTrigger>(this, XboxTrigger::SIDE::RIGHT)){}

double XboxController::GetLY() const{
	return this->GetRawAxis(1);
}

double XboxController::GetRY() const{
	return this->GetRawAxis(5);
}



}/* namespace vulcan */
