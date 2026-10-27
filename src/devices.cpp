#include "vex.h"
#include "devices.h"

using namespace vex;

namespace fred {
    brain Brain = brain();
    controller Controller = controller();
    inertial inertialSensor = inertial(PORT10, right);

    motor leftFrontMotor = motor(PORT1, ratio6_1, false);
    motor leftBackMotor = motor(PORT8, ratio6_1, false);
    motor rightFrontMotor = motor(PORT3, ratio6_1, true);
    motor rightBackMotor = motor(PORT5, ratio6_1, true);

    motor_group leftDrive = motor_group(leftFrontMotor, leftBackMotor);
    motor_group rightDrive = motor_group(rightFrontMotor, rightBackMotor);

    pneumatics claw = pneumatics(Brain.ThreeWirePort.A);
}
