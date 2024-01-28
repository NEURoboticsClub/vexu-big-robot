#ifndef SUBSYSTEMS_SUBSYSTEMS_H
#define SUBSYSTEMS_SUBSYSTEMS_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"
#include "subsystems/drivebase.h"
#include "subsystems/intake.h"
#include "subsystems/catapult.h"
#include "subsystems/latch.h"
#include "subsystems/climber.h"

Drivebase drivebase;
Intake intake;
Catapult catapult;
Climber climber;
Latch latch;

#endif