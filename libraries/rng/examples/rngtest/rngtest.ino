#include <sha256.h>
#include <rng.h>
#include <panic.h>
#include <progress.h>

void PROGRESS(float p){
}

void PANIC(paniccode p){
  for(;;){
    delay(500);
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
  }
}

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  Serial.begin(9600);
  uint8_t PRIVATE[32];

  for(;;){
    
    rng::generate(PRIVATE,32);
    Serial.write(PRIVATE,32);
  }
}

void loop(){

}
