#include <panic.h>
#include <bignat.h>

const char BITCOIN[] PROGMEM = {"123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"};
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

void TestCmp(){
  struct bignat zero(NULL,0);
  struct bignat zero2(NULL,0);
  
  if( zero.Cmp(zero2) != 0 ){
    FAIL(F("zero.Cmp(zero2) != 0"));
  }
  if( zero2.Cmp(zero) != 0 ){
    FAIL(F("zero2.Cmp(zero) != 0"));
  }

  WORD onebuf[1];
  struct bignat one(onebuf,sizeof(onebuf));
  one.Set(1);

  if( zero.Cmp(one) != -1 ){
    FAIL(F("zero.Cmp(one) != -1"));
  }
  if( one.Cmp(zero) != 1 ){
    FAIL(F("one.Cmp(zero) != 1"));
  }

  WORD abuf[4];
  struct bignat a(abuf,sizeof(abuf));
  WORD bbuf[4];
  struct bignat b(bbuf,sizeof(bbuf));

  uint8_t aval[] = {16, 56, 94, 68};
  a.SetBytes(aval,4);

  uint8_t bval[] = {37, 146, 1, 89};
  b.SetBytes(bval,4);

  if( a.Cmp(b) != -1 ){
    FAIL(F("a.Cmp(b) != -1"));
  }
  if( b.Cmp(a) != 1 ){
    FAIL(F("b.Cmp(a) != 1"));
  }

}

void printNat(const struct bignat &a){
  char display[40];
  a.String(10,DECIMAL,display,sizeof(display));
  Serial.print(display);
}

void printlnNat(const struct bignat &a){
  printNat(a);
  Serial.println();
}


bool testMulAddConsistency(const struct bignat &a,const struct bignat &b){

  Serial.print(F("testMulAddConsistency("));
  printNat(a);
  Serial.print(F(","));
  printNat(b);
  Serial.println(F(")"));


  WORD onebuf[1];
  struct bignat one(onebuf,sizeof(onebuf));
  one.Set(1);

  WORD ibuf[4];
  struct bignat i(ibuf,sizeof(ibuf));

  WORD addbuf[8];
  struct bignat add(addbuf,sizeof(addbuf));

  WORD mulbuf[8];
  struct bignat mul(mulbuf,sizeof(mulbuf));

  while(i.Cmp(b)!=0){
    add.Add(add,a);
    i.Add(i,one);
  }
  
  mul.Mul(a,b);

  if( add.Cmp(mul) != 0){
    Serial.print(F("a="));printlnNat(a);
    Serial.print(F("b="));printlnNat(b);
    Serial.print(F("add="));printlnNat(add);
    Serial.print(F("mul="));printlnNat(mul);
    return false;
  }

  Serial.print(F("="));
  printNat(mul);
  Serial.println();

  return true;
}

void TestMulAddConsistency(){
  WORD abuf[4];
  struct bignat a(abuf,sizeof(abuf));
  WORD bbuf[4];
  struct bignat b(bbuf,sizeof(bbuf));

  a.Set(1);

  if( !testMulAddConsistency(a,b) ){
    FAIL(F("TestMulAddConsistency 1 0"));
  }

  a.Set(1);
  b.Set(1);
  if( !testMulAddConsistency(a,b) ){
    FAIL(F("TestMulAddConsistency 1 1"));
  }

  a.Set(255);
  b.Set(127);
  if( !testMulAddConsistency(a,b) ){
    FAIL(F("TestMulAddConsistency 255 127"));
  }

  uint8_t aval[] = {16, 184, 76, 68};
  a.SetBytes(aval,sizeof(aval));

  uint8_t bval[] = {123,216};
  b.SetBytes(bval,sizeof(bval));
  if( !testMulAddConsistency(a,b) ){
    FAIL(F("TestMulAddConsistency {16, 184, 76, 68} {123,216}"));
  }

}

