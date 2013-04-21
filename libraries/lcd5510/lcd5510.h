#ifndef TEXT5510_H
#define TEXT5510_H
//This code is derived from http://playground.arduino.cc/Code/PCD8544

// Modifications are Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
#include <Arduino.h>

namespace Lcd{

  void Initialize();
  void Clear();
  void String(int x,int y,const char *characters);
  void String(int x,int y,const __FlashStringHelper *msg);
  void Progress(int y,float percent);
  void Bitmap(uint8_t *bitmap);
}

#endif
