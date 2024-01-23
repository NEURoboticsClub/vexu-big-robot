#include "main.h"
#include "ARMS/config.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// arms::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	std::shared_ptr<OdomChassisController> odomchas =
		ChassisControllerBuilder()
				.withMotors({2,-3},{4,-5},{17,-18},{11,-12})
				.withSensors(
					RotationSensor{7, true}, // left encoder in ADI ports A & B
					RotationSensor{8, true},  // right encoder in ADI ports C & D (reversed)
					RotationSensor{19}  // middle encoder in ADI ports E & F
				)
				.withGains(
					{0.0004, 0.00005, 0}, // Distance controller gains
					{0.0006, 0.0003, 0}, // Turn controller gains
					{0.0006, 0.0003, 0.00000}  // Angle controller gains (helps drive straight)
				 	)
				.withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 10.5_in, 5.46_in, 2.75_in}, 360})
				.withOdometry()
				.buildOdometry();

		// std::shared_ptr<XDriveModel> xModel = std::dynamic_pointer_cast<XDriveModel>(odomchas->getModel());
	
	odomchas->setState({0_m,0_m,0_deg});
	// odomchas->turnToAngle(180_deg);
	odomchas->driveToPoint({5_in, 0_m}, false);
	// odomchas->driveToPoint({0_m, 1_m}, true);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	std::shared_ptr<ChassisController> drive = 
		ChassisControllerBuilder()
			.withMotors({2,-3},{4,-5},{17,-18},{11,-12})
			.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
			.build();
		std::shared_ptr<XDriveModel> xModel = std::dynamic_pointer_cast<XDriveModel>(drive->getModel());

		Controller controller;
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton intakeOutButton(ControllerDigital::L1);
		Motor intakeMotor(15);		
		
	while (true) {
		xModel->xArcade(controller.getAnalog(ControllerAnalog::leftX), controller.getAnalog(ControllerAnalog::leftY),controller.getAnalog(ControllerAnalog::rightX));

		if (intakeInButton.isPressed()) {
            intakeMotor.moveVelocity(200);
        } else if (intakeOutButton.isPressed()) {
			intakeMotor.moveVelocity(-200);
        } else {
			intakeMotor.moveVoltage(0);
        }
	}
}