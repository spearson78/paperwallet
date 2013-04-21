#include <panic.h>

void PANIC(paniccode p){
  Serial.println(F("PANIC "));
  Serial.println(p);
  for(;;){}
}

void setup(){
  Serial.begin(9600);
  PANIC(PANIC_UNKNOWN_ERROR);
}

void loop(){
}
