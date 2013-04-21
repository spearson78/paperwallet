#ifndef  PRINTER_H
#define  PRINTER_H
// This code is derived from http://arduino.cc/forum/index.php?topic=74776.0
// The original code was released into the public domain by its author sentryGun53

// Modifications are Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
#include <Arduino.h>
#include <qrencode.h>

namespace printer{
  void initialize();
  void printByte(byte inByte);
  void print(const char *characters);
  void print(const __FlashStringHelper *msg);
  void printLine(const char *characters);
  void formfeed();
  void printQR(const qrcontext &qr);
  void printPosition(const __FlashStringHelper *x,const __FlashStringHelper *y);
}

#endif
