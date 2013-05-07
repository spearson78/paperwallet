#ifndef M190PRINTER_H
#define M190PRINTER_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>

namespace m190{
  const int PIN_MOTOR = 9; //PWM required
  const int PIN_RESET = 10;
  const int PIN_TIMING = A5;

  typedef boolean (*pixelsource)(void *ctx,int x,int y);

  void initialize();
  void formfeed(int rows);
  void print(pixelsource s,void *ctx,int rows,boolean overlap);
  void print(char *x);
  void print(const __FlashStringHelper *msg);
  void printP(const byte *bitmap,int w,int h);
}

#endif
