#include <panic.h>
#include <bignat.h>
#include <base58.h>

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
  Serial.begin(9600);
  Serial.println("BEGIN");  

  char encoded[40];
  byte dataA[] = {0,235,21,35,29,252,235,96,146,88,134,182,125,6,82,153,146,89,21,174,177,114,192,102,71};

  base58::encode(dataA,sizeof(dataA),encoded,sizeof(encoded));

  char expected[] ="1NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L";

  if( strcmp(encoded,expected) != 0 ){
    Serial.println(encoded);
    Serial.println(expected);
    FAIL(F("TestBase58String Failed"));
  }

  Serial.println("END");
}

void loop(){
}
