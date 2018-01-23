/*
 * MotionProfileDriveController.cpp
 *
 *  Created on: 22 בינו׳ 2018
 *      Author: Coding Monkeys
 */

#include <Subsystems/Chassis/Controllers/MotionProfileDriveController.h>

namespace vulcan {
	MotionProfileDriveController::MotionProfileDriveController(float tolerance, float dt) :
		m_tolerance(tolerance), m_dt(dt), output(0), m_enabled(false),
		m_velController(std::make_unique<vulcan::PIDController>(0,0,0,VELOCITY_FEEDFORWARD)){}
	MotionProfileDriveController::MotionProfileDriveController(float tolerance) : m_tolerance(tolerance), output(0), m_enabled(false),
			m_velController(std::make_unique<vulcan::PIDController>(0,0,0,VELOCITY_FEEDFORWARD)){}

	void MotionProfileDriveController::Enable(){
		m_enabled = true;
		m_velController->Enable();
		time.Start();
	}

	void MotionProfileDriveController::Disable(){
			m_enabled = false;
			m_velController->Disable();
			time.Stop();
			time.Reset();
	}

	void MotionProfileDriveController::SetProfile(const MotionProfile& profile){
		if(m_profile.get())
			m_profile.release();
		m_profile = std::make_unique<MotionProfile>(profile);
	}
	void MotionProfileDriveController::SetTolerance(float tolerance){
		m_tolerance = tolerance;
	}
	void MotionProfileDriveController::SetPID(double p, double i, double d){
		m_velController->SetPID(p,i,d);
	}

	void MotionProfileDriveController::Calculate(){
		if(m_enabled){
			double currTime = time.Get();
			m_velController->SetSetpoint(m_profile->GetSetpoint(currTime)->GetVelocity());
			m_velController->Calculate(Chassis::GetInstance()->GetVelocity());
			output = m_velController->GetOutput();
		}
	}
	double MotionProfileDriveController::GetOutput(){
		return output;
	}
} /* namespace vulcan */
