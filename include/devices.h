#pragma once
#include "vex.h"

namespace fred{
    // Brain
    extern vex::brain Brain;   

    // Controller
    extern vex::controller Controller;

    // Sensors
    extern vex::inertial inertialSensor;

    // Motors

    // Drivetrain motors
    extern vex::motor leftFrontMotor;
    extern vex::motor leftBackMotor;
    extern vex::motor rightFrontMotor;
    extern vex::motor rightBackMotor;

    // Motor Groups
    extern vex::motor_group leftDrive;
    extern vex::motor_group rightDrive;

    // pneumatics 
    extern vex::pneumatics claw;
}