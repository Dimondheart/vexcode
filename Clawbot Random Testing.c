#pragma config(Sensor, dgtl1,  rightSonar,     sensorSONAR_raw)
#pragma config(Sensor, dgtl3,  backBumper,     sensorTouch)
#pragma config(Sensor, dgtl4,  leftSonar,      sensorSONAR_raw)
#pragma config(Motor,  port1,           flashlight,    tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           leftMotor,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define LEFTJOY_X vexRT[Ch4]
#define LEFTJOY_Y vexRT[Ch3]

#define RIGHTJOY_X vexRT[Ch1]
#define RIGHTJOY_Y vexRT[Ch2]

#define MOVEMENT_LIMIT_BTN vexRT[Btn8U]

#define FORWARD_ENABLED true
#define FORWARD_DISABLED false
#define REVERSE_ENABLED true
#define REVERSE_DISABLED false

void limitMovement();                               //Using only one sonar
void limitMovement2();                                                  //Using 2 sonars
void tankDrive(bool allowForward, bool allowReverse);  //In tankDrive mode, LEFTJOY_Y affects left motor, RIGHTJOY_Y affects right motor


const int sonarStop = 550;

const int joystickDeadzone = 3;

task main ()
{
	bool moveLimitEnabled = true;  //defult/initial sonar use state

	while(true)
	{
		while (moveLimitEnabled == true && MOVEMENT_LIMIT_BTN != 1)  //while sonar is enabled and the sonar toggle button isn't pressed
		{
			limitMovement();
		}

		moveLimitEnabled = false;

		while (moveLimitEnabled == false && MOVEMENT_LIMIT_BTN == 1)  //sonar has been disabled, but button is still pressed so don't continue to next loop
		{
			//arcadeDrive(FORWARD_ENABLED);
			tankDrive(FORWARD_ENABLED, REVERSE_ENABLED);
		}

		while (moveLimitEnabled == false && MOVEMENT_LIMIT_BTN != 1)  //sonar still disabled, but button has been released
		{
			//arcadeDrive(FORWARD_ENABLED);
			tankDrive(FORWARD_ENABLED, REVERSE_ENABLED);
		}
		moveLimitEnabled = true;

		while (moveLimitEnabled == true && MOVEMENT_LIMIT_BTN == 1)  //sonar has been enabled, but button is still pressed so don't continue to next loop
		{
			limitMovement();
		}
		/*original motor control using only one joystick*/
		//motor[leftMotor]  = -(vexRT[Ch2] + vexRT[Ch1])/2;  // (y + x)/2
		//motor[rightMotor] = -(vexRT[Ch2] - vexRT[Ch1])/2;  // (y - x)/2
	}
}

void limitMovement()
{
	if ((SensorValue[rightSonar] > sonarStop || SensorValue[rightSonar] < 0)  //Allowed to move fwd & rev
		&& (SensorValue[backBumper] == 0))
	{
		motor[flashlight] = 0;
		//arcadeDrive(FORWARD_ENABLED);
		tankDrive(FORWARD_ENABLED, REVERSE_ENABLED);
	}

	else if ((SensorValue[rightSonar] > sonarStop || SensorValue[rightSonar] < 0)  //Allowed to move fwd & NOT rev
			&& (SensorValue[backBumper] == 1))
	{
		motor[flashlight] = 0;
		//arcadeDrive(FORWARD_ENABLED);
		tankDrive(FORWARD_ENABLED, REVERSE_DISABLED);
	}

	else if (SensorValue[rightSonar] <= sonarStop  //Allowed to move NOT fwd & rev
			&& SensorValue[backBumper] == 0)
	{
		motor[flashlight] = 127;
		//arcadeDrive(FORWARD_DISABLED);
		tankDrive(FORWARD_DISABLED, REVERSE_ENABLED);
	}

	else                                 //Allowed to move NOT fwd & NOT rev
	{
		motor[flashlight] = 127;
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
	}
}

void limitMovement2()
{
}

void tankDrive(bool allowForward, bool allowReverse)
{
	signed int leftDrive, rightDrive = 0;

	leftDrive = LEFTJOY_Y;
	rightDrive = RIGHTJOY_Y;

	if (allowForward == true && allowReverse == true                                //Fwd & rev Allowed
			&&(abs(LEFTJOY_Y) > joystickDeadzone || abs(RIGHTJOY_Y) > joystickDeadzone))
	{
		motor[leftMotor] = leftDrive;
		motor[rightMotor] = rightDrive;
	}

	else if (allowForward == true                                                    //Fwd Allowed, rev NOT Allowed
			&& allowReverse == false
			&&((leftDrive > 0 && rightDrive > 0)
				||(leftDrive > 35 && rightDrive > -35)
				||(leftDrive > -35 && rightDrive > 35)))
	{
		motor[leftMotor] = leftDrive;
		motor[rightMotor] = rightDrive;
	}


	else if (allowForward == false                                          //Fwd NOT Allowed, rev Allowed
			&& allowReverse == true
			&&((leftDrive < 0 && rightDrive < 0)
				||(leftDrive < 35 && rightDrive < -35)
				||(leftDrive < -35 && rightDrive < 35)))
	{
		motor[leftMotor] = leftDrive;
		motor[rightMotor] = rightDrive;
	}

	else                           //"Just in Case"
	{
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
	}
}