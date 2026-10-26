#pragma once
#include "vex.h"

using namespace vex;

namespace fred{
    // Controller
    controller Controller = controller();

    // Sensors
    inertial inertialSensor = inertial(PORT10, right);

    // Motors

    // Drivetrain motors
    motor leftFrontMotor = motor (
        PORT1,
        ratio6_1,
        false
    );
    motor leftBackMotor = motor (
        PORT8,
        ratio6_1,
        false
    );
    motor rightFrontMotor = motor (
        PORT3,
        ratio6_1,
        true
    );
    motor rightBackMotor = motor (
        PORT5,
        ratio6_1,
        true
    );

    // Motor Groups
    motor_group leftDrive = motor_group (
        leftFrontMotor,
        leftBackMotor
    );
    motor_group rightDrive = motor_group (
        rightFrontMotor,
        rightBackMotor
    );

    // Smartdrive
    smartdrive smartDrivetrain = smartdrive (
        leftDrive,
        rightDrive,
        inertialSensor,
        260,
        429, // verify
        305,
        mm,
        1.0
    );
}