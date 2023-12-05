#ifndef ULTRASONICTASK_H
#define ULTRASONICTASK_H

#include "GLOBALS.h"
#include "Tasks.h"
#include <NewPing.h>

const int trigPin = 8;
const int echoPin = 7;
NewPing sonar(trigPin, echoPin, 50);

// enum UltraState {
//   ULTRA_INIT,
//   ULTRA_IDLE,
//   ULTRA_PINGLOW1,
//   ULTRA_PINGHIGH1,
//   ULTRA_PINGLOW2,
//   ULTRA_PONG
// };

enum UltraState {
  ULTRA_INIT,
  ULTRA_ON
};

void tickUltra(UltraState *state);

#endif
