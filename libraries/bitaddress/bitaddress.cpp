// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <bitaddress.h>
#include <base58.h>

#include <bitelliptic.h>
#include <rmd160.h>
#include <sha256.h>
#include <base58.h>
#include <panic.h>

#define ADDRESS_VERIFY

void bitaddress::generatePublicKey(uint8_t *PRIVATE,struct bigint &pubx,struct bigint &puby){
  WORD pbuf[32];
  WORD gxbuf[32];
  WORD gybuf[32];
  
  struct bigint P(pbuf,sizeof(pbuf));
  struct bigint Gx(gxbuf,sizeof(gxbuf));
  struct bigint Gy(gybuf,sizeof(gybuf));
  P.SetBytesP(_P,sizeof(_P));
  
  //Gx and Gy are only needed for the initial add step. I may be able to avoid allocating them by allocating them within addjacobian
  Gx.SetBytesP(_Gx,sizeof(_Gx));
  Gy.SetBytesP(_Gy,sizeof(_Gy));
  
  struct bitcurve S256(P,Gx,Gy);
  
  S256.ScalarBaseMult(PRIVATE,32,pubx,puby);

#ifdef ADDRESS_VERIFY
  int oncurve = S256.isOnCurve(pubx,puby);
  if( !oncurve ){
    PANIC(PANIC_BITADDRESS_PK_NOTONCURVE);
  }
#endif
}

void bitaddress::generatePrivateWIF(uint8_t *PRIVATE,char *out,int limit){
  WORD wifbuf[37];
  wifbuf[0]=0x80;
  memcpy(wifbuf+1,PRIVATE,32);
  
  struct SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx,wifbuf,33);
  
  uint8_t hash[32];
  sha256_final(&ctx,hash);
  
  sha256_init(&ctx);
  sha256_update(&ctx,hash,32);
  sha256_final(&ctx,hash);
  
  wifbuf[33]=hash[0];
  wifbuf[34]=hash[1];
  wifbuf[35]=hash[2];
  wifbuf[36]=hash[3];
  
  base58::encode(wifbuf,sizeof(wifbuf),out,limit);
}

void bitaddress::generateAddress(const struct bigint &x,const struct bigint &y,char *out,int limit){
  uint8_t four=4;
  
  struct SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx,&four,1);
  
  uint8_t tbuf[32];
  x._abs.Bytes(tbuf,sizeof(tbuf));
  sha256_update(&ctx,tbuf,x._abs.len);
  y._abs.Bytes(tbuf,sizeof(tbuf));
  sha256_update(&ctx,tbuf,y._abs.len);
  
  uint8_t hash[32];
  sha256_final(&ctx,hash);
  
  uint8_t digest[25];
  struct digest d;
  Reset(&d);
  Write(&d,hash,sizeof(hash));
  Sum(&d,digest+1);
  
  digest[0]=0;
  
  sha256_init(&ctx);
  sha256_update(&ctx,digest,21);
  sha256_final(&ctx,hash);

  sha256_init(&ctx);
  sha256_update(&ctx,hash,sizeof(hash));
  sha256_final(&ctx,hash);
  
  digest[21]=hash[0];
  digest[22]=hash[1];
  digest[23]=hash[2];
  digest[24]=hash[3];
  
  base58::encode(digest,sizeof(digest),out,limit);
}
