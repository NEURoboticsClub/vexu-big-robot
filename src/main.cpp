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

	drivebase.init();
	catapult.init();
	for (int i = 0; i < 6; i++) {
		drivebase.moveDistance(4_ft);
		drivebase.turnAngle(182_deg);
	}

	// drivebase.moveDistance(2.4_ft);
	// drivebase.turnAngle(130_deg);
	// catapult.block();
	// intake.moveIn();
	// drivebase.moveDistance(1.85_ft);
	// pros::delay(500);
	// intake.stop();
	// drivebase.moveDistance(-0.5_ft);
	// drivebase.turnAngle(95_deg);
	// drivebase.moveDistance(-13_in);
	// drivebase.turnAngle(-50_deg);
	// drivebase.moveDistance(-6_ft);
	// drivebase.turnAngle(125_deg);
	// drivebase.moveDistance(1.5_ft);
	// drivebase.turnAngle(-15_deg);
	// drivebase.moveDistance(4_in);
	// intake.moveout();
	// pros::delay(500);
	// intake.stop();
	// drivebase.turnAngle(-15_deg);
	// drivebase.moveDistance(-3_in);
	// drivebase.turnAngle(205_deg);
	// drivebase.moveDistance(-1.5_ft);
	// drivebase.turnAngle(20_deg);
	// drivebase.moveDistance(1.25_ft);
	// drivebase.turnAngle(-90_deg);
	// intake.moveIn();
	// drivebase.moveDistance(14_in);
	// pros::delay(500);
	// intake.stop();
	// drivebase.moveDistance(-3_in);
	// drivebase.turnAngle(-90_deg);
	// drivebase.moveDistance(9_in);
	// drivebase.turnAngle(-45_deg);
	// drivebase.moveDistance(3_in);
	// intake.moveout();
	// pros::delay(500);
	// drivebase.moveDistance(-6_in);
	// intake.stop();
	// drivebase.turnAngle(215_deg);
	// drivebase.moveDistance(-1.5_ft);
	// drivebase.turnAngle(30_deg);
	// drivebase.moveDistance(1.5_ft);
	// drivebase.turnAngle(45_deg);
	// drivebase.moveDistance(3.5_ft);
	// drivebase.turnAngle(45_deg);
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
	// catapult.init();

    while (true) {
		drivebase.tankDrive(controller);
		intake.toggleIntake(controller, catapult.isUp());
		catapult.manual(controller);
		catapult.launch(controller);
		catapult.block(controller);
		catapult.reset(controller);
		latch.shut(controller);
		climber.climb(controller);
		pros::delay(2);
    }
}