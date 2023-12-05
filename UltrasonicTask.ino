#include "UltrasonicTask.h"
// #include <NewPing.h>

void tickUltra(UltraState *state); // Arduino bug workaround
void tickUltra(UltraState *state) {
  // switch (*state) {
  // case ULTRA_IDLE:
  //   *state = ULTRA_PINGLOW1;
  //   break;
  // case ULTRA_PINGLOW1: // Delay would be helpful here to ping, arduino only managing to clock in at .05
  //   digitalWrite(trigPin, LOW);
  //   *state = ULTRA_PINGHIGH1;
  //   break;
  // case ULTRA_PINGHIGH1:
  //   digitalWrite(trigPin, HIGH);
  //   *state = ULTRA_PINGLOW2;
  //   break;
  // case ULTRA_PINGLOW2:
  //   digitalWrite(trigPin, LOW);
  //   *state = ULTRA_PONG;
  //   break;
  // case ULTRA_PONG:
  //   *state = ULTRA_IDLE;
  //   break;
  // default:
  //   *state = ULTRA_IDLE;
  //   break;
  // }
  // switch (*state) {
  // case ULTRA_IDLE:
  //   break;
  // case ULTRA_PINGLOW1:
  //   break;
  // case ULTRA_PINGHIGH1:
  //   break;
  // case ULTRA_PINGLOW2:
  //   break;
  // case ULTRA_PONG:
  //   // Serial.println(micros());
  //   duration = pulseIn(echoPin, HIGH); // This thing delays the state machine a lot I think, but idk how to do it a different way
  //   // Serial.println(micros());
  //   distance = duration * 0.022; // Should be 0.01echoPin, but I think state machine is not fast enough to ping correctly, so corrected to 0.022
  //   Serial.println(distance);
  //   break;
  // default:
  //   break;
  // }
  // Found a library that does ultrasonic a lot faster and thus more accurately without
  // delaying the entire state machine

  switch (*state) {
  case ULTRA_INIT:
    *state = ULTRA_ON;
    break;
  case ULTRA_ON:
    break;
  default:
    *state = ULTRA_INIT;
    break;
  }
  switch (*state) {
  case ULTRA_INIT:
    break;
  case ULTRA_ON:
    distance = sonar.ping_cm();
    break;
  default:
    break;
  }
}