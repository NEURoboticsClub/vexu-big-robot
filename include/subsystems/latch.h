#ifndef SUBSYSTEMS_LATCH_H
#define SUBSYSTEMS_LATCH_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Latch
{
    public:
        Latch();
        void shut(Controller& controller);
    private:
        Motor latchMotor = Motor({-4});
        bool previousState;
        bool currentState;
        bool isShutting;
};

#endif
