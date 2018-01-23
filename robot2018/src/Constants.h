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
 */

//speed controllers
<<<<<<< HEAD
constexpr int RLEFT_MOTOR = 0;
constexpr int FLEFT_MOTOR = 0;
constexpr int RRIGHT_MOTOR = 0;
constexpr int FRIGHT_MOTOR = 0;

constexpr int LEFT_ENCODER_A = 0;
constexpr int LEFT_ENCODER_B = 0;
constexpr int RIGHT_ENCODER_A = 0;
constexpr int RIGHT_ENCODER_B = 0;

//Joysticks
constexpr int RIGHT_JOYSTICK = 0;
constexpr int LEFT_JOYSTICK = 0;

constexpr float DISTANCE_PER_PULSE = 0;
=======

//physical limits
constexpr double MAX_ROBOT_VELOCITY = 10;//in m/s
constexpr double VELOCITY_FEEDFORWARD = 1/MAX_ROBOT_VELOCITY;
constexpr double MAX_ROBOT_ACCELERATION = 2; //in m/s^2
>>>>>>> changes to motion profiles, added command to follow profile for 1d movement
