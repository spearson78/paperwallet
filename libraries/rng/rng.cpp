// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <rng.h>
#include <sha256.h>
#include <panic.h>
#include <progress.h>

byte getSample(){
  int a = analogRead(0);
  return (a ^ (a>>1) ^ (a>>2) ^ (a>>3) ^ (a>>4) ^ (a>>5) ^ (a>>6) ^ (a>>7))&0x01;
}

#define RNG_VERIFY

const int rounds = 50;

void rng::generate(byte *data,int dataLen){
#ifdef RNG_VERIFY
  byte run=0;
  byte last=0;
  unsigned int runs[25];
  memset(runs,0,sizeof(unsigned int)*25);
#endif

  SHA256_CTX hash;
  sha256_init(&hash);

  for( int r = 0; r < rounds ; r++){
    PROGRESS((float)r/(float)rounds);
    for( int i = 0; i < dataLen ; i++ ){
      byte build =0;
      for(int bit=0;bit<8;bit++){
        int s = getSample();
        build |= (s << bit);
#ifdef RNG_VERIFY
        if(s==last){
          run++;
          if( run > 25 ){
            PANIC(PANIC_RNG_RUN);
          }
        } else {
          runs[run]++;
          unsigned int limit = (5000 >> run)+5;
          if( runs[run] >= limit ){
            PANIC(PANIC_RNG_REGULAR);
          }
          run=0;
          last=s;
        }
#endif
      }
      sha256_update(&hash,&build,1);
    }
  }
/*
  for(int i=0;i<20;i++){
    unsigned int limit = (5000 >> i)+5;
    Serial.print("RUNS[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(runs[i]);
    Serial.print(" limit=");
    Serial.print(limit);
    
    Serial.println();
  }
*/
  sha256_final(&hash,data);
}
