#include "subsystems/catapult.h"

Catapult::Catapult(){
    catapultSensor.reset();
    sensorValue = catapultSensor.get();
    lastSensorValue = catapultSensor.get();
    toLaunch = false;
    launching = false;
}

void Catapult::launch(Controller& controller){
    if(!launching) {
        toLaunch = controller.getDigital(ControllerDigital::A);
        if (toLaunch) {
            launching = true;
            catapultMotor.moveVelocity(200);
        }
    }

    if (launching) {
        lastSensorValue = sensorValue;
        sensorValue = catapultSensor.get();
        if (sensorValue > 330) {
            catapultMotor.moveVelocity(20);
        }
        if (sensorValue < lastSensorValue) {
            catapultMotor.moveVelocity(0);
            launching = false;
        }
    }
}