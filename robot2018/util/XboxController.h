/*
 * XboxController.h
 *
 *  Created on: 18 áôáø× 2018
 *      Author: Guy
 */

#ifndef UTIL_XBOXCONTROLLER_H_
#define UTIL_XBOXCONTROLLER_H
#include <GenericHID.h>
#include <buttons/Trigger.h>
#include <buttons/JoystickButton.h>

namespace vulcan {

class XboxController;
class XboxTrigger;

class XboxTrigger : public frc::Trigger{
public:
	enum SIDE {LEFT, RIGHT};
	XboxTrigger(const XboxController& controller, SIDE s);
	bool Get() override;
private:
	GenericHID& m_controller;
	SIDE m_side;
	int m_axis;
};

class XboxController : public GenericHID {
public:
	XboxController(int port);
	frc::JoystickButton m_aButton, m_bButton, m_xButton, m_yButton, m_lButton, m_rButton, m_backButton, m_startButton;
	XboxTrigger m_lTrigger, m_rTrigger;
	frc::JoystickButton m_lStick, m_rStick;
};

} /* namespace vulcan */

#endif /* UTIL_XBOXCONTROLLER_H_ */
