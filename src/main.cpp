#include "vex.h"
#include "devices.h"
#include "usercontrol.h"
#include "auton.h"

// A global instance of competition
vex::competition Competition;


void pre_auton(void) {
    // Callibrate sensors
    fred::inertialSensor.calibrate();
    while (fred::inertialSensor.isCalibrating()) {
        vex::wait(20, vex::msec);
    }
    fred::inertialSensor.resetHeading();
    fred::inertialSensor.resetRotation();
    return;
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(fred_autonomous);
    Competition.drivercontrol(fred_usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        vex::wait(100, vex::msec);
    }
}
