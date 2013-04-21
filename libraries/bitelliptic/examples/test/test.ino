#include <panic.h>
#include <bignat.h>
#include <bigint.h>
#include <bitelliptic.h>

void PROGRESS(float p){
  Serial.println(p);
}

void PANIC(paniccode p){
  Serial.println(F("PANIC"));
  Serial.println(p);
  for(;;){}
}

void FAIL(const __FlashStringHelper * msg){
  Serial.println(F("FAIL "));
  Serial.println(msg);
}

void setup(){
}

void loop(){
}
