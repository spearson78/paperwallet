#include <sha256.h>
#include <rng.h>
#include <panic.h>
#include <progress.h>

void PROGRESS(float p){
}

void PANIC(paniccode p){
  Serial.print(F("#PANIC "));
  Serial.println(p);
  for(;;){}
}


void setup() {
  Serial.begin(9600);
  byte PRIVATE[32];

  Serial.print(F("#==================================================================\n"));
  Serial.print(F("# generator arduino rng\n"));
  Serial.print(F("#==================================================================\n"));
  Serial.print(F("type: d\n"));
  Serial.print(F("count: 1000\n"));
  Serial.print(F("numbit: 32\n"));

  for(;;){
    rng::generate(PRIVATE,32);

    for( int i = 0 ; i< 32/4 ; i++){
      uint32_t *r = (uint32_t*)(PRIVATE+(i*4));
      Serial.print(*r);  
      Serial.print(F("\n"));  
    }
  }
}

void loop(){

}
