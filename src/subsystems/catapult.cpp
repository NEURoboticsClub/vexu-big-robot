#include "subsystems/catapult.h"

Catapult::Catapult(){
    catapultSensor.reset_position();
    catapultSensor.set_data_rate(5);
    sensorValue = 0;
    countdown = 500;
    toLaunch = false;
    launching = false;
}

void Catapult::init() {
    catapultSensor.reset_position();
    catapultSensor.set_data_rate(5);
    sensorValue = 0;
    countdown = 500;
}

void Catapult::launch(Controller& controller){
    if (launching) {
        sensorValue = -1 * catapultSensor.get_position();
        std::cout << "sensorValue: " << sensorValue << std::endl;
        if (countdown > 0) {
            countdown--;
        } else {
            if (sensorValue < 200) {
            catapultMotor.moveVelocity(0);
            launching = false;
            }
        }
    }
    if(!launching) {
        toLaunch = controller.getDigital(ControllerDigital::A);
        if (toLaunch) {
            launching = true;
            countdown = 500;
            catapultMotor.moveVelocity(200);
        }
    }
}