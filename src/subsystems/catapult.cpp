#include "subsystems/catapult.h"

Catapult::Catapult(){
    catapultSensor.reset_position();
    catapultSensor.set_data_rate(5);
    sensorValue = 0;
    countdown = 500;
    toLaunch = false;
    launching = false;
    toBlock = false;
    blocking = false;
    previousState = false;
    currentState = false;
    isDrawing = false;
}

void Catapult::init() {
    catapultSensor.reset_position();
    catapultSensor.set_data_rate(2);
    sensorValue = 0;
    countdown = 500;
    catapultMotorLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
    catapultMotorRight.setBrakeMode(AbstractMotor::brakeMode::hold);
    previousState = false;
    currentState = false;
    isDrawing = false;
}

void Catapult::reset(Controller& controller) {
    if (controller.getDigital(ControllerDigital::up)) {
        catapultSensor.reset_position();
        catapultSensor.set_data_rate(5);
        sensorValue = 0;
        countdown = 500;
        toLaunch = false;
        launching = false;
        toBlock = false;
        blocking = false;
        previousState = false;
        currentState = false;
        isDrawing = false;
    }
}

void Catapult::launch(Controller& controller){
    if (!blocking) {
        if (launching) {
            sensorValue = -1 * catapultSensor.get_position();
            if (countdown > 0) {
                countdown--;
            } 
            else {
                if (sensorValue < 400) {
                catapultMotorLeft.moveVelocity(0);
                catapultMotorRight.moveVelocity(0);
                launching = false;
                }
            }
        }
        if(!launching) {
            toLaunch = controller.getDigital(ControllerDigital::A);
            if (toLaunch) {
                launching = true;
                countdown = 500;
                catapultMotorLeft.moveVelocity(200);
                catapultMotorRight.moveVelocity(200);
            }
        }
    }
}

void Catapult::block(Controller& controller) {
    if (!launching) {
        if (blocking) {
            sensorValue = -1 * catapultSensor.get_position();
            if (countdown > 0) {
                countdown--;
            } 
            else {
                if (sensorValue < 2500) {
                catapultMotorLeft.moveVelocity(0);
                catapultMotorRight.moveVelocity(0);
                blocking = false;
                }
            }
        }
        if(!blocking) {
            toBlock = controller.getDigital(ControllerDigital::B);
            if (toBlock) {
                blocking = true;
                countdown = 500;
                catapultMotorLeft.moveVelocity(200);
                catapultMotorRight.moveVelocity(200);
            }
        }
    }
}

void Catapult::launch() {
    catapultMotorLeft.moveVelocity(200);
    catapultMotorRight.moveVelocity(200);
    pros::delay(1000);
    sensorValue = -1 * catapultSensor.get_position();
    while (sensorValue >= 400) {
        pros::delay(2);
        sensorValue = -1 * catapultSensor.get_position();
    }
    catapultMotorLeft.moveVelocity(0);
    catapultMotorRight.moveVelocity(0);
}

void Catapult::block() {
    catapultMotorLeft.moveVelocity(200);
    catapultMotorRight.moveVelocity(200);
    pros::delay(1000);
    sensorValue = -1 * catapultSensor.get_position();
    while (sensorValue >= 2500) {
        pros::delay(2);
        sensorValue = -1 * catapultSensor.get_position();
    }
    catapultMotorLeft.moveVelocity(0);
    catapultMotorRight.moveVelocity(0);
}

void Catapult::manual(Controller& controller) {
    // currentState = controller.getDigital(ControllerDigital::down);
    
    // if (currentState != previousState) {
    //     if (currentState) {
    //         isDrawing = !isDrawing;
    //     }
    //     previousState = currentState;
    // }

    isDrawing = controller.getDigital(ControllerDigital::down);

    if (isDrawing) {
        launching = false;
        blocking = false;
        catapultMotorLeft.moveVelocity(100);
        catapultMotorRight.moveVelocity(100);
    } else if (!launching && !blocking) {
        catapultMotorLeft.moveVelocity(0);
        catapultMotorRight.moveVelocity(0);
    }
}

bool Catapult::isUp() {
    return launching || blocking || isDrawing;
}