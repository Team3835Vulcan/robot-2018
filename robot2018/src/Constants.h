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
constexpr int RLEFT_MOTOR = 12;
constexpr int FLEFT_MOTOR = 13;
constexpr int RRIGHT_MOTOR = 10;
constexpr int FRIGHT_MOTOR = 11;

constexpr int CONV_MOTOR = 19;

constexpr int COLL1_MOTOR = 14;
constexpr int COLL2_MOTOR = 15;
constexpr int ROTOR_MOTOR = 16;

constexpr int ELEV1_MOTOR = 17;
constexpr int ELEV2_MOTOR = 18;

constexpr int LEFT_ENCODER_A = 4;
constexpr int LEFT_ENCODER_B = 3;
constexpr int RIGHT_ENCODER_A = 2;
constexpr int RIGHT_ENCODER_B = 1;

//limit switches
constexpr int UP_COLL_SWITCH = 8;
constexpr int DOWN_COLL_SWITCH = 9;
constexpr int CUBE_SWITCH = 7;
constexpr int ELEV_UP_SWITCH = 5;
constexpr int ELEV_DOWN_SWITCH = 6;

//pneumatics
constexpr int CLAW_FORWARD = 0;
constexpr int CLAW_BACKWARD = 1;

//Joysticks
constexpr int RIGHT_JOYSTICK = 1;
constexpr int LEFT_JOYSTICK = 0;

//math
constexpr double PI = 3.141592653589793238462;

//physical properties
constexpr float GEAR_RATIO = 9.87;
constexpr float WHEEL_DIAMETER = 6 * 0.0254; //in meters
constexpr float DISTANCE_PER_PULSE = PI * WHEEL_DIAMETER / (GEAR_RATIO * 20);
constexpr float WHEELBASE = 0.497; //in meters

//physical limits
constexpr double MAX_ROBOT_VELOCITY = 2.8;//in m/s
constexpr double VELOCITY_FEEDFORWARD = 1/MAX_ROBOT_VELOCITY;
constexpr double MAX_ROBOT_ACCELERATION = 2; //in m/s^2
constexpr double ROTOR_VOLT_DELTA = 2.6;
