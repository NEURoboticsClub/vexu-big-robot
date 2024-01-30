#ifndef SUBSYSTEMS_CLIMBER_H
#define SUBSYSTEMS_CLIMBER_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Climber
{
    public:
        Climber();
        void climb(Controller& controller);
    private:
        MotorGroup climbingMotors = MotorGroup({2, -3});
        bool previousState;
        bool currentState;
        bool isClimbing;
};

#endif
