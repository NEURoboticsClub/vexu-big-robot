#ifndef SUBSYSTEMS_CATAPULT_H
#define SUBSYSTEMS_CATAPULT_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Catapult
{
    public:
        Catapult();
        void init();
        void launch(Controller& controller);
    private:
        Motor catapultMotor = Motor(-9);
        pros::Rotation catapultSensor = pros::Rotation(8);
        double sensorValue;
        bool toLaunch;
        bool launching;
};

#endif
