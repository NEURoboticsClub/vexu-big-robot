#include "subsystems/catapult.h"

Catapult::Catapult(){
    catapultSensor.reset_position();
    catapultSensor.set_data_rate(5);
    sensorValue = 0;
    toLaunch = false;
    launching = false;
}

void Catapult::init() {
    catapultSensor.reset_position();
    catapultSensor.set_data_rate(5);
    sensorValue = 0;
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
        sensorValue = catapultSensor.get_position();
        // std::cout << "sensorValue: " << sensorValue << std::endl;
        if (sensorValue > 36000) {
            catapultSensor.reset_position();
            sensorValue = 0;
            catapultMotor.moveVelocity(0);
            launching = false;
        }
    }
}