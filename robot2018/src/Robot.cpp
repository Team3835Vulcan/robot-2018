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
#include <cscore_oo.h>
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
#include <autos/LeftSideSwitch.h>
#include <autos/MiddleRightSwitch.h>
#include <autos/MiddleLeftSwitch.h>
#include <autos/RightSideScale.h>
#include <autos/LeftSideScale.h>
#include <autos/DoNothing.h>
#include <autos/BaseLine.h>
#include <iostream>

class Robot: public frc::TimedRobot {
public:
	void RobotInit() override {

		Chassis::GetInstance();
		Collector::GetInstance();
		Conveyor::GetInstance();
		Elevator::GetInstance();
		OI::GetInstance();

		cam = frc::CameraServer::GetInstance()->StartAutomaticCapture();
		cam.SetFPS(10);
		cam.SetResolution(360, 240);

		m_pos.AddDefault("middle", 'M');
		m_pos.AddObject("left", 'L');
		m_pos.AddObject("right", 'R');

		m_pref.AddDefault("scale", "sc");
		m_pref.AddObject("switch", "sw");

		frc::SmartDashboard::PutData("Robot Position", &m_pos);
		frc::SmartDashboard::PutData("Auto Preference", &m_pref);

		frc::SmartDashboard::PutData("left switch", new LeftSideSwitch());
		frc::SmartDashboard::PutData("right switch", new RightSideSwitch());
		frc::SmartDashboard::PutData("left scale", new LeftSideScale());
		frc::SmartDashboard::PutData("right switch", new RightSideScale());
		frc::SmartDashboard::PutData("midleft switch", new MiddleLeftSwitch());
		frc::SmartDashboard::PutData("midright switch",
				new MiddleRightSwitch());
		frc::SmartDashboard::PutData("baseline", new BaseLine());
		frc::SmartDashboard::PutData("straigtdrive", new DriveStraight(3));

		SetPeriod(1e-3);
	}

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {
	}

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
		std::string gameData =
				frc::DriverStation::GetInstance().GetGameSpecificMessage();

		char side = m_pos.GetSelected();
		std::string pref = m_pref.GetSelected();

		char switchSide;
		char scaleSide;

		//choose autonomous according to side and preference
		if (gameData.length() > 0) {
			switchSide = gameData[0];
			scaleSide = gameData[1];

			if (side == 'M') {
				if (switchSide == 'R') {
					m_autonomous = new MiddleRightSwitch();
					frc::SmartDashboard::PutString("auto chosen", "mid right");
				} else {
					m_autonomous = new MiddleLeftSwitch();
					frc::SmartDashboard::PutString("auto chosen", "mid left");
				}
			} else if (side == 'R') {
				if (pref == "sc" && side == scaleSide) {
					m_autonomous = new RightSideScale();
					frc::SmartDashboard::PutString("auto chosen",
							"right scale");
				} else if (pref == "sw" && side == switchSide) {
					m_autonomous = new RightSideSwitch();
					frc::SmartDashboard::PutString("auto chosen",
							"right switch");
				} else {

					if (scaleSide == side) {
						m_autonomous = new RightSideScale();
						frc::SmartDashboard::PutString("auto chosen",
								"right scale");
					} else if (switchSide == side) {
						m_autonomous = new RightSideSwitch();
						frc::SmartDashboard::PutString("auto chosen",
								"right switch");
					} else {
						m_autonomous = new BaseLine();
						frc::SmartDashboard::PutString("auto chosen",
								"base line");
					}
				}
			} else if (side == 'L') {
				if (pref == "sc" && side == scaleSide) {
					m_autonomous = new LeftSideScale();
					frc::SmartDashboard::PutString("auto chosen",
							"left switch");
				} else if (pref == "sw" && side == switchSide) {
					m_autonomous = new LeftSideSwitch();
					frc::SmartDashboard::PutString("auto chosen", "left scale");
				} else {
					if (scaleSide == side) {
						m_autonomous = new LeftSideScale();
						frc::SmartDashboard::PutString("auto chosen",
								"left scale");
					} else if (switchSide == side) {
						m_autonomous = new LeftSideSwitch();
						frc::SmartDashboard::PutString("auto chosen",
								"left switch");
					} else {
						m_autonomous = new BaseLine();
						frc::SmartDashboard::PutString("auto chosen",
								"baseline");
					}
				}
			}
		}

		//just to be sure
		if (m_autonomous == nullptr) {
			m_autonomous = new BaseLine();
			frc::SmartDashboard::PutString("auto chosen", "baseline");
		}
		m_autonomous->Start();
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (m_autonomous != nullptr) {
			m_autonomous->Cancel();
			m_autonomous = nullptr;
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {
	}

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* m_autonomous = nullptr;
	frc::SendableChooser<char> m_pos;
	frc::SendableChooser<std::string> m_pref;
	cs::UsbCamera cam;
};

START_ROBOT_CLASS(Robot)
