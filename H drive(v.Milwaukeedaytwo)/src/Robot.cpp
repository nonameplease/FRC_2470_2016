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
class Robot: public SampleRobot
{
	Joystick stick;// only joystick
	Joystick stick2;
	VictorSP motor_h1;
	VictorSP motor_h2;
	VictorSP motor_l1;
	VictorSP motor_l2;
	VictorSP motor_r1;
	VictorSP motor_r2;
	VictorSP motor_elevator;
	VictorSP motor_andymark;
	DoubleSolenoid grab;
	DigitalInput limitSwitch;
	bool buttonvalue1;
	bool buttonvalue2;
	bool buttonvalue3;
	bool buttonvalue4;

	double kupdateperiod = 0.05;

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
		//chassis.SetExpiration(0.1);
	}

	//custom functions
	void driveforward(double power, double time)
	{
		motor_l1.Set(-power);
		motor_l2.Set(-power);
		motor_r1.Set(power);
		motor_r2.Set(power);
		Wait(time);
		motor_l1.Set(0);
		motor_l2.Set(0);
		motor_r1.Set(0);
		motor_r2.Set(0);
	}

	void turn(double power, double time)
	{
		/*
		 * negative power: turn left, positive power: turn right
		 */
		motor_l1.Set(power);
		motor_l2.Set(power);
		motor_r1.Set(power);
		motor_r2.Set(power);
		Wait(time);
		motor_l1.Set(0);
		motor_l2.Set(0);
		motor_r1.Set(0);
		motor_r2.Set(0);
	}

	void RobotInit() override
    {
        //CameraServer::GetInstance()->StartAutomaticCapture();
        //camera.StartAutomaticCapture();
    }

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{

		/*buttonValue1 = SmartDashboard::GetBoolean("DB/Button 1");
		buttonValue2 = SmartDashboard::GetBoolean("DB/Button 2");
		SmartDashboard::PutBoolean("DB/LED 1", buttonValue1);
		SmartDashboard::PutBoolean("DB/LED 2", buttonValue2);
		if(buttonValue1 == true && buttonValue2 == false)*/
		buttonvalue1 = SmartDashboard::GetBoolean("DB/Button 1"); //slide left/forward
		buttonvalue2 = SmartDashboard::GetBoolean("DB/Button 2"); //slide right/backward
		buttonvalue3 = SmartDashboard::GetBoolean("DB/Button 3"); //grab stuff
		buttonvalue4 = SmartDashboard::GetBoolean("DB/Button 0"); //switch to drive forward and backward
		SmartDashboard::PutBoolean("DB/LED 1", buttonvalue1);
		SmartDashboard::PutBoolean("DB/LED 2", buttonvalue2);
		SmartDashboard::PutBoolean("DB/LED 3", buttonvalue3);
		SmartDashboard::PutBoolean("DB/LED 0", buttonvalue4);

		if (buttonvalue3 == true)
		{
            //Grab and run
            motor_l1.Set(0.5);
            motor_l2.Set(0.5);
            motor_r1.Set(-0.5);
            motor_r2.Set(-0.5);
            Wait(0.5);
            motor_l1.Set(0);
            motor_l2.Set(0);
            motor_r1.Set(0);
            motor_r2.Set(0);
            Wait(0.5);
            grab.Set(DoubleSolenoid::kForward);
            Wait(0.5);
            motor_elevator.Set(-1);
            Wait(1);
            motor_elevator.Set(0);
            Wait(0.5);
            grab.Set(DoubleSolenoid::kReverse);
            Wait(0.5);
            motor_elevator.Set(1);
            Wait(1);
            motor_elevator.Set(0);
		}

		if (buttonvalue1 == true && buttonvalue4 == false)
		{
			//H-Drive sideways left
			motor_h1.Set(-0.5);
			motor_h2.Set(-0.5);
			Wait(3);
			motor_h1.Set(0);
			motor_h2.Set(0);
		}
		else if (buttonvalue1 == true && buttonvalue4 == true)
		{
			motor_l1.Set(0.5);
			motor_l2.Set(0.5);
			motor_r1.Set(-0.5);
			motor_r2.Set(-0.5);
			Wait(4);
			motor_l1.Set(0);
			motor_l2.Set(0);
			motor_r1.Set(0);
			motor_r2.Set(0);
			Wait(0.5);
		}
		else if (buttonvalue2 == true && buttonvalue4 == false)
		{
			//H-Drive sideways right
			motor_h1.Set(0.5);
			motor_h2.Set(0.5);
			Wait(3);
			motor_h1.Set(0);
			motor_h2.Set(0);
		}
		else if (buttonvalue1 == true && buttonvalue4 == true)
		{
			motor_l1.Set(-0.5);
			motor_l2.Set(-0.5);
			motor_r1.Set(0.5);
			motor_r2.Set(0.5);
			Wait(4);
			motor_l1.Set(0);
			motor_l2.Set(0);
			motor_r1.Set(0);
			motor_r2.Set(0);
			Wait(0.5);
		}
		else if (buttonvalue1 == true && buttonvalue2 == true)
		{

		}

		Wait(1);
		grab.Set(DoubleSolenoid::kForward);
		Wait(1);
		motor_l1.Set(-0.5);
		motor_l2.Set(-0.5);
		motor_r1.Set(0.5);
		motor_r2.Set(0.5);
		Wait(1);
		motor_l1.Set(0);
		motor_l2.Set(0);
		motor_r1.Set(0);
		motor_r2.Set(0);

		//container grabbing
		/*motor_h1.Set(-0.5);
        motor_h1.Set(-0.5);
		Wait(2.0);
		motor_h1.Set(0);
		motor_h1.Set(0);
		motor_andymark.Set(-1);
		Wait(6.0);
		motor_andymark.Set(0);
		motor_h1.Set(0.5);
		motor_h2.Set(0.5);
		Wait(1.0);
		motor_andymark.Set(1);
		Wait(1.0);
		motor_andymark.Set(0);
		Wait(1.0);
		motor_h1.Set(0);
		motor_h2.Set(0);
		motor_andymark.Set(1);
		Wait(5);
		motor_andymark.Set(0);*/

		//Drive forward
		/*Wait(2.0);
		motor_l1.Set(0.5);
		motor_l2.Set(0.5);
		motor_r1.Set(-0.5);
		motor_r2.Set(-0.5);
		Wait(2.0);
		motor_l1.Set(0);
		motor_l2.Set(0);
		motor_r1.Set(0);
		motor_r2.Set(0);
		Wait(0.5);
		motor_l1.Set(0.3);
		motor_l2.Set(0.3);
		motor_r1.Set(0.3);
		motor_r2.Set(0.3);
		Wait(0.5);
		motor_l1.Set(0);
		motor_l2.Set(0);
		motor_r1.Set(0);
		motor_r2.Set(0);*/


		/*buttonValue1 = SmartDashboard::GetBoolean("DB/Button 1");
		buttonValue2 = SmartDashboard::GetBoolean("DB/Button 2");
		SmartDashboard::PutBoolean("DB/LED 1", buttonValue1);
		SmartDashboard::PutBoolean("DB/LED 2", buttonValue2);
		if(buttonValue1 == true && buttonValue2 == false)
		{
			SmartDashboard::PutBoolean("DB/LED 1", true);*/

	}

	/**
	 * Runs the motors with arcade steering.
	 */
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
