#ifndef IRTASK_H
#define IRTASK_H

#include "GLOBALS.h"
#include "Tasks.h"

#include <IRremote.h>

int codes[] = {0xFFFFFFFF,
               0xFFA25D, 0xFF629D, 0xFFE21D,
               0xFF22DD, 0xFF02FD, 0xFFC23D,
               0xFFE01F, 0xFFA857, 0xFF906F,
               0xFF6897, 0xFF9867, 0xFFB04F,
               0xFF30CF, 0xFF18E7, 0xFF7A85,
               0xFF10EF, 0xFF38C7, 0xFF5AA5,
               0xFF42BD, 0xFF4AB5, 0xFF52AD};
int RECV_PIN = 9;
IRrecv irrecv = IRrecv(RECV_PIN);
decode_results results;

int i;
int code;
int cmd;
int loc;
int left[2] = {-100, 100};
int right[2] = {100, -100};

enum IRState {
  IR_INIT,
  IR_IDLE,
  IR_RECV
};

int getIRCode(int code);
void tickIR(IRState *state);

#endif
