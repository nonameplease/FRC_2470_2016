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

	Robot() :

			stick(0),// as they are declared above.
			stick2(1),
			motor_h1(4),
			motor_h2(5),
			motor_l1(0),
			motor_l2(1),
			motor_r1(2),
			motor_r2(3),
			motor_elevator(6),
			motor_andymark(7),
			grab(0,1),
			limitSwitch(9)
			//camera.StartAutomaticCapture()

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
		CameraServer::GetInstance()->StartAutomaticCapture();
		while (IsOperatorControl() && IsEnabled())
		{
			//limitswitch
			int limitswitch = 1;
			limitswitch = limitSwitch.Get(); // 0-close 1-open

			//elevator
			if (stick2.GetRawButton(1))
			{
				motor_elevator.Set(-1);
			}
			else if (stick2.GetRawButton(2) && limitswitch == 1)
			{
				motor_elevator.Set(1);
			}
			else
			{
				motor_elevator.Set(0);
			}

			//double solenoid
			if (stick2.GetRawButton(3))
			{
				grab.Set(DoubleSolenoid::kReverse);
			}
			else if (stick2.GetRawButton(4))
			{
				grab.Set(DoubleSolenoid::kForward);
			}
			else
			{
				grab.Set(DoubleSolenoid::kOff);
			}

			//andymark motor
			if (stick.GetRawButton(1))
			{
				motor_andymark.Set(1);
			}
			else if (stick.GetRawButton(2))
			{
				motor_andymark.Set(-1);
			}
			else
			{
				motor_andymark.Set(0);
			}


			//H Drive
			double axis_0 = stick.GetRawAxis(0);
			motor_h1.Set(axis_0);
			motor_h2.Set(axis_0);

			double axis_1 = stick.GetRawAxis(1);
			double axis_4 = stick.GetRawAxis(4);
			if(axis_1 > 0.2 || axis_1 < -0.2 || axis_4 > 0.2 || axis_4 < -0.2)
			{
				motor_l1.Set((-axis_1 + axis_4/2)/2);
				motor_l2.Set((-axis_1 + axis_4/2)/2);
				motor_r1.Set((axis_1 + axis_4/2)/2);
				motor_r2.Set((axis_1 + axis_4/2)/2);
			}
			/*else if(axis_4 > 0.2 || axis_4 < -0.2)
			{
				motor_l1.Set(axis_4);
				motor_l2.Set(axis_4);
				motor_r1.Set(axis_4);
				motor_r2.Set(axis_4);
			}*/
			else
			{
				motor_l1.Set(0);
				motor_l2.Set(0);
				motor_r1.Set(0);
				motor_r2.Set(0);
			}

			//motor powered solenoid
	/*			if (stick.GetRawButton(5))
				motor_solenoid.Set(1);
			else if (stick.GetRawButton(6))
				motor_solenoid.Set(-1);
			else
				motor_solenoid.Set(0);
	*/
			Wait(kupdateperiod);
		}

	}
	/**
	 * Runs during test mode
	 */
	void Test()
	{
		grab.Set(DoubleSolenoid::kReverse);
		Wait(4.0);
		grab.Set(DoubleSolenoid::kForward);

	}
};

START_ROBOT_CLASS(Robot);



