#ifndef SUBSYSTEMS_INTAKE_H
#define SUBSYSTEMS_INTAKE_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Intake
{
    public:
        Intake();
        void toggleIntake(Controller& controller);
        void moveIn();
        void stop();
        void moveout();
    private:
        MotorGroup intakeMotors = MotorGroup({16, -10});
        bool previousStateIn;
        bool currentStateIn;
        bool previousStateOut;
        bool currentStateOut;
        bool intakeIn;
        bool intakeOut;
};

#endif
