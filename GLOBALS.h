#ifndef GLOBALS_H
#define GLOBALS_H
// Stores all global variables shared between files

// Target location for the robot
extern int destloc[2];

// Ultrasonic measured distance
extern int distance = 1000;

extern int forceMove;
extern int forceSpeeds[2];
extern int isRoaming;
extern int roamingSpeeds[2];

// Commands
struct command {
  String description;
  void (*func)(int *args);
  int *args;
};
extern command commands[22]{};

void print(int *args) {
  char *cargs = (char *)args;
  Serial.println(cargs);
}

void ultraprint(int *args) {
  Serial.println("Distance: " + String(distance));
}

void setDestination(int *args) {
  forceMove = 0;
  isRoaming = 0;
  destloc[0] = args[0];
  destloc[1] = args[1];
  Serial.println("Setting destination to (" + String(destloc[0]) + ", " + String(destloc[1]) + ")");
}

void callLDrive(int speed) {
  forceMove = 1;
  isRoaming = 0;
  forceSpeeds[0] = speed;
}

void callRDrive(int speed) {
  forceMove = 1;
  isRoaming = 0;
  forceSpeeds[1] = speed;
}

void calldrive(int speed) {
  forceMove = 1;
  isRoaming = 0;
  forceSpeeds[0] = speed;
  forceSpeeds[1] = speed;
}

void callalldrive(int *speeds) {
  forceMove = 1;
  isRoaming = 0;
  Serial.println("aLeft: " + String(speeds[0]) + " Right: " + String(speeds[1]));
  forceSpeeds[0] = speeds[0];
  forceSpeeds[1] = speeds[1];
  Serial.println("bLeft: " + String(forceSpeeds[0]) + " Right: " + String(forceSpeeds[1]));
}

void callstop(int *args) {
  forceMove = 1;
  isRoaming = 0;
  forceSpeeds[0] = 0;
  forceSpeeds[1] = 0;
}

void callroam(int *args) {
  forceMove = 0;
  isRoaming = 1;
}

#endif