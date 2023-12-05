#include "DrivetrainTask.h"

void tickDrive(DriveState *state); // Arduino bug workaround
void tickDrive(DriveState *state) {
  switch (*state) {
  case DRIVE_INIT:
    if (forceMove) {
      *state = DRIVE_FORCE;
      break;
    } else if (isRoaming) {
      *state = DRIVE_ROAM;
      break;
    }
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);

    stop();
    *state = DRIVE_IDLE;
    break;
  case DRIVE_IDLE:
    if (forceMove) {
      *state = DRIVE_FORCE;
      break;
    } else if (isRoaming) {
      *state = DRIVE_ROAM;
      break;
    }
    if (destloc[0] != currloc[0] || destloc[1] != currloc[1]) {
      targetloc[0] = destloc[0];
      targetloc[1] = destloc[1];
      *state = DRIVE_SEARCH;
    }
    break;
  case DRIVE_SEARCH:
    if (forceMove) {
      *state = DRIVE_FORCE;
      break;
    } else if (isRoaming) {
      *state = DRIVE_ROAM;
      break;
    }
    if (targetloc[0] == currloc[0] && targetloc[1] == currloc[1]) {
      *state = DRIVE_IDLE;
    } else {
      *state = DRIVE_GOTO;
    }
    break;
  case DRIVE_GOTO:
    if (forceMove) {
      *state = DRIVE_FORCE;
      break;
    } else if (isRoaming) {
      *state = DRIVE_ROAM;
      break;
    }
    if (destloc[0] == currloc[0] && destloc[1] == currloc[1] || targetloc[0] != destloc[0] || targetloc[1] != destloc[1]) {
      *state = DRIVE_IDLE;
    }
    break;
  case DRIVE_FORCE:
    if (!forceMove) {
      if (isRoaming) {
        *state = DRIVE_ROAM;
      } else {
        *state = DRIVE_IDLE;
      }
    }
    break;
  case DRIVE_ROAM:
    if (forceMove) {
      *state = DRIVE_FORCE;
      break;
    } else if (!isRoaming) {
      *state = DRIVE_IDLE;
      break;
    }
  default:
    if (forceMove) {
      *state = DRIVE_FORCE;
      break;
    } else if (isRoaming) {
      *state = DRIVE_ROAM;
      break;
    }
    *state = DRIVE_INIT;
    break;
  }
  switch (*state) {
  case DRIVE_INIT:
    stop();
    break;
  case DRIVE_IDLE:
    stop();
    break;
  case DRIVE_SEARCH:
    break;
  case DRIVE_GOTO:

    if (currloc[0] < targetloc[0]) {
      alldrive(100, 100);
      currloc[0]++;
    } else if (currloc[0] > targetloc[0]) {
      alldrive(-100, -100);
      currloc[0]--;
    } else if (currloc[1] < targetloc[1]) {
      alldrive(100, -100);
      currloc[1]++;
    } else if (currloc[1] > targetloc[1]) {
      alldrive(-100, 100);
      currloc[1]--;
    }
    Serial.println("Moving to (" + String(currloc[0]) + ", " + String(currloc[1]) + ")");
    break;
  case DRIVE_FORCE:
    Serial.println("Left: " + String(forceSpeeds[0]) + " Right: " + String(forceSpeeds[1]));
    alldrive(forceSpeeds);
  case DRIVE_ROAM:
    randVal = random(1000);
    if (randVal == 0 || (distance < 5 && randVal < 500)) {
      roamingSpeeds[0] = -100;
      roamingSpeeds[1] = 100;
    } else if (randVal == 1 || (distance < 5)) {
      roamingSpeeds[0] = 100;
      roamingSpeeds[1] = -100;
    } else if (randVal < 20) {
      roamingSpeeds[0] = 100;
      roamingSpeeds[1] = 100;
    }
    alldrive(roamingSpeeds);
  default:
    break;
  }
}

void LDrive(int speed) {
  speed = -speed;
  if (speed > 0) {
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
  } else if (speed < 0) {
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
  } else {
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
  }
}

void RDrive(int speed) {
  if (speed > 0) {
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
  } else if (speed < 0) {
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
  } else {
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
  }
}

void alldrive(int speeds[]) {
  LDrive(speeds[0]);
  RDrive(speeds[1]);
}

void alldrive(int lspeed, int rspeed) {
  LDrive(lspeed);
  RDrive(rspeed);
}

void drive(int speed) {
  LDrive(speed);
  RDrive(speed);
}

void stop() {
  drive(0);
}