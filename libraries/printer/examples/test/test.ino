#include <qrencode.h>
#include <printer.h>

void setup(){

  printer::initialize();
  {
    qrcontext qr;

    qr.qrencode("5JGjRHavsH4kR4LcuraThjcA96AGPDX2hTSrWVS5m1YAhfyfTSm");
    printer::printPosition(F("430"),F("200"));
    printer::printQR(qr);
    printer::print(F("\x1B(s3T"));  
    printer::print(F("\x1B(s16H"));  
    printer::print(F("\x1B(s12V"));  
    printer::printLine("\r\n\x1b*p348X5JGjRHavsH4kR4LcuraThjc");
    printer::printLine("\x1b*p348XA96AGPDX2hTSrWVS5m1YAhfyfTSm");
  }

  {
    qrcontext qr;

    qr.qrencode("1NS2cfyDnmpBJN2uw9unD61XZcpZ1cjxFH");
    printer::printLine("\x1b*p1183Y\x1b*p210X1NS2cfyDnmpBJN2uw9unD61XZcpZ1cjxFH");
    printer::printPosition(F("310"),F("1206"));
    printer::printQR(qr);
    printer::print(F("\x1B(s3T"));  
    printer::print(F("\x1B(s16H"));  
    printer::print(F("\x1B(s12V"));  
  }

  printer::formfeed();
}

void loop(){
}