bool testDivSubConsistency(const struct bignat &a,const struct bignat &b){

  Serial.print(F("testDivSubConsistency("));
  printNat(a);
  Serial.print(F(","));
  printNat(b);
  Serial.println(F(")"));

  WORD onebuf[1];
  struct bignat one(onebuf,sizeof(onebuf));
  one.Set(1);

  WORD ibuf[4];
  struct bignat i(ibuf,sizeof(ibuf));

  WORD subbuf[8];
  struct bignat sub(subbuf,sizeof(subbuf));

  WORD divbuf[8];
  struct bignat div(divbuf,sizeof(divbuf));
  WORD rbuf[8];
  struct bignat r(rbuf,sizeof(rbuf));

  WORD vbuf[33];

  sub.Set(a);

  while(sub.Cmp(b)>=0){
    sub.Sub(sub,b);
    i.Add(i,one);
  }
  
  div.Div(a,b,r,vbuf);

  if( i.Cmp(div) != 0){
    Serial.print("a=");printlnNat(a);
    Serial.print("b=");printlnNat(b);
    Serial.print("div=");printlnNat(div);
    Serial.print("i=");printlnNat(i);
    return false;
  }

  if( r.Cmp(sub) != 0){
    Serial.print("a=");printlnNat(a);
    Serial.print("b=");printlnNat(b);
    Serial.print("r=");printlnNat(r);
    Serial.print("sub=");printlnNat(sub);
    return false;
  }

  Serial.print(F("="));
  printNat(div);
  Serial.print(F(" r "));
  printNat(r);
  Serial.println();

  return true;
}

void TestDivSubConsistency(){
  WORD abuf[4];
  struct bignat a(abuf,sizeof(abuf));
  WORD bbuf[4];
  struct bignat b(bbuf,sizeof(bbuf));

  a.Set(1);
  b.Set(1);
  if( !testDivSubConsistency(a,b) ){
    FAIL(F("testDivSubConsistency 1 1"));
  }

  a.Set(255);
  b.Set(127);
  if( !testDivSubConsistency(a,b) ){
    FAIL(F("testDivSubConsistency 255 127"));
  }

  uint8_t aval[] = {16, 56, 94, 68};
  a.SetBytes(aval,sizeof(aval));

  uint8_t bval[] = {123,216};
  b.SetBytes(bval,sizeof(bval));
  if( !testDivSubConsistency(a,b) ){
    FAIL(F("testDivSubConsistency {16, 56, 94, 68} {123,216}"));
  }

}


void TestShl(){
  WORD abuf[2];
  struct bignat a(abuf,sizeof(abuf));
  WORD bbuf[2];
  struct bignat b(bbuf,sizeof(bbuf));
  uint8_t bval[] = {1,0};
  b.SetBytes(bval,sizeof(bval));

  a.Set(128);
  a.Shl(a,1);

  if( a.Cmp(b) != 0){
    FAIL(F("TestShl 128 << 1 != 256"));
  }
}

void TestBase58String(){
  char encoded[40];
  uint8_t dataA[] = {0,235,21,35,29,252,235,96,146,88,134,182,125,6,82,153,146,89,21,174,177,114,192,102,71};

  WORD bbuf[32];
  struct bignat b(bbuf,sizeof(bbuf));
  b.SetBytes(dataA,sizeof(dataA));
  b.String(58,BITCOIN,encoded,sizeof(encoded));

  char expected[] ="NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L";

  if( strcmp(encoded,expected) != 0 ){
    Serial.println(encoded);
    Serial.println(expected);
    FAIL(F("TestBase58String Failed"));
  }
}

void setup(){
  Serial.begin(9600); 
  Serial.println("BEGIN");  

  TestCmp();
  TestMulAddConsistency();
  TestDivSubConsistency();
  TestShl();
  TestBase58String();

  Serial.println("END");
}

void loop(){
}


