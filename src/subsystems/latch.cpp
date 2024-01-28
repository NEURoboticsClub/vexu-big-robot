#include "subsystems/latch.h"

Latch::Latch(){
    previousState = false;
    currentState = false;
    isShutting= false;
}

void Latch::shut(Controller& controller){
    currentState = controller.getDigital(ControllerDigital::X);
    
    if (currentState != previousState) {
        if (currentState) {
            isShutting = !isShutting;
        }
        previousState = currentState;
    }

    if (isShutting) {
        latchMotor.moveVelocity(300);
    } else {
        latchMotor.moveVelocity(0);
    }
}