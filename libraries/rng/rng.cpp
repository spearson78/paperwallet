// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <rng.h>
#include <sha256.h>
#include <panic.h>
#include <progress.h>

#define NIST_RNG_VERIFY
#define NIST_RUN_RNG_VERIFY
#define DEBIAS

//#define DEBUG

//#define RNGVALDEBUG

#ifdef DEBUG
void DBGPRINT(char *str);
#endif

byte getSampleImpl(){
  int s = analogRead(0);
  //Analog values have 10 bits of accuracy. Condense these 10 bits of noise into 1 bit
  byte r = (s ^ s>>1 ^ s>>2  ^ s>>3 ^ s>>4 ^ s>>5 ^ s>>6 ^ s>>7 ^ s>>8 ^ s>>9)&0x01;
  return r;
}

byte getSample(){
#ifdef DEBIAS
  //Von neumann debiasing
  for(byte i=0;i<100;i++){
    byte s1 =getSampleImpl();
    byte s2 =getSampleImpl();

#ifdef RNGVALDEBUG
  char out[5];
  itoa(s1,out,10);
  DBGPRINT(out);
  itoa(s2,out,10);
  DBGPRINT(out);
#endif    

    //debias
    if(s1 != s2){
      return s1;
    }
  }
  PANIC(PANIC_RNG_FAIL_DEBIAS);
#else
  return getSampleImpl();
#endif
}

const int rounds = 50;
const int n=8*rounds*32;

bool generateimpl(byte data[32]){
#ifdef NIST_RNG_VERIFY
  byte last=0;  
  int p=0;
  int v=0;
#endif

  for( byte r = 0; r < rounds ; r++){
    PROGRESS((float)r/(float)rounds);
    for( byte i = 0; i < 32 ; i++ ){
      for(byte bit=0;bit<8;bit++){
        byte s = getSample();
        if(data!=NULL){
          data[i] ^= (s<<bit);
        }
#ifdef NIST_RNG_VERIFY
        if( s==1 ){
          p++;
        }
        if(s!=last){
          v++;
          last=s;
        }
#endif
      }
    }
  }

#ifdef NIST_RNG_VERIFY

  float rootn = sqrt(n);
  float roottwo = sqrt(2);

  float freq = abs(n-(p<<1));

  float sobs = freq/rootn;
  float Pfreq = sobs/roottwo;

  if(Pfreq>1.82139){
#ifdef DEBUG
    char out[5];
    itoa(p,out,10);
    DBGPRINT(out);

    DBGPRINT("FAIL FREQ");
#endif
    return false;
  } else {
#ifdef NIST_RUN_RNG_VERIFY
    float pi = (float)p/n;
    float twonpi=2.0*n*pi;
    float tworoottwonpi=2.0*sqrt(2.0*n)*pi;

    float ompi = 1.0-pi;
    float Prun = abs(((float)v-twonpi*(ompi)))/(tworoottwonpi*ompi);

    if(Prun>1.82139){
#ifdef DEBUG
    DBGPRINT("FAIL RUN");
#endif
      return false;
    }
#endif
  }
#endif
  return true;
}

void rng::generate(byte data[32]){

  bool pass = generateimpl(data);
#ifdef NIST_RNG_VERIFY

  //If the value looks non random check 10 more times to ensure the random number generator is still functioning
  if( !pass ){
    byte failcount=0;
    for(byte i=0;i<10;i++){      
#ifdef DEBUG
      DBGPRINT("CHECK RNG");
#endif
      if(!generateimpl(NULL)){
        failcount++;
        //10% chance of seeing a failure in 10 samples
        if(failcount>2){
          PANIC(PANIC_RNG_FAIL_NIST);
        }
      }
    }
  }
#endif
}
