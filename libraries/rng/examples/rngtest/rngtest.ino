#include <sha256.h>
#include <rng.h>
#include <panic.h>
#include <progress.h>
#include <SoftwareSerial.h>

//#define DEBUG

SoftwareSerial mySerial(10, 11); // RX, TX

const int LEDPIN=8;

void DBGPRINT(char *str){
#ifdef DEBUG
  Serial.println(str);
#endif
}

void PROGRESS(float p){
static byte flipflop=0;
  flipflop++;
  digitalWrite(LEDPIN,flipflop%2);
}

void PANIC(paniccode errorCode){
#ifdef DEBUG
  Serial.println(F("PANIC"));
  Serial.println(errorCode);
#endif
  
  for(;;){
    for(int i=0;i<(errorCode);i++){
      digitalWrite(LEDPIN,HIGH);
      delay(250);
      digitalWrite(LEDPIN,LOW);
      delay(250);
    }
    delay(1000);
  }
}

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

  pinMode(LEDPIN,OUTPUT);
  digitalWrite(LEDPIN,LOW);
}

void loop(){
  uint8_t PRIVATE[32];

  digitalWrite(LEDPIN,HIGH);
  delay(500);
  digitalWrite(LEDPIN,LOW);
  delay(500);
    
#ifdef DEBUG
    Serial.println(F("Generate"));
#endif
    rng::generate(PRIVATE);
#ifndef DEBUG
    Serial.write(PRIVATE,32);
    mySerial.write(PRIVATE,32);
#endif
}
