/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <RobotBase.h>
#include <Subsystems/Chassis/Chassis.h>
#include <Subsystems/Collector/Collector.h>
#include <Subsystems/Conveyor/Conveyor.h>
#include <Subsystems/Elevator/Elevator.h>
#include <OI.h>
#include <Commands/Chassis/DrivePath.h>
#include <Commands/Chassis/DriveStraight.h>
#include <Commands/Chassis/Turn.h>
#include <autos/RightSideSwitch.h>
#include <autos/RightSideScale.h>
class Robot : public frc::TimedRobot {
public:
	void RobotInit() override {

		Chassis::GetInstance();
		Collector::GetInstance();
		Conveyor::GetInstance();
		Elevator::GetInstance();
		OI::GetInstance();
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		Path p ({ { 0,0 },{ 0.2,3.5 }, {0.6,5.4},{ 0.8,8.5 } });
		frc::SmartDashboard::PutData("drive path", new DrivePath(std::move(p),90));
		frc::SmartDashboard::PutData("drive straight", new DriveStraight(3.6));
		frc::SmartDashboard::PutData("turn 60", new Turn(60));
		frc::SmartDashboard::PutData("right switch", new RightSideSwitch());
		frc::SmartDashboard::PutData("right scale", new RightSideScale());
		SetPeriod(1e-3);
	}

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to
	 * the
	 * chooser code above (like the commented example) or additional
	 * comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {

		m_autonomousCommand = m_chooser.GetSelected();

		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Cancel();
			m_autonomousCommand = nullptr;
		}
	}

	void TeleopPeriodic() override { frc::Scheduler::GetInstance()->Run(); }

	void TestPeriodic() override {}

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* m_autonomousCommand = nullptr;
	frc::SendableChooser<frc::Command*> m_chooser;
};

START_ROBOT_CLASS(Robot)
