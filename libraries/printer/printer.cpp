#include <printer.h>
// This code is derived from http://arduino.cc/forum/index.php?topic=74776.0
// The original code was released into the public domain by its author sentryGun53

// Modifications are Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// parallel port pin# = arduino pin#
const int nStrobe = 12;
const int data_0 = 11;
const int data_1 = 10;
const int data_2 = 9;
const int data_3 = 8;
const int data_4 = 7;
const int data_5 = 6;
const int data_6 = 5;
const int data_7 = 4;
const int nAck = 3;
const int busy = 2;

const int strobeWait = 2;   // microseconds to strobe for

void printer::printByte(byte inByte) {
  while(digitalRead(busy) == HIGH) {
    // wait for busy to go low
  }

  digitalWrite(data_0, inByte & (1<<0));        // set data bit pins
  digitalWrite(data_1, inByte & (1<<1));        // set data bit pins
  digitalWrite(data_2, inByte & (1<<2));        // set data bit pins
  digitalWrite(data_3, inByte & (1<<3));        // set data bit pins
  digitalWrite(data_4, inByte & (1<<4));        // set data bit pins
  digitalWrite(data_5, inByte & (1<<5));        // set data bit pins
  digitalWrite(data_6, inByte & (1<<6));        // set data bit pins
  digitalWrite(data_7, inByte & (1<<7));        // set data bit pins

  digitalWrite(nStrobe, LOW);       // strobe nStrobe to input data bits
  delayMicroseconds(strobeWait);
  digitalWrite(nStrobe, HIGH);
}

void resetPrinter() {
  printer::printByte(27); // reset printer
  printer::printByte('E');
}

void printer::formfeed() {
  printByte(0x0C);
}

void printer::print(const __FlashStringHelper *msg)
{
  const char PROGMEM *p = (const char PROGMEM *)msg;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    printByte(c);
    delay(1);
  }
}

void printer::print(const char *characters) {
  while (*characters)
  {
      printByte(*characters++);
      delay(1);
  }
}

void printer::printLine(const char *characters) {
  printer::print(characters);  
  printByte(10); // new line
  printByte(13); // carriage return
}

void printer::initialize(){
  pinMode(nStrobe, OUTPUT);      // is active LOW
  digitalWrite(nStrobe, HIGH);   // set HIGH
  pinMode(data_0, OUTPUT);
  pinMode(data_1, OUTPUT);
  pinMode(data_2, OUTPUT);
  pinMode(data_3, OUTPUT);
  pinMode(data_4, OUTPUT);
  pinMode(data_5, OUTPUT);
  pinMode(data_6, OUTPUT);
  pinMode(data_7, OUTPUT);

  pinMode(nAck, INPUT);     // is active LOW
  pinMode(busy, INPUT);  

  //resetPrinter();  
}

void printer::printPosition(const __FlashStringHelper *x,const __FlashStringHelper *y){

  printer::print(F("\x1b*p"));
  printer::print(x);
  printer::printByte('x');
  printer::print(y);
  printer::printByte('Y');
}

void printer::printQR(const qrcontext &qr){
  printer::print(F("\x1B*t300R"));
  printer::print(F("\x1B*r328T"));
  printer::print(F("\x1B*r328S"));
  printer::print(F("\x1B*r1A"));
  printer::print(F("\x1B*b0M"));

  for( int y = 0 ; y < 41 ;y++){
    for(int yblob=0;yblob<8;yblob++){
      printer::print(F("\x1B*b41W"));
      for(int x=0; x<41;x++){
        if( qr.getQRBit(x,y) ){
           printer::printByte(0xFF);
         } else {
           printer::printByte(0x00);
         }
      }
    }
  }
  printer::print("\x1B*rB");

}

