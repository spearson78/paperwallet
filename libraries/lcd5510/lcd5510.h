#ifndef TEXT5510_H
#define TEXT5510_H
//This code is derived from http://playground.arduino.cc/Code/PCD8544

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
