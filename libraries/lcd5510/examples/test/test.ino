#include <lcd5510.h>

void setup(){
  Lcd::Initialize();
  Lcd::String(0,1,F("Hello World"));

  for(float i=0;i<1.0;i+=0.01)
  {
    delay(100);
    Lcd::Progress(2,i);
  }
}

void loop()
{
}
