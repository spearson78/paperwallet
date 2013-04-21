#include <panic.h>
#include <bignat.h>
#include <bigint.h>

const char DECIMAL[] PROGMEM = {"0123456789"};

void PANIC(unsigned char errorCode){
  Serial.println(F("PANIC "));
  Serial.println(errorCode);
  for(;;){}
}

void FAIL(const __FlashStringHelper * msg){
  Serial.println(F("FAIL "));
  Serial.println(msg);
}

void printInt(const struct bigint &a){
  char display[40];
  a.String(10,DECIMAL,display,sizeof(display));
  Serial.print(display);
}

void printlnInt(const struct bigint &a){
  printInt(a);
  Serial.println();
}

void TestCmp(){
  WORD abuf[4];
  struct bigint a(abuf,sizeof(abuf));
  WORD bbuf[4];
  struct bigint b(bbuf,sizeof(bbuf));

  uint8_t aval[] = {16, 56, 94, 68};
  a.SetBytes(0,aval,4);

  uint8_t bval[] = {37, 146, 1, 89};
  b.SetBytes(0,bval,4);

  if( a.Cmp(b) != -1 ){
    FAIL(F("a.Cmp(b) != -1"));
  }
  if( b.Cmp(a) != 1 ){
    FAIL(F("b.Cmp(a) != 1"));
  }

  b.SetBytes(1,bval,4);
  if( a.Cmp(b) != 1 ){
    FAIL(F("a.Cmp(-b) != 1"));
  }
  if( b.Cmp(a) != -1 ){
    FAIL(F("-b.Cmp(a) != -1"));
  }

}

void TestMul(){
  WORD abuf[4];
  struct bigint a(abuf,sizeof(abuf));
  WORD bbuf[4];
  struct bigint b(bbuf,sizeof(bbuf));
  WORD cbuf[4];
  struct bigint c(cbuf,sizeof(cbuf));

  WORD rbuf[8];
  struct bigint r(rbuf,sizeof(rbuf));
  WORD r2buf[8];
  struct bigint r2(r2buf,sizeof(r2buf));

  uint8_t aval[] = {16, 56, 94, 68};
  a.SetBytes(0,aval,4);

  uint8_t bval[] = {37, 146, 1, 89};
  b.SetBytes(0,bval,4);
  c.SetBytes(1,bval,4);

  r.Mul(a,b);
  r2.Mul(a,c);

  if(r.Abs().Cmp(r2.Abs()) != 0){
    FAIL(F("abs(a*b) != abs(a*-b)"));
  }

  if( r2.Sign() != -1 ){
    FAIL(F("a*-b is positive"));
  }
  
  if( r2.Sign() == r.Sign() ){
    FAIL(F("a*b has same sign as a*-b"));
  }
}

void TestDiv(){
  WORD abuf[4];
  struct bigint a(abuf,sizeof(abuf));
  WORD bbuf[4];
  struct bigint b(bbuf,sizeof(bbuf));
  WORD cbuf[4];
  struct bigint c(cbuf,sizeof(cbuf));

  WORD qbuf[8];
  struct bigint q(qbuf,sizeof(qbuf));
  WORD q2buf[8];
  struct bigint q2(q2buf,sizeof(q2buf));

  WORD rbuf[8];
  struct bigint r(rbuf,sizeof(rbuf));
  WORD r2buf[8];
  struct bigint r2(r2buf,sizeof(r2buf));

  WORD vbuf[33];

  uint8_t aval[] = {37, 146, 1, 89};
  a.SetBytes(0,aval,4);

  uint8_t bval[] = {16, 56, 94, 68};
  b.SetBytes(0,bval,4);
  c.SetBytes(1,bval,4);

  q.QuoRem(a,b,r,vbuf);
  q2.QuoRem(a,c,r2,vbuf);

  if(r.Cmp(r2) != 0){
    FAIL(F("remainder a/b != remainder a/-b"));
  }

  if(q.Abs().Cmp(q2.Abs()) != 0){
    FAIL(F("abs(a/b) != abs(a/-b)"));
  }

  if( q2.Sign() != -1 ){
    FAIL(F("a/-b is positive"));
  }
  
  if( q2.Sign() == q.Sign() ){
    FAIL(F("a/b has same sign as a/-b"));
  }
}

bool testGcd(const struct bigint &d,const struct bigint &x,const struct bigint &a,const struct bigint &b){
  WORD Xbuf[4];
  struct bigint X(Xbuf,sizeof(Xbuf));

  WORD Dbuf[4];
  struct bigint D(Dbuf,sizeof(Dbuf));
  D.GCD(X,a,b);

  if( D.Cmp(d) != 0 ){
    FAIL(F("D.Cmp(d) != 0"));
  }
  if( X.Cmp(x) != 0 ){
    FAIL(F("X.Cmp(x) != 0"));
  }
  
}

void TestGCD(){

  WORD dbuf[4];
  struct bigint d(dbuf,sizeof(dbuf));
  uint8_t dval[] = {3,167};
  d.SetBytes(0,dval,sizeof(dval));

  WORD xbuf[4];
  struct bigint x(xbuf,sizeof(xbuf));
  uint8_t xval[] = {3};
  x.SetBytes(1,xval,sizeof(xval));

  WORD abuf[4];
  struct bigint a(abuf,sizeof(abuf));
  uint8_t aval[] = {252,3};
  a.SetBytes(0,aval,sizeof(aval));
  
  WORD bbuf[4];
  struct bigint b(bbuf,sizeof(bbuf));
  uint8_t bval[] = {94,246};
  b.SetBytes(0,bval,sizeof(bval));

  testGcd(d,x,a,b);
}

void TestModInverse(){

  WORD onebuf[1];
  struct bigint one(onebuf,sizeof(onebuf));
  one.Set(1);

  WORD ebuf[4];
  struct bigint e(ebuf,sizeof(ebuf));
  e.Set(1);

  WORD pbuf[4];
  struct bigint p(pbuf,sizeof(pbuf));
  p.Set(13);

  WORD ibuf[4];
  struct bigint i(ibuf,sizeof(ibuf));

  WORD i2buf[4];
  struct bigint i2(i2buf,sizeof(i2buf));

  i.ModInverse(e,p);
  i2.Mul(i,e);
  i.Mod(i2,p);
  if( i.Cmp(one) != 0){
    FAIL(F("ModInverse Failed"));
  }

}


void setup(){
  Serial.begin(9600); 
  Serial.println("BEGIN");  

  TestCmp();
  TestMul();
  TestDiv();
  TestGCD();
  TestModInverse();

  Serial.println("END");  
}

void loop(){
}
