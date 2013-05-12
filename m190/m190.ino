#include <panic.h>
#include <progress.h>
#include <bignat.h>
#include <bigint.h>
#include <sha256.h>
#include <rmd160.h>
#include <base58.h>
#include <bitelliptic.h>
#include <bitaddress.h>
#include <rng.h>
#include <qrencode.h>
#include <m190printer.h>

const int LEDPIN=8;
const int BUTTONPIN=11;

void PANIC(byte errorCode){
  for(;;){
    for(byte i=0;i<errorCode;i++){
      digitalWrite(LEDPIN,HIGH);
      delay(250);
      digitalWrite(LEDPIN,LOW);
      delay(250);
    }
    delay(1000);
  }
}

void PROGRESS(float progress){
  static byte flipflop=0;
  if(flipflop==0){
    digitalWrite(LEDPIN,HIGH);
    flipflop=1;
  }else {
    digitalWrite(LEDPIN,LOW);
    flipflop=0;
  }
}

uint8_t PRIVATE[32];
WORD xbuf[32];
WORD ybuf[32];
struct bigint pubx(xbuf,sizeof(xbuf));
struct bigint puby(ybuf,sizeof(ybuf));

/*
const int ringsize=128;
int ring[ringsize];
int ringpos=0;
void recordTick(int val,unsigned long micros){
  ring[ringpos]=val;
  ringpos++;
  ringpos%=ringsize;
}
*/

void dumpStats(){
/*
  Serial.println("Ring Buf");
  int last=0;
  for(int i=0;i<ringsize;i++){
    int p=i+ringpos;
    p%=ringsize;
    int val = ring[p];
    Serial.print(val);
    if( val >= last ){
      Serial.println(" >");
    } else {
      Serial.println(" <");
    }
    last=val;
  }
  */
}

const float qrxscale=2.25;
const int qryscale=2;

//const float qrxscale=1.125;
//const int qryscale=1;

//const int qryscale=3;
//const float qrxscale=3.375;

boolean qrcodesource(void *ctx,int x,int y){
//  return( x==10 || y==10);
  qrcontext *qr=(qrcontext *)ctx;

  float fx = (float)x/qrxscale;
  x=fx;
  y/=qryscale;
  if(x<0||x>WD||y<0||y>WD){
    return 0;
  } else {
    return qr->getQRBit(x,y);
  }
}

byte qroffset=20;

boolean qrcodesource2(void *ctx,int x,int y){
//  return( x==10 || y==10);
  qrcontext *qr=(qrcontext *)ctx;

  float fx = (float)x/qrxscale;
  x=fx;
  x-=qroffset;
  y/=qryscale;
  if(x<0||x>WD||y<0||y>WD){
    return 0;
  } else {
    return qr->getQRBit(x,y);
  }
}


boolean horizlinesource(void *ctx,int x,int y){
  return 1;  
}

void horizline(){
  m190::print(horizlinesource,NULL,5,true);
  m190::formfeed(2);
}

void printqr(char *encoded){
  qrcontext qr;
  qr.qrencode(encoded);
  m190::print(qrcodesource2,&qr,WD*qryscale,true);
}

void printprivate(uint8_t *PRIVATE){
  char encoded[52];
  bitaddress::generatePrivateWIF(PRIVATE,encoded,sizeof(encoded));
  printqr(encoded);
  m190::formfeed(5);
  m190::print(encoded);
  /*  
  m190::print(encoded);
  qrcontext qr;
  qr.qrencode(encoded);
  m190::print(qrcodesource,NULL,WD*qryscale,true);
  m190::formfeed(2);
  */
}

void printpublic(const struct bigint &x,const struct bigint &y){
  char encoded[40];
  bitaddress::generateAddress(x,y,encoded,sizeof(encoded)); 
  //qrcontext qr;
  //qr.qrencode(encoded);
  
  m190::print(encoded);
  m190::formfeed(5);  
  printqr(encoded);
  //qrcode(qr);
}

void generatePrivateKey(uint8_t *PRIVATE){
  rng::generate(PRIVATE,32);
}

void setup(){
  m190::initialize();  

  pinMode(BUTTONPIN,INPUT);
  pinMode(LEDPIN,OUTPUT);
  

  //dumpStats();
}


void loop(){  
  digitalWrite(LEDPIN,HIGH);  
  while(digitalRead(BUTTONPIN)==LOW){
  }
  digitalWrite(LEDPIN,LOW);  
  
  //memset(ring,0,sizeof(int)*ringsize);
  m190::formfeed(40);

  generatePrivateKey(PRIVATE);
  
  digitalWrite(LEDPIN,HIGH);  
  
  qroffset=20;
  printprivate(PRIVATE);
  m190::formfeed(40);
  
  bitaddress::generatePublicKey(PRIVATE,pubx,puby);
  
  digitalWrite(LEDPIN,HIGH);  
  
  qroffset=5;
  printpublic(pubx,puby);
  m190::formfeed(20);

  digitalWrite(LEDPIN,LOW);  
}
