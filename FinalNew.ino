#include "Tasks.h"
#include "Timer.h"

int prevtime = 0;
int currtime = 0;
void setup() {
  Serial.begin(9600);
  setupTasks();

  prevtime = micros();

  TimerSet(10);
  TimerOn();
}

int freeRAM() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void loop() {
  currtime = micros();
  executeTasks(currtime);
  prevtime = currtime;
  // Serial.print ("Free memory is: ");
  // Serial.println (freeRAM ());
  while (!TimerFlag) {
  }
  TimerFlag = 0;
}
