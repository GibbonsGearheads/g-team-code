

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller cont;

motor Lmotor1 = motor(PORT5, ratio18_1, true); // Right motor 1 and 2 Left motor 1 and 2
motor Lmotor2 = motor(PORT10, ratio18_1, true);
motor Lmotor3 = motor(PORT11, ratio18_1, true);

motor Rmotor1 = motor(PORT2, ratio18_1, false);
motor Rmotor2 = motor(PORT3, ratio18_1, false);
motor Rmotor3 = motor(PORT12, ratio18_1, false);

motor_group Leftmotors = motor_group(Lmotor1, Lmotor2, Lmotor3);
motor_group Rightmotors = motor_group(Rmotor1, Rmotor2, Rmotor3);

motor Cmotor = motor(PORT4, ratio18_1, true); // Conveyor motor
// motor Smotor = motor(PORT9, ratio18_1, false);   // Spinning thing
motor Fmotor = motor(PORT1, ratio18_1, true);    // Firing motor
motor Endmotor = motor(PORT8, ratio18_1, false); // Endgame motor

/// letter buttons\\\\\\\\.Rightmotors.spin(fwd);
bool xbut;
bool bbut;
bool abut; // nothing so far;
bool ybut; // nothing so far;
//////bumpers\\\\\\.
bool r1but; // shoot
bool l1but; // conveyor
bool l2but; // turn left
bool r2but; // turn right
/// arrow keys\\\\\\ .
bool downbut; // roller down
bool upbut;   // roller up
bool rightbut;
bool leftbut;

