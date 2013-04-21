// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <panic.h>
#include <progress.h>
#include <bignat.h>
#include <bigint.h>
#include <sha256.h>
#include <rmd160.h>
#include <base58.h>
#include <bitelliptic.h>
#include <bitaddress.h>
#include <rng.h>
#include <qrencode.h>
#include <lcd5510.h>
#include <printer.h>

//Read high fuse bits
//avrdude -v -patmega328p -cusbtiny -U hfuse:r:hfuse.txt:b

//Disable Bootloader on reset
//avrdude -v -patmega328p -cusbtiny -U hfuse:w:0xDF:m

//Enable bootloader on reset
//avrdude -v -patmega328p -cusbtiny -U hfuse:w:0xDE:m

//burn without bootloader
//avrdude -v -patmega328p -cusbtiny -U hfuse:w:0xDF:m -Uflash:w:/tmp/build2279538609720273931.tmp/paperwallet.cpp.hex:i

void PANIC(byte errorCode){
  Lcd::Clear();
  Lcd::String(0,0,F("E"));
  char buf[2];
  buf[0]=errorCode+65;
  buf[1]=NULL;
  Lcd::String(0,1,buf);
  for(;;){
  }
}

void PROGRESS(float progress){
  Lcd::Progress(5,progress);
}

void displayPrivate(uint8_t *PRIVATE){

  char encoded[128];

  bitaddress::generatePrivateWIF(PRIVATE,encoded,sizeof(encoded));

  Lcd::Clear();
  Lcd::String(0,0,F("Private Key"));
  Lcd::String(0,1,encoded);  
}

void displayPrivateQR(uint8_t *PRIVATE){
  char encoded[128];
  bitaddress::generatePrivateWIF(PRIVATE,encoded,sizeof(encoded));

  Lcd::Clear();
  displayQR(encoded);
}

void printPrivateQR(uint8_t *PRIVATE){
  char encoded[128];
  bitaddress::generatePrivateWIF(PRIVATE,encoded,sizeof(encoded));

  printer::printPosition(F("477"),F("92"));
  printQR(encoded);
  char split[27];
  memcpy(split,encoded,26);
  split[26]=0;
  printer::print(F("\x1B(s3T\x1B(s16H\x1B(s12V\r\n\x1b*p395X"));
  printer::printLine(split);
  printer::print(F("\x1b*p395X"));
  printer::printLine(encoded+26);
}

void displayPublic(const struct bigint &x,const struct bigint &y){
  char encoded[40];
  bitaddress::generateAddress(x,y,encoded,sizeof(encoded)); 

  Lcd::Clear();
  Lcd::String(0,0,F("Address"));
  Lcd::String(0,1,encoded);  
}

void displayPublicQR(const struct bigint &x,const struct bigint &y){
  char encoded[40];
  bitaddress::generateAddress(x,y,encoded,sizeof(encoded)); 
  Lcd::Clear();
  displayQR(encoded);
}

void printPublicQR(const struct bigint &x,const struct bigint &y){
  char encoded[40];
  bitaddress::generateAddress(x,y,encoded,sizeof(encoded)); 
  printer::print(F("\x1b*p1067Y\x1b*p257X"));   
  printer::printLine(encoded);
  printer::printPosition(F("357"),F("1092"));
  printQR(encoded);
}

void displayResults(uint8_t *PRIVATE,const struct bigint &x,const struct bigint &y){
  displayPrivate(PRIVATE);
  displayPublic(x,y);
}

void generatePrivateKey(uint8_t *PRIVATE){
  rng::generate(PRIVATE,32);
}

void displayQR(const char *string){
  qrcontext qr;

  qr.qrencode(string);

  Lcd::Bitmap(qr.qrframe);
}

void printQR(const char *string){
  qrcontext qr;

  qr.qrencode(string);

  printer::printQR(qr);
}

uint8_t PRIVATE[32];
WORD xbuf[32];
WORD ybuf[32];
struct bigint pubx(xbuf,sizeof(xbuf));
struct bigint puby(ybuf,sizeof(ybuf));
int state = 0;

void setup(){
  Lcd::Initialize();
  Lcd::Clear();
  //Lcd::String(17,1,F("Offline"));
  Lcd::String(21,2,F("Wallet"));
  //Lcd::String(11,3,F("Generator"));

  pinMode(A1,INPUT);
  pinMode(13,INPUT);
  printer::initialize();

  generatePrivateKey(PRIVATE);
  bitaddress::generatePublicKey(PRIVATE,pubx,puby);
}

void loop(){
  switch( state ){
  case 0:
    displayPrivate(PRIVATE);
    break;
  case 1:
    displayPublic(pubx,puby); 
    break;
  }
  delay(1000);
  int a1 = LOW;
  int a0 = LOW;
  while(a1==LOW && a0==LOW){
    a0=digitalRead(13);
    a1=digitalRead(A1);
  }
  if( a0 == HIGH ){
    state++;
    if( state == 2 ){
      state =0;
    }
  } 
  else {
    Lcd::Clear();
    Lcd::String(0,1,F("Printing"));

    printPrivateQR(PRIVATE);
    printPublicQR(pubx,puby);
    printer::formfeed();
  }
}



