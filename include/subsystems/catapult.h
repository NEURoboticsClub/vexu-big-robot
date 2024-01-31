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
        Motor catapultMotorLeft = Motor(-9);
        Motor catapultMotorRight = Motor(17);
        pros::Rotation catapultSensor = pros::Rotation(8);
        double sensorValue;
        int countdown;
        bool toLaunch;
        bool launching;
};

#endif
