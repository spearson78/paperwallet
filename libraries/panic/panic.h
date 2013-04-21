#ifndef PANIC_H
#define PANIC_H

typedef unsigned char paniccode;

const paniccode PANIC_UNKNOWN_ERROR=0;

void PANIC(paniccode p);

#endif

