#include "DrivetrainTask.h"
#include "IRTask.h"
#include "Tasks.h"
#include "UltrasonicTask.h"

void addTask(task &mytask) {
  tasks[tasksize] = mytask;
  ++tasksize;
}

void executeTasks(int currtime) {
  for (unsigned int i = 0; i < tasksize; ++i) {
    if (tasks[i].elapsed >= tasks[i].period) {
      tasks[i].func(tasks[i].state);
      tasks[i].elapsed %= tasks[i].period;
    }
    tasks[i].elapsed += (currtime - prevtime) / 1000;
  }
}

// Define your tasks here
// For example:
// task myTask = {10, 10, &myState, myFunction};
// addTask(myTask);

void addTasks() {
  addTask(irTask);
  addTask(pingTask);
  addTask(driveTask);
}

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

void setupTasks() {
  addTasks();
  // find gcd
  periodGCD = tasks[0].period;
  for (unsigned int i = 1; i < tasksize; ++i) {
    periodGCD = gcd(periodGCD, tasks[i].period);
  }
}
