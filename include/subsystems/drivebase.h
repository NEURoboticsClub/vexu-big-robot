#ifndef SUBSYSTEMS_DRIVEBASE_H
#define SUBSYSTEMS_DRIVEBASE_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Drivebase
{
    public:
        Drivebase();
        void tankDrive(Controller& controller);
        void generatePath(std::initializer_list<okapi::PathfinderPoint> wayPoints, std::string pathID);
        void setTarget(std::string pathID);
        std::shared_ptr<OdomChassisController> chassisGeneric;
    private:
        std::shared_ptr<SkidSteerModel> chassisTank;
        std::shared_ptr<AsyncMotionProfileController> profileController;

};

#endif