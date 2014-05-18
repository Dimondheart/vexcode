#pragma config(Sensor, dgtl1,  bumper,         sensorTouch)
#pragma config(Motor,  port1,           flashlight,    tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           leftMotor,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,           clawMotor,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define LEFTJOY_Y -vexRT[Ch2]
#define RIGHTJOY_Y -vexRT[Ch3]

#define CLAWCLOSE_BTN vexRT[Btn5U]
#define CLAWOPEN_BTN vexRT[Btn6U]

#define FLASHLIGHT_BTN vexRT[Btn8U]

const int joystickDeadzone = 10;
const bool btnPressed = true;

void tankDrive();
void clawControl();


task main()
{
	while (true)
	{
		tankDrive();

		clawControl();

		if (FLASHLIGHT_BTN == btnPressed) motor[flashlight] = 127;
		else motor[flashlight] = 0;
	}
}


void tankDrive()
{
	if (abs(LEFTJOY_Y) > joystickDeadzone && abs(RIGHTJOY_Y) > joystickDeadzone)
	{
		motor[leftMotor] = LEFTJOY_Y;
		motor[rightMotor] = RIGHTJOY_Y;
	}
	else if (!(abs(LEFTJOY_Y) > joystickDeadzone) && abs(RIGHTJOY_Y) > joystickDeadzone)
	{
		motor[leftMotor] = 0;
		motor[rightMotor] = RIGHTJOY_Y;
	}
	else if (abs(LEFTJOY_Y) > joystickDeadzone && !(abs(RIGHTJOY_Y) > joystickDeadzone))
	{
		motor[leftMotor] = LEFTJOY_Y;
		motor[rightMotor] = 0;
	}
	else
	{
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
	}
}


void clawControl()
{
	if (CLAWCLOSE_BTN == btnPressed) motor[clawMotor] = -64;
	else if (CLAWOPEN_BTN == btnPressed) motor[clawMotor] = 64;
	else motor[clawMotor] = 0;
}