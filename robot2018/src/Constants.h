/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/*
 * Add all needed constants here.
 * Relevant constants are:
 * 1. Ports on the robot(for speedcontrollers, sensors etc)
 * 2. physical size measurements of the robot
 * 3. physical limits of the robot
 * 4. final controller parameters
 */

//speed controllers
constexpr int RLEFT_MOTOR = 8;
constexpr int FLEFT_MOTOR = 9;
constexpr int RRIGHT_MOTOR = 6;
constexpr int FRIGHT_MOTOR = 7;

constexpr int CONV_MOTOR = 0;

constexpr int COLL1_MOTOR = 3;
constexpr int COLL2_MOTOR = 4;
constexpr int ROTOR_MOTOR = 5;

constexpr int ELEV1_MOTOR = 1;
constexpr int ELEV2_MOTOR = 2;

constexpr int LEFT_ENCODER_A = 0;
constexpr int LEFT_ENCODER_B = 0;
constexpr int RIGHT_ENCODER_A = 0;
constexpr int RIGHT_ENCODER_B = 0;

//limit switches
constexpr int UP_COLL_SWITCH = 7;
constexpr int DOWN_COLL_SWITCH = 8;
constexpr int CUBE_SWITCH = 9;
constexpr int ELEV_UP_SWITCH = 6;
constexpr int ELEV_DOWN_SWITCH = 5;

//pneumatics
constexpr int CLAW_FORWARD = 0;
constexpr int CLAW_BACKWARD = 0;

//Joysticks
constexpr int RIGHT_JOYSTICK = 1;
constexpr int LEFT_JOYSTICK = 0;

constexpr float DISTANCE_PER_PULSE = 0;

//physical limits
constexpr double MAX_ROBOT_VELOCITY = 10;//in m/s
constexpr double VELOCITY_FEEDFORWARD = 1/MAX_ROBOT_VELOCITY;
constexpr double MAX_ROBOT_ACCELERATION = 2; //in m/s^2
