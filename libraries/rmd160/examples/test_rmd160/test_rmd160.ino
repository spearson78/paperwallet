#include <rmd160.h>
#include <panic.h>

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

  struct digest d;
  uint8_t rdata[] = {"The quick brown fox jumps over the lazy dog"};
  uint8_t digest[20];
  
  Reset(&d);
  Write(&d,rdata,sizeof(rdata)-1);
  Sum(&d,digest);

  uint8_t expecteddigest[] = {0x37,0xF3,0x32,0xF6,0x8D,0xB7,0x7B,0xD9,0xD7,0xED,0xD4,0x96,0x95,0x71,0xAD,0x67,0x1C,0xF9,0xDD,0x3B};

  if( memcmp(digest,expecteddigest,20) != 0 ){
    FAIL(F("Digest Mismatch"));
  }

  Serial.println("END");
}

void loop(){
}
