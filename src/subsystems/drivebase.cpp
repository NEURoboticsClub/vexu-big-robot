#include "subsystems/drivebase.h"

Drivebase::Drivebase(){
    MotorGroup motorsLeft = {-18, -19, -20};
    MotorGroup motorsRight = {11, 12, 13};

    chassisGeneric = 
        ChassisControllerBuilder()
				.withMotors(motorsLeft, motorsRight)
				.withGains(
					{0.0016, 0.00000, 0}, // Distance controller gains
					{0.0016, 0.0000, 0}, // Turn controller gains
					{0.0016, 0.0000, 0.00000}  // Angle controller gains (helps drive straight)
				 	)
				.withDimensions({AbstractMotor::gearset::blue, (60.0 / 36.0)}, {{3.25_in, 14.6875_in}, imev5BlueTPR})
				.withOdometry()
				.buildOdometry();
    
    chassisTank = std::dynamic_pointer_cast<SkidSteerModel>(chassisGeneric->getModel());

    profileController =
        okapi::AsyncMotionProfileControllerBuilder()
            .withLimits({1.0*0.6, 2.0*0.6, 10.0*0.6})
            .withOutput(chassisGeneric)
            .buildMotionProfileController();    
}

void Drivebase::tankDrive(Controller& controller){
    chassisTank->tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY));
}

void Drivebase::generatePath(std::initializer_list<okapi::PathfinderPoint> wayPoints, std::string pathID){
    profileController->generatePath(wayPoints, pathID);
}

void Drivebase::setTarget(std::string pathID){
    profileController->setTarget(pathID);
}
