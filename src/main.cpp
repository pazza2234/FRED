#include "devices.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Global variables
double gear;

// Artificial gearshift
void gearDown() {
    gear = 3;
}

void gearUp() {
    gear = 1.5;
}


void pre_auton(void) {
    // Callibrate sensors
    fred::inertialSensor.calibrate();
    while (fred::inertialSensor.isCalibrating()) {
        wait(20, msec);
    }
    fred::inertialSensor.resetHeading();
    fred::inertialSensor.resetRotation();
    return;
}


void autonomous(void) {
}


/**
 * @brief user control function
 */
void usercontrol(void) {
    gear = 3;
    fred::leftDrive.setVelocity(0, percent);
    fred::rightDrive.setVelocity(0, percent);

    fred::leftDrive.spin(forward);
    fred::rightDrive.spin(forward);
    while (1) {

        // Movement
        fred::leftDrive.setVelocity(fred::Controller.Axis2.position() / gear * -1, percent);
        fred::rightDrive.setVelocity(fred::Controller.Axis3.position() / gear * -1, percent);

        // Artificial gearshift
        // important note is how it does not effect actual power
        // it only changes how easy it is to control
        fred::Controller.ButtonDown.pressed(gearDown);
        fred::Controller.ButtonUp.pressed(gearUp);
        wait(20, msec); // Sleep the task for a short amount of time to
                        // prevent wasted resources.
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
    }
}
