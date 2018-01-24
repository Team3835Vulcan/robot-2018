/*
 * MotionProfileDriveController.cpp
 *
 *  Created on: 22 בינו׳ 2018
 *      Author: Coding Monkeys
 */

#include <Subsystems/Chassis/Controllers/MotionProfileDriveController.h>

namespace vulcan {
	MotionProfileDriveController::MotionProfileDriveController(float tolerance, float dt) :
		m_tolerance(tolerance), m_dt(dt), m_enabled(false), m_goalDist(0), m_goalTime(0),
		m_currDist(0), m_currVel(0), m_currTime(0), m_prevTime(0),
		m_velController(std::make_unique<vulcan::PIDController>(0,0,0,VELOCITY_FEEDFORWARD)),
		output(0){
			m_velController->SetInputRange(-MAX_ROBOT_VELOCITY, MAX_ROBOT_VELOCITY);
			m_velController->SetOutputRange(-1,1);
	}

	MotionProfileDriveController::MotionProfileDriveController(float tolerance) :
			m_tolerance(tolerance), m_dt(0.02), m_enabled(false), m_goalDist(0), m_goalTime(0),
			m_currDist(0), m_currVel(0), m_currTime(0), m_prevTime(0),
			m_velController(std::make_unique<vulcan::PIDController>(0,0,0,VELOCITY_FEEDFORWARD)),
			output(0){
			m_velController->SetInputRange(-MAX_ROBOT_VELOCITY, MAX_ROBOT_VELOCITY);
			m_velController->SetOutputRange(-1,1);
	}

	void MotionProfileDriveController::Enable(){
		m_enabled = true;
		m_velController->Enable();
		time.Start();
		m_prevTime = time.Get();
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
		m_goalDist = m_profile->GetDist();
		m_goalTime = m_profile->GetTime();
	}
	void MotionProfileDriveController::SetTolerance(float tolerance){
		m_tolerance = tolerance;
	}
	void MotionProfileDriveController::SetPID(double p, double i, double d){
		m_velController->SetPID(p,i,d);
	}

	void MotionProfileDriveController::Calculate(){
		if(m_enabled){
			m_currTime = time.Get();
			double dt = m_currTime - m_prevTime;
			m_currVel = Chassis::GetInstance()->GetVelocity();
			m_currDist += m_currVel * dt;

			float goalVel = m_profile->GetSetpoint(m_currTime)->GetVelocity();
			m_velController->SetRelativeSetpoint(goalVel - m_currVel);
			m_velController->Calculate(Chassis::GetInstance()->GetVelocity());
			output = m_velController->GetOutput();

			m_prevTime = m_currTime;
		}
	}
	const double MotionProfileDriveController::GetOutput() const {
		return output;
	}

	bool MotionProfileDriveController::IsOnTarget(){
		return m_goalDist <= m_tolerance;
	}

} /* namespace vulcan */
