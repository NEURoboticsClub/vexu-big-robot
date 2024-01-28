#include "subsystems/climber.h"

Climber::Climber(){
    previousState = false;
    currentState = false;
    isClimbing= false;
}

void Climber::climb(Controller& controller){
    currentState = controller.getDigital(ControllerDigital::B);
    
    if (currentState != previousState) {
        if (currentState) {
            isClimbing = !isClimbing;
        }
        previousState = currentState;
    }

    if (isClimbing) {
        climbingMotors.moveVelocity(300);
    } else {
        climbingMotors.moveVelocity(0);
    }
}