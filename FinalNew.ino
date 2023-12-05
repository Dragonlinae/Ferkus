#include "Tasks.h"
#include "Timer.h"
#include <IRremote.h>

int prevtime = 0;
int currtime = 0;
void setup() {
  Serial.begin(9600);
  setupTasks();

  prevtime = micros();

  TimerSet(10);
  TimerOn();
}

void loop() {
  currtime = micros();
  executeTasks(currtime);
  prevtime = currtime;
  while (!TimerFlag) {
  }
  TimerFlag = 0;
}
