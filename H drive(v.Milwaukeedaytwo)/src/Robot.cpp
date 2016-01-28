/*
 * Robot.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: bpsstudent
 */

#include "WPILib.h"
#include "Joystick.h"
#include "CameraServer.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot : public SampleRobot
{
	//Variables that we will want to use throughout the program
	Joystick stick; //A Joystick that we can use


	//Public means that other files can use these functions
public:

	//This is a "Constructor" and will be called when this class gets made somewhere
	Robot() :
		stick(0) //Initialize the Joystick to channel/port 0
	{
		//Can add other "initialization" code here
	}

	//Will be called to initialize the robot
	//Should be called from the FRC program itself
	void RobotInit() override
	{
		//Add initialization code here
	}

	void Autonomous()
	{
		//Add autonomous code here
	}

	void OperatorControl()
	{
		//Add "Manual mode" code here
	}
};

START_ROBOT_CLASS(Robot);



