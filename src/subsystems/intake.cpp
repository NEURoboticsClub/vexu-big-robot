#include "subsystems/intake.h"

Intake::Intake(){
    previousStateIn = false;
    previousStateOut = false;
    currentStateIn = false;
    currentStateOut = false;
    intakeIn = false;
    intakeOut = false;
}

void Intake::toggleIntake(Controller& controller, bool catUp){
    currentStateIn = controller.getDigital(ControllerDigital::R1);
    currentStateOut = controller.getDigital(ControllerDigital::L1);
    
    if(currentStateIn != previousStateIn){
        if(currentStateIn){
            intakeIn = !intakeIn;
            intakeOut = false;
        }
        previousStateIn = currentStateIn;
    }

    if(currentStateOut != previousStateOut){
        if(currentStateOut){
            intakeOut = !intakeOut;
            intakeIn = false;
        }
        previousStateOut = currentStateOut;
    }

    if (catUp) {
        intakeMotors.moveVelocity(0);
    }
    else if(intakeIn){
        intakeMotors.moveVelocity(600);
    }
    else if(intakeOut){
        intakeMotors.moveVelocity(-600);
    }
    else{
        intakeMotors.moveVelocity(0);
    }
}

void Intake::moveIn(){
    intakeMotors.moveVelocity(300);
}
void Intake::stop(){
    intakeMotors.moveVelocity(0);
}
void Intake::moveout(){
    intakeMotors.moveVelocity(-600);
}