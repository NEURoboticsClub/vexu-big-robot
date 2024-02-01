#include "subsystems/drivebase.h"

Drivebase::Drivebase(){
    MotorGroup motorsLeft = {-12, -13};
    MotorGroup motorsRight = {18, 19};
    motorsLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
    motorsRight.setBrakeMode(AbstractMotor::brakeMode::brake);

    chassisGeneric = 
        ChassisControllerBuilder()
				.withMotors(motorsLeft, motorsRight)
				.withGains(
					{0.0027, 0.0175, 0.000085}, // Distance controller gains
					{0.0001, 0.0000, 0}, // Turn controller gains
					{0.0001, 0.0000, 0.00000}  // Angle controller gains (helps drive straight)
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

void Drivebase::init() {
    chassisTank->setMaxVelocity(400);
    chassisGeneric->setMaxVelocity(150);
    chassisGeneric->setState({0_m, 0_m, 0_deg});
    profileController->reset();
}

void Drivebase::generatePath(std::initializer_list<okapi::PathfinderPoint> wayPoints, std::string pathID){
    profileController->generatePath(wayPoints, pathID);
}

void Drivebase::setTarget(std::string pathID){
    profileController->setTarget(pathID);
}

void Drivebase::removePath(std::string pathID){
    profileController->removePath(pathID);
}

void Drivebase::waitUntilSettled(){
    profileController->waitUntilSettled();
}

void Drivebase::driveToPoint(okapi::Point point){
    chassisGeneric->driveToPoint(point);
}

void Drivebase::turnToAngle(okapi::QAngle angle){
    chassisGeneric->turnToAngle(angle);
}

void Drivebase::turnAngle(okapi::QAngle angle){
    chassisGeneric->turnAngle(angle);
}

void Drivebase::moveDistance(okapi::QLength distance){
    chassisGeneric->moveDistance(distance);
}