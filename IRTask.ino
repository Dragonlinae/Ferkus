#include "IRTask.h"

int getIRCode(int value) {
  // Serial.println(value, HEX);
  for (i = 0; i < sizeof(codes) / sizeof(int); ++i) {
    if (value == codes[i]) {
      return i;
    }
  }
  return -1;
}

void tickIR(IRState *state); // Arduino bug workaround
void tickIR(IRState *state) {
  code = -1;
  switch (*state) {
  case IR_INIT:
    addIRCommands();
    irrecv.enableIRIn();
    *state = IR_IDLE;
  case IR_IDLE:
    if (irrecv.decode(&results)) {
      // Serial.println(results.value, HEX);
      code = getIRCode(results.value);
      if (code >= 0) {
        *state = IR_RECV;
      }
      irrecv.resume();
    } else {
      *state = IR_IDLE;
    }
    break;
  case IR_RECV:
    if (irrecv.decode(&results)) {
      code = getIRCode(results.value);
      if (code >= 0) {
        *state = IR_RECV;
      }
      irrecv.resume();
    } else {
      *state = IR_IDLE;
    }
    break;
  default:
    *state = IR_INIT;
    break;
  }

  switch (*state) {
  case IR_INIT:
    break;
  case IR_IDLE:
    break;
  case IR_RECV:
    if (code > 0 && code < sizeof(commands) / sizeof(command) && commands[code].description != "") {
      // Serial.println(code);
      Serial.println(commands[code].description);
      commands[code].func(commands[code].args);
      Serial.println(commands[code].args[0]);
    } else if (code == 0) {
      // Serial.println(code);
      Serial.println("Holding...");
    } else {
      // Serial.println(code);
      Serial.println(results.value, HEX);
      Serial.println("No command found");
    }
  }
}

void addIRCommand(command cmd, int index);
void addIRCommand(command cmd, int index) {
  commands[index] = cmd;
}

void addIRCommand(String description, void (*func)(int *args), int *args, int index);
void addIRCommand(String description, void (*func)(int *args), int *args, int index) {
  command cmd = {description, func, args};
  addIRCommand(cmd, index);
}

void addIRCommands() {
  addIRCommand("Power", &print, (int *)"Powering off", 1);
  addIRCommand("Ultrasonic", &ultraprint, NULL, 3);

  for (loc = 0; loc < 10; ++loc) {
    cmd = loc + 12;
    if (cmd == 12) {
      cmd = 10;
    }
    addIRCommand("Going to Location " + String(loc) + " at " + String(locations[loc][0]) + ", " + String(locations[loc][1]), setDestination, locations[loc], cmd);
  }

  addIRCommand("Forward", calldrive, (int *)100, 2);
  addIRCommand("Backward", calldrive, (int *)-100, 8);
  addIRCommand("Left", callalldrive, (int *)left, 4);
  addIRCommand("Right", callalldrive, (int *)right, 6);
  addIRCommand("Stop", callstop, NULL, 5);
}