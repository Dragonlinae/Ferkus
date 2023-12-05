#ifndef TASKS_H
#define TASKS_H

int periodGCD;

struct task {
  unsigned long period;
  unsigned long elapsed;
  int state;
  void (*func)(int state);
};

task tasks[20];
int tasksize;

void addTask(task &mytask);
void executeTasks(int currtime);
void addTasks();

#endif