bool fireOn = false; // toggle on
bool iFire = false;  // still pressing
int fireCooldown = 1;
int COOLDOWNTIME = 1;
bool Shutdown = false;
class customTimer
{
public:
    float time = 0;
    float maxTimer = 0;
    customTimer(float max)
    {
        maxTimer = max;
        reset();
    }
    void update()
    {
        if (time > 0)
        {
            time -= ((float)20 / (float)1000);
        }
    }
    void reset()
    {
        time += maxTimer;
    }
    bool done()
    {

        if (time <= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

void pre_auton(void)
{
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{
    /*
    customTimer backup_timer = customTimer(0.5);
    customTimer roller_timer = customTimer(0.6);
    customTimer moveup_timer = customTimer(0.55);
    float steps = 0;

    while (1)
    {
        Leftmotors.setVelocity(0, percent);
        Rightmotors.setVelocity(0, percent);

        backup_timer.update();

        Leftmotors.setVelocity(-2.5, percent);
        Rightmotors.setVelocity(-2.5, percent);

        wait(20, msec);

        Leftmotors.spin(fwd);
        Rightmotors.spin(fwd);

        if (backup_timer.done())
        {
            Leftmotors.setVelocity(0, percent);
            Rightmotors.setVelocity(0, percent);
            break;
        }
    }
    while (1)
    {
        Leftmotors.setVelocity(0, percent);
        Rightmotors.setVelocity(0, percent);
        Smotor.setVelocity(0, percent);

        roller_timer.update();

        Leftmotors.setVelocity(-2.5, percent);
        Rightmotors.setVelocity(-2.5, percent);

        Smotor.setVelocity(100, percent);

        wait(20, msec);

        Leftmotors.spin(fwd);
        Rightmotors.spin(fwd);
        Smotor.spin(fwd);
        if (roller_timer.done())
        {
            Leftmotors.setVelocity(0, percent);
            Rightmotors.setVelocity(0, percent);
            Smotor.setVelocity(0, percent);
            break;
        }
    }
    while (1)
    {
        Leftmotors.setVelocity(0, percent);
        Rightmotors.setVelocity(0, percent);

        moveup_timer.update();

        Leftmotors.setVelocity(10, percent);
        Rightmotors.setVelocity(10, percent);

        wait(20, msec);

        Leftmotors.spin(fwd);
        Rightmotors.spin(fwd);

        if (moveup_timer.done())
        {
            Leftmotors.setVelocity(0, percent);
            Rightmotors.setVelocity(0, percent);
            break;
        }
    }*/
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool spinOn = false;     // still spinning
bool buttondown = false; // stopped pressing button
bool rspinOn = false;
bool rbuttondown = false;

bool revOn = false;
bool revButtonDown = false;

bool endGameOut = false;

void usercontrol(void)
{
    customTimer rollerTimer = customTimer(0.5f);
    customTimer reverse_timer = customTimer(0.5f);

    while (1)
    {
        bool reversed = false;

        // checks if one of the used buttones are curently being pressed
        {
            l1but = cont.ButtonL1.pressing();
            l2but = cont.ButtonL2.pressing();
            r1but = cont.ButtonR1.pressing();
            r2but = cont.ButtonR2.pressing();

            xbut = cont.ButtonX.pressing();
            bbut = cont.ButtonB.pressing();
            abut = cont.ButtonA.pressing();
            ybut = cont.ButtonY.pressing();

            upbut = cont.ButtonUp.pressing();
            downbut = cont.ButtonDown.pressing();
            leftbut = cont.ButtonLeft.pressing();
            rightbut = cont.ButtonRight.pressing();
        }
        // code for movement
        {
            if ((cont.Axis2.position() > 5) || ((cont.Axis2.position() < -5)))
            {
                if (!endGameOut)
                {
                    Rightmotors.setVelocity(cont.Axis2.position(), percent);
                    if ((cont.Axis2.position() >= 100))
                    {
                        Rightmotors.setVelocity(100, percent);
                    }
                    if ((cont.Axis2.position() <= -100))
                    {
                        Rightmotors.setVelocity(-100, percent);
                    }
                    {
                        Rightmotors.setVelocity(-100, percent);
                    }
                    if ((cont.Axis2.position() <= -100))
                    {
                        Rightmotors.setVelocity(100, percent);
                    }
                }
            }
            else
            {
                Rightmotors.setVelocity(0, percent);
            }
            if ((cont.Axis3.position() > 5) || ((cont.Axis3.position() < -5)))
            {
                Leftmotors.setVelocity(cont.Axis3.position(), percent);
                if ((cont.Axis3.position() >= 100))
                {
                    Leftmotors.setVelocity(100, percent);
                }
                if ((cont.Axis3.position() <= -100))
                {
                    Leftmotors.setVelocity(-100, percent);
                }
            }
            else
            {
                Leftmotors.setVelocity(0, percent);
            }
        }
        // code for firing
        {
            if (fireCooldown > 0)
            {
                fireCooldown -= 0.02;
            }
            else
            {
                fireCooldown = COOLDOWNTIME;
            }
            if (r1but && fireCooldown <= 0 && !iFire)
            {
                iFire = true;
                fireOn = !fireOn;
                fireCooldown = COOLDOWNTIME;
            }
            if (iFire)
            {
                fireCooldown = COOLDOWNTIME;
            }
            if (!r1but)
            {
                if (iFire)
                {
                    iFire = false;
                }
            }
            if (fireOn)
            {
                Fmotor.setVelocity(100, percent);
                // fmotor
            }
            else
            {
                Fmotor.setVelocity(0, percent);
            }
        }
        // conveyor
        {
            if (l1but)
            {
                Cmotor.setVelocity(100, percent);
            }
            else if (xbut)
            {
                Cmotor.setVelocity(-100, percent); //
            }
            else
            {
                Cmotor.setVelocity(0, percent);
            }

            // code for auto turning
            if (r2but)
            {
                Leftmotors.setVelocity(90, percent);
                Rightmotors.setVelocity(-90, percent);
            }
            if (l2but)
            {
                Leftmotors.setVelocity(-90, percent);
                Rightmotors.setVelocity(90, percent);
            }
        }
        // code for reversed mode
        {
            if (!revButtonDown)
            {
                reverse_timer.update();
            }
            if (leftbut && reverse_timer.done() && !revButtonDown)
            {
                revOn = revOn;
                revButtonDown = true;
                reverse_timer.reset();
            }
            if (!leftbut)
            {
                if (revButtonDown)
                {
                    revButtonDown = false;
                }
            }
            if (revOn)
            {
                Lmotor1.setReversed(false);
                Lmotor2.setReversed(false);
                Rmotor1.setReversed(true);
                Rmotor2.setReversed(true);
            }
            else
            {
                Lmotor1.setReversed(true);
                Lmotor2.setReversed(true);
                Rmotor1.setReversed(false);
                Rmotor2.setReversed(false);
            }
        }
        Fmotor.spin(fwd);
        Cmotor.spin(fwd);
        wait(20, msec);
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();
    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        wait(100, msec);
    }
}
