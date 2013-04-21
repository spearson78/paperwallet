// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "base58.h"
#include <bignat.h>

const char BITCOIN[] PROGMEM = {"123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"};

void base58::encode(byte *data,int dataLen,char *out,int outlen){
  WORD abuf[37];
  struct bignat a(abuf,sizeof(abuf));

  int i;
  for(i = 0;i<dataLen&&data[i]==0;i++){
    out[i]=pgm_read_byte(BITCOIN);
  }

  a.SetBytes(data,dataLen);
  a.String(58,BITCOIN,out+i,outlen-i);
}
