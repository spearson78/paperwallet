#include <qrencode.h>

void setup(){
  
  Serial.begin(9600);
  
  Serial.println(F("Generating QR Code"));
  qrcontext qr;

  qr.qrencode("5Kcw44bQjwJFG7TZp89RvrGkH36rE32mZDHfSrz9uziK7MqsSYN");

  Serial.println(F("Generated QR Code"));
  Serial.println(WD);

   for(int y = 0 ;y<WD;y++){
     for(int x = 0 ;x<WD;x++){
       if( qr.getQRBit(x,y) ){
         Serial.print(F("██"));
       } else {
         Serial.print(F("  "));
       }       
     }
     Serial.println();     
   }
}

void loop(){
}


