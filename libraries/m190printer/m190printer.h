#ifndef M190PRINTER_H
#define M190PRINTER_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>

namespace m190{
  const int PIN_MOTOR = 4;
  const int PIN_RESET = 2;
  const int PIN_TIMING = A0;

  const int PIN_SOLA = 5;
  const int PIN_SOLB = 6;
  const int PIN_SOLC = 7;
  const int PIN_SOLD = 8;
  const int PIN_SOLE = 9;
  const int PIN_SOLF = 10;
  const int PIN_SOLG = 11;
  const int PIN_SOLH = 12;

  typedef boolean (*pixelsource)(void *ctx,int x,int y);

  void initialize();
  void formfeed(int rows);
  void print(pixelsource s,void *ctx,int rows,boolean overlap);
  void print(char *x);
  void print(const __FlashStringHelper *msg);
  void printP(const byte *bitmap,int w,int h);
}

#endif
