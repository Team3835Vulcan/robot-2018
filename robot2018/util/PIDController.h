/*
 * PIDController.h
 *
 *  Created on: 9 בינו׳ 2018
 *      Author: Coding Monkeys
 *
 *  This version of a PIDController is designed to work directly in a
 *  command loop. As such, one must create and configure the controller
 *  in the command. The calculate function should be called once per cycle
 *  for consistent results.
 */

#ifndef UTIL_PIDCONTROLLER_H_
#define UTIL_PIDCONTROLLER_H_

#include <Timer.h>

namespace vulcan {

class PIDController {
private:

	//controller parameters
	double m_p;
	double m_i;
	double m_d;
	double m_f;

	double m_setpoint;
	double m_prevError; //holds the previous error
	double m_error; //holds the current error
	double m_totalError; //holds error integral

	double m_tolerance; //controller's tolerance

	double m_output; //holds current output

	//min/max setpoint inputs
	double m_minInput;
	double m_maxInput;

	//min/max outputs
	double m_minOutput;
	double m_maxOutput;

	//used for differential time calculations(differntiation and integration)
	double m_prevTime;
	double m_currTime;

	//allows controller to calculate
	bool m_isEnabled;

	Timer time;

	double Limit(double value, double min, double max); //limit value between a min and max
public:
	PIDController(double p, double i, double d);
	PIDController(double p, double i, double d, double f);

	//get loop parameters
	double GetP();
	double GetI();
	double GetD();
	double GetF();

	//set loop parameters
	void SetP(double p);
	void SetI(double i);
	void SetD(double d);
	void SetPID(double p, double i, double d);
	void SetF(double f);

	//set input/output range
	void SetInputRange(double min, double max);
	void SetOutputRange(double min, double max);

	void SetTolerance(double tolerance); //set absolute tolerance

	//MUST BE CALLED EACH TIME A NEW SETPOINT IS APPLIED IF USED
	void SetPercentTolerance(double percent); //set tolerance to percentage of setpoint

	bool IsOnTarget(); //is error in tolerance range

	void SetSetpoint(double setpoint); //set absolute setpoint
	void SetRelativeSetpoint(double delta); //add a value to the current setpoint

	void Calculate(double input); //calculate the output value
	double GetOutput(); //get the output

	void Enable(); //start the timer, enable calculation
	void Disable(); //stop the timer, disable calculation
	void Reset(); //reset the intergral, timer and zeroes the error, setpoint and output
	//also disables calculation


};

} /* namespace vulcan */

#endif /* UTIL_PIDCONTROLLER_H_ */
