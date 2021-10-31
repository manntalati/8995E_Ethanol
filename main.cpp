/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Nanu                                             */
/*    Created:      Mon Mar 01 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftFront            motor         9               
// LeftBack             motor         1               
// RightFront           motor         19              
// RightBack            motor         12              
// belt                 motor         5               
// Controller1          controller                    
// intake               motor         17              
// FourBarLeft          motor         8               
// FourBarRight         motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

void driveForward (int number)
{
  LeftFront.startRotateFor(fwd, number, deg);
  LeftBack.startRotateFor(fwd, number, deg);
  RightFront.startRotateFor(reverse, number, deg);
  RightBack.rotateFor(reverse, number, deg);
}

void driveBackward (int number)
{
  LeftFront.startRotateFor(reverse, number, deg);
  LeftBack.startRotateFor(reverse, number, deg);
  RightFront.startRotateFor(fwd, number, deg);
  RightBack.rotateFor(fwd, number, deg);
}

void turnRight (int number)
{
  LeftFront.startRotateFor(fwd, number, deg);
  LeftBack.startRotateFor(fwd, number, deg);
  RightFront.startRotateFor(fwd, number, deg);
  RightBack.rotateFor(fwd, number, deg);
}

void turnLeft (int number)
{
  LeftFront.startRotateFor(reverse, number, deg);
  LeftBack.startRotateFor(reverse, number, deg);
  RightFront.startRotateFor(reverse, number, deg);
  RightBack.rotateFor(reverse, number, deg);
}


void auton(void)
{
  intake.setVelocity(100, pct);
  belt.setVelocity(110, pct);
  driveForward(2000);
  belt.spin(reverse);
  driveForward(1000);
  belt.stop();
  driveBackward(500);
}

void driverControl(void)
{
  while (true) 
  {
        // use the joysticks to move forward, backward, and sideways  
        // but divide everything by 2 because the speed is too fast 
        LeftFront.spin(forward, (Controller1.Axis2.position() + Controller1.Axis1.position() + Controller1.Axis4.position()), percent);
        LeftBack.spin(forward, (Controller1.Axis2.position() - Controller1.Axis1.position() + Controller1.Axis4.position()), percent);
        RightFront.spin(forward, ((-Controller1.Axis2.position()) + Controller1.Axis1.position() + Controller1.Axis4.position()), percent);
        RightBack.spin(forward, ((-Controller1.Axis2.position()) - Controller1.Axis1.position() + Controller1.Axis4.position()), percent);

    
    if (Controller1.ButtonL2.pressing())
    {
        // spin the left and right intake opposite directions to suck in the ball
        intake.spin(forward, 110, percent);
        belt.spin(forward, 110, percent);
    }
    else if (Controller1.ButtonL1.pressing())
    {
        // spin the left and the right intake opposite directions to release the ball
        intake.spin(reverse, 110, percent);
        belt.spin(reverse, 110, percent);

    }
    else if (Controller1.ButtonR2.pressing())
    {
        // spin the spinners at the top of the robot the same to allow the ball to score
        FourBarLeft.spin(forward, 110, percent);
        FourBarRight.spin(forward, 110, percent);
    }
    else if (Controller1.ButtonR1.pressing())
    {
        // spin the spinners at the top of the robot the same to allow the ball to come out of the robot
        FourBarLeft.spin(reverse, 110, percent);
        FourBarRight.spin(reverse, 110, percent);
    }

    else
    {
        // stop all of the motors
        intake.stop();
        belt.stop();
        FourBarLeft.stop();
        FourBarRight.stop();
    }
  }
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //run the competition autonomous code
  Competition.autonomous(auton);
  //run the competition driver control code
  Competition.drivercontrol(driverControl);
  while (true)
  {
    vex::task::sleep(20);
  }
  
}