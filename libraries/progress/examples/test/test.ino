#include <progress.h>

void PROGRESS(float p){
  Serial.println(p);
}

void setup(){
  PROGRESS(0.5);
}

void loop(){
}
