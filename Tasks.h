#ifndef TASKS_H
#define TASKS_H
#include "DrivetrainTask.h"
#include "IRTask.h"
#include "Tasks.h"
#include "UltrasonicTask.h"
int periodGCD;

struct task {
  byte period;
  byte elapsed;
  int state;
  void (*func)(int state);
};

task tasks[5];
int tasksize;

void addTask(task &mytask);
void executeTasks(int currtime);
void addTasks();


IRState irState = IR_INIT;
task irTask = {100, 100, &irState, tickIR};
UltraState ultraState = ULTRA_INIT;
task pingTask = {20, 20, &ultraState, tickUltra};
DriveState driveState = DRIVE_INIT;
task driveTask = {410, 410, &driveState, tickDrive};

#endif
