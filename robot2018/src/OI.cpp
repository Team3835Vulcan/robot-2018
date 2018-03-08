/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <OI.h>
#include <Commands/Collector/Collect.h>
#include <Commands/Collector/SwitchClaw.h>
#include <Commands/Collector/CollectRoutine.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Collector/ManualRotor.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Elevator/ElevCtrl.h>

OI::OI() : m_left(std::make_unique<frc::Joystick>(LEFT_JOYSTICK)),
   m_right(std::make_unique<frc::Joystick>(RIGHT_JOYSTICK)),
   m_op(std::make_unique<vulcan::XboxController>(2)){
		m_op->m_bButton->WhenPressed(new MoveBelt(Conveyor::SIDE::RIGHT));
		m_op->m_xButton->WhenPressed(new MoveBelt(Conveyor::SIDE::LEFT));
		m_op->m_yButton->WhenPressed(new Collect(Collector::COLLECTMODE::EJECT));
		m_op->m_aButton->WhenPressed(new SwitchClaw());
		m_op->m_lTrigger->ToggleWhenPressed(
				new Collect(Collector::COLLECTMODE::COLLECT));
		m_op->m_rButton->WhenPressed(new RotorAction(Collector::ROTOR_POS::UP));
		m_op->m_lButton->WhenPressed(new RotorAction(Collector::ROTOR_POS::DOWN));
		m_op->m_backButton->ToggleWhenPressed(new ManualRotor());
   }

OI& OI::GetInstance(){
	static OI instance;
	return instance;
}

const float OI::GetLeftY() const{
	return -m_left->GetY();
}

const float OI::GetRightY() const{
	return -m_right->GetY();
}

const float OI::GetOPLY() const{
	return m_op->GetLY();
}

const float OI::GetOPRY() const{
	return m_op->GetRY();
}
