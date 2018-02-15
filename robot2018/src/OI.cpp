/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <OI.h>
#include <Commands/Collector/Collect.h>
#include <Commands/Collector/SwitchClaw.h>
#include <Commands/Collector/RotorAction.h>
#include <Commands/Conveyor/MoveBelt.h>
#include <Commands/Elevator/ElevCtrl.h>

OI::OI() : m_left(std::make_unique<frc::Joystick>(LEFT_JOYSTICK)),
		   m_right(std::make_unique<frc::Joystick>(RIGHT_JOYSTICK)),
		   m_op(std::make_unique<frc::Joystick>(2)),
		   m_collectBtn(std::make_unique<frc::JoystickButton>(m_op.get(), 3)),
		   m_ejectBtn(std::make_unique<frc::JoystickButton>(m_op.get(),2)),
		   m_rotorUpBtn(std::make_unique<frc::JoystickButton>(m_op.get(),6)),
		   m_rotorDownBtn(std::make_unique<frc::JoystickButton>(m_op.get(),7)),
		   m_switchClaw(std::make_unique<frc::JoystickButton>(m_op.get(),1)),
		   m_convLeft(std::make_unique<frc::JoystickButton>(m_op.get(),4)),
		   m_convRight(std::make_unique<frc::JoystickButton>(m_op.get(),5)),
		   m_elevUp(std::make_unique<frc::JoystickButton>(m_op.get(),11)),
		   m_elevDown(std::make_unique<frc::JoystickButton>(m_op.get(),10))
		   {
				m_collectBtn->ToggleWhenPressed(new Collect(-0.8));
				m_ejectBtn->ToggleWhenPressed(new Collect(1));
				m_convLeft->ToggleWhenPressed(new MoveBelt(0.85));
				m_convRight->ToggleWhenPressed(new MoveBelt(-0.85));
				m_rotorUpBtn->WhenPressed(new RotorAction(0.8));
				m_rotorDownBtn->WhenPressed(new RotorAction(-0.4));
				m_switchClaw->WhenPressed(new SwitchClaw());
				m_elevUp->WhenPressed(new ElevCtrl(1));
				m_elevDown->WhenPressed(new ElevCtrl(-0.35));
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

const float OI::GetOPY() const{
	return m_op->GetY();
}
