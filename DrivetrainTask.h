#ifndef DRIVETRAINTASK_H
#define DRIVETRAINTASK_H

#include "GLOBALS.h"
#include "Tasks.h"

// Locations (0-9 on remote are saved locations)
extern int locations[10][2] = {{0, 0},
                               {2, 3},
                               {9, 4},
                               {5, 2},
                               {1, 8},
                               {6, 3},
                               {2, 9},
                               {8, 1},
                               {4, 6},
                               {7, 5}};
int currloc[2] = {0, 0};
double currlocprec[2] = {0, 0};
int destloc[2] = {0, 0};
int targetloc[2] = {0, 0};
double direction = 0;

// map of environment
// 0 = empty, >0 = path calculation, -1 = obstacle
const int fieldsize = 10;
byte fieldMap[fieldsize][fieldsize] = {0};

// Motor Stuff
const int L1 = 12;
const int L2 = 13;
const int R1 = 11;
const int R2 = 10;

extern int isRoaming = 0;
extern int roamingSpeeds[2] = {100, 100};
extern int forceMove = 0;
extern int forceSpeeds[2] = {0, 0};

int randVal;

enum DriveState {
  DRIVE_INIT,
  DRIVE_IDLE,
  DRIVE_SEARCH,
  DRIVE_GOTO,
  DRIVE_FORCE,
  DRIVE_ROAM
};

void tickDrive(DriveState *state);

#endif