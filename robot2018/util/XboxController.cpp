
/*
 * XboxController.cpp
 *
 *  Created on: 18 áôáø× 2018
 *      Author: Guy
 */

#include <util/XboxController.h>

namespace vulcan {

XboxTrigger::XboxTrigger(const XboxController& controller, SIDE s) : m_controller(controller), m_side(s)
		{
				if(m_side == LEFT)
					m_axis = 2;
				else
					m_axis = 3;
		}

bool XboxTrigger::Get() {
	return m_controller.GetRawAxis(m_axis) > 0.8;
}

XboxController::XboxController(int port) : GenericHID(port), m_aButton(this, 1), m_bButton(this, 2), m_xButton(this, 3), m_yButton(this, 4),
		m_lButton(this, 5), m_rButton(this, 6), m_backButton(this, 7), m_startButton(this, 8), m_lTrigger(this, XboxTrigger::SIDE::LEFT),
		m_rTrigger(this, XboxTrigger::SIDE::RIGHT){}

} /* namespace vulcan */
