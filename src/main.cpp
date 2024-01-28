#include "main.h"
#include "ARMS/api.h"
#include "ARMS/config.h"
#include "ARMS/chassis.h"
#include "ARMS/odom.h"
#include "ARMS/pid.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// arms::init();
	catapult.init();
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
void competition_initialize() {
}

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
				.withMotors({-18, -19, -20}, {11, 12, 13})
				.withGains(
					{0.0016, 0.00000, 0}, // Distance controller gains
					{0.0016, 0.0000, 0}, // Turn controller gains
					{0.0016, 0.0000, 0.00000}  // Angle controller gains (helps drive straight)
				 	)
				.withDimensions({AbstractMotor::gearset::blue, (60.0 / 36.0)}, {{3.25_in, 14.6875_in}, imev5BlueTPR})
				.withOdometry()
				.buildOdometry();

	
	odomchas->setState({0_m,0_m,0_deg});
	// odomchas->turnToAngle(180_deg);
	odomchas->driveToPoint({6_in, 0_m}, false);
	// odomchas->driveToPoint({0_m, 1_m}, true);

    // arms::chassis::move(6.0);
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
    Controller controller;

    while (true) {
		drivebase.tankDrive(controller);
		intake.toggleIntake(controller);
		catapult.launch(controller);
		latch.shut(controller);
		climber.climb(controller);
		pros::delay(2);
    }
}