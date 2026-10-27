#include "vex.h"
#include "usercontrol.h"
#include "devices.h"

// Global variables
double gear = 3;

// true  = arcade
// false = tank
bool drivetype = false;

// Artificial gearshift
void gearDown() {
    gear = 3;
}

void gearUp() {
    gear = 1.5;
}

void tankdrive() {
    // Movement
    // I am not going to ask why we do that gear bs, I mean it gets clamped anyways so
    // that just creates an end deadzone no?
    fred::leftDrive.setVelocity(fred::Controller.Axis2.position() / gear * -1, vex::percent);
    fred::rightDrive.setVelocity(fred::Controller.Axis3.position() / gear * -1, vex::percent);

    fred::Controller.ButtonDown.pressed(gearDown);
    fred::Controller.ButtonUp.pressed(gearUp);
}


void arcadedrive() {
    const double forward = fred::Controller.Axis3.position();
    const double turn    = fred::Controller.Axis4.position();

    const double left  = forward + turn;
    const double right = forward - turn;

    // NOTE: if above 100%, it is just set to that later
    // Do not worry that it can go above. tis is fine
    fred::leftDrive.setVelocity(left,  vex::percent);
    fred::leftDrive.setVelocity(right, vex::percent);
}


void controlDrivetrain() {
    vex::this_thread::setPriority(0); // Highest - dont let any lost input

    fred::leftDrive.setVelocity(0, vex::percent);
    fred::rightDrive.setVelocity(0, vex::percent);

    fred::leftDrive.spin(vex::forward);
    fred::rightDrive.spin(vex::forward);

    fred::Controller.ButtonA.pressed([](){drivetype=!drivetype;});
    while(1){
        drivetype ? arcadedrive() : tankdrive();
        vex::this_thread::sleep_for(20); // msec
    }
}


void fred_usercontrol(void) {
    vex::thread driveThread = vex::thread(controlDrivetrain);
}