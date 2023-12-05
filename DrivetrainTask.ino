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
    if (targetloc[0] == currloc[0] && targetloc[1] == currloc[1] || !(fieldMap[targetloc[0]][targetloc[1]] > 0)) {
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
    for (int iter = 1; iter < fieldsize * fieldsize; ++iter) {
      for (int i = 0; i < fieldsize; ++i) {
        for (int j = 0; j < fieldsize; ++j) {
          if (fieldMap[i][j] > 0) {
            fieldMap[i][j] = 0;
          }
        }
      }
    }
    fieldMap[targetloc[1]][targetloc[0]] = 1;
    for (int iter = 1; iter < fieldsize * fieldsize; ++iter) {
      for (int i = 0; i < fieldsize; ++i) {
        for (int j = 0; j < fieldsize; ++j) {
          if (fieldMap[i][j] == 0) {
            if (i < fieldsize - 1 && fieldMap[i + 1][j] == iter) {
              fieldMap[i][j] = iter + 1;
            } else if (i > 0 && fieldMap[i - 1][j] == iter) {
              fieldMap[i][j] = iter + 1;
            } else if (j < fieldsize - 1 && fieldMap[i][j + 1] == iter) {
              fieldMap[i][j] = iter + 1;
            } else if (j > 0 && fieldMap[i][j - 1] == iter) {
              fieldMap[i][j] = iter + 1;
            }
          }
        }
      }
    }
    // for (int i = 0; i < fieldsize; ++i) {
    //   Serial.print("[");
    //   for (int j = 0; j < fieldsize; ++j) {
    //     Serial.print(fieldMap[i][j]);
    //     if (j < fieldsize-1) {
    //       Serial.print(", ");
    //     }
    //   }
    //   Serial.println("]");
    // }
    if (fieldMap[currloc[1]][currloc[0]] == 0) {
      Serial.println("No path found");
      break;
    }
    break;
  case DRIVE_GOTO:
    int nextPath = fieldMap[currloc[1]][currloc[0]] - 1;
    int godir;
    Serial.println("Next path: " + String(nextPath));
    Serial.println("Current location: (" + String(currloc[0]) + ", " + String(currloc[1]) + ")");
    if (currloc[1] < fieldsize && fieldMap[currloc[1] + 1][currloc[0]] == nextPath || currloc[1] < 0) {
      Serial.println("Down");
      if (direction < 1.9) {
        godir = 1;
      } else if (direction > 2.1) {
        godir = -1;
      } else {
        godir = 0;
        direction = 2;
      }
    } else if (currloc[1] > 0 && fieldMap[currloc[1] - 1][currloc[0]] == nextPath || currloc[1] > fieldsize) {
      Serial.println("Up");
      if (direction > 0.1 && direction < 2.0) {
        godir = -1;
      } else if (direction >= 2.0 && direction < 3.9) {
        godir = 1;
      } else {
        godir = 0;
        direction = 0;
      }
    } else if (currloc[0] < fieldsize && fieldMap[currloc[1]][currloc[0] + 1] == nextPath || currloc[0] < 0) {
      Serial.println("Right");
      if (direction < 0.9 || direction > 3) {
        godir = 1;
      } else if (direction > 1.1 && direction <= 3) {
        godir = -1;
      } else {
        godir = 0;
        direction = 1;
      }
    } else if (currloc[0] > 0 && fieldMap[currloc[1]][currloc[0] - 1] == nextPath || currloc[0] > fieldsize) {
      Serial.println("Left");
      if (direction < 2.9 && direction > 1) {
        godir = 1;
      } else if (direction > 3.1 || direction <= 1) {
        godir = -1;
      } else {
        godir = 0;
        direction = 3;
      }
    }
    if (godir == 0) {
      drive(100);
      if (direction == 0) {
        currlocprec[1] -= 0.5;
      } else if (direction == 1) {
        currlocprec[0] += 0.5;
      } else if (direction == 2) {
        currlocprec[1] += 0.5;
      } else if (direction == 3) {
        currlocprec[0] -= 0.5;
      }
    } else if (godir == 1) {
      alldrive(100, -100);
      direction += 0.25;
      if (direction >= 4) {
        direction -= 4;
      }
    } else {
      alldrive(-100, 100);
      direction -= 0.25;
      if (direction < 0) {
        direction += 4;
      }
    }
    currloc[0] = (int)currlocprec[0];
    currloc[1] = (int)currlocprec[1];
    Serial.println("Moving to (" + String(currlocprec[0]) + ", " + String(currlocprec[1]) + ")");
    Serial.println("Direction: " + String(direction) + " (" + String(godir) + ")");
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