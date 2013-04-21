// This code is derived from http://code.google.com/p/go/source/browse/ripemd160
// Copyright 2010 The Go Authors. All rights reserved.
// Arduino Port Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.
#include <rmd160.h>
#include <panic.h>

#define RMD160CHECKNX

const uint32_t RMDINITIALSTATE[] PROGMEM = {
  0x67452301ul,
  0xefcdab89ul,
  0x98badcfeul,
  0x10325476ul,
  0xc3d2e1f0ul
};

void Reset(struct digest *d){
  memcpy_P(d->s,RMDINITIALSTATE,5*sizeof(uint32_t));
  d->nx=0;
  d->tc=0;
}

// work buffer indices and roll amounts for one line
const byte _n[80] PROGMEM = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
        3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
        1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
        4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13
};

const byte _r[80] PROGMEM ={
        11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
        7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
        11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
        11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
        9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6
};

// same for the other parallel one
const byte n_[80] PROGMEM = {
        5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
        6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
        15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
        8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
        12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11
};

const byte r_[80] PROGMEM = {
        8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
        9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
        9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
        15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
        8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11
};

inline void _Rotate(uint32_t *a,uint32_t *b,uint32_t *c,uint32_t *d,uint32_t *e,uint32_t *alpha,uint32_t *beta,uint32_t s){
  *alpha = (*alpha<<s | *alpha>>(32-s)) + *e;           
  *beta = (*c)<<10 | (*c)>>22;
  
  *a=*e;
  *c=*b;
  *e=*d;
  *b=*alpha;
  *d=*beta;
}

inline int _Block(struct digest *md, uint8_t *p , int len) {

        int n = 0;
        uint32_t x[16];
        
        while( len >= BLOCKSIZE ){
          uint32_t a = md->s[0];
          uint32_t b = md->s[1];
          uint32_t c = md->s[2];
          uint32_t d = md->s[3];
          uint32_t e = md->s[4];
          
          uint32_t aa = a;
          uint32_t bb = b;
          uint32_t cc = c;
          uint32_t dd = d;
          uint32_t ee = e;

          int j = 0;
          for( int i=0;i<16;i++){
            x[i] = (uint32_t)p[j] | ((uint32_t)p[j+1])<<8 | ((uint32_t)p[j+2])<<16 | ((uint32_t)p[j+3])<<24;
            j += 4;
          }
          
          
          int i = 0;
          
          uint32_t alpha;
          uint32_t s;
          uint32_t beta;
          
          
          //round 1
          while( i<16 ){
            alpha = a + (b ^ c ^ d) + x[pgm_read_byte(_n+i)];
            s = pgm_read_byte(_r+i);
            _Rotate(&a,&b,&c,&d,&e,&alpha,&beta,s);
            
            // parallel line
            alpha = aa + (bb ^ (cc | ~dd)) + x[pgm_read_byte(n_+i)] + 0x50a28be6ul;
            s = pgm_read_byte(r_+i);
            
            _Rotate(&aa,&bb,&cc,&dd,&ee,&alpha,&beta,s);
            
            i++;          
          }
          
          // round 2
          while(i < 32){
            alpha = a + (b&c | ~b&d) + x[pgm_read_byte(_n+i)] + 0x5a827999ul;
            s = pgm_read_byte(_r+i);
            _Rotate(&a,&b,&c,&d,&e,&alpha,&beta,s);

            
            // parallel line
            alpha = aa + (bb&dd | cc&~dd) + x[pgm_read_byte(n_+i)] + 0x5c4dd124ul;
            s = pgm_read_byte(r_+i);
            _Rotate(&aa,&bb,&cc,&dd,&ee,&alpha,&beta,s);

            i++;
          }

          // round 3
          while( i < 48 ) {
            
            alpha = a + ((b|~c)^d) + x[pgm_read_byte(_n+i)] + 0x6ed9eba1ul;
            s = pgm_read_byte(_r+i);
            _Rotate(&a,&b,&c,&d,&e,&alpha,&beta,s);
  
            // parallel line
            alpha = aa + ((bb | ~cc) ^ dd) + x[pgm_read_byte(n_+i)] + 0x6d703ef3ul;
            s = pgm_read_byte(r_+i);
            _Rotate(&aa,&bb,&cc,&dd,&ee,&alpha,&beta,s);
  
            i++;
          }
          
          // round 4
          while( i < 64 ){
            alpha = a + (b&d | c&~d) + x[pgm_read_byte(_n+i)] + 0x8f1bbcdcul;
            s = pgm_read_byte(_r+i);
            _Rotate(&a,&b,&c,&d,&e,&alpha,&beta,s);
            
            // parallel line
            alpha = aa + (bb&cc | ~bb&dd) + x[pgm_read_byte(n_+i)] + 0x7a6d76e9ul;
            s = pgm_read_byte(r_+i);
            _Rotate(&aa,&bb,&cc,&dd,&ee,&alpha,&beta,s);
  
            i++;
          }
 
          // round 5
          while( i < 80 ) {
            alpha = a + (b ^ (c | ~d)) + x[pgm_read_byte(_n+i)] + 0xa953fd4eul;
            s = pgm_read_byte(_r+i);
            _Rotate(&a,&b,&c,&d,&e,&alpha,&beta,s);
  
            // parallel line
            alpha = aa + (bb ^ cc ^ dd) + x[pgm_read_byte(n_+i)];
            s = pgm_read_byte(r_+i);
            _Rotate(&aa,&bb,&cc,&dd,&ee,&alpha,&beta,s);
  
            i++;
          }
         
          // combine results
          dd += c + (md->s[1]);
          md->s[1] = (md->s[2]) + d + ee;
          md->s[2] = (md->s[3]) + e + aa;
          md->s[3] = (md->s[4]) + a + bb;
          md->s[4] = (md->s[0]) + b + cc;
          md->s[0] = dd;
          
          p+=BLOCKSIZE;
          len -= BLOCKSIZE;
          n+=BLOCKSIZE;
        }
        
        return n;
}

int Write(struct digest *d,uint8_t *p , int len){

  int nn = len;
  d->tc += nn;
  
  //There are left over bytes from the last call to write try to build a block
  if( d->nx > 0) {
    int n = len;
    if( len > BLOCKSIZE-d->nx ){
      n = BLOCKSIZE - d->nx;
    }
    for( int i=0;i<n;i++){
      d->x[d->nx+i] = p[i];
    }
    d->nx += n;
    if( d->nx == BLOCKSIZE ){
      _Block(d,d->x,BLOCKSIZE);
      d->nx = 0;
    }
    p += n;
    len -= n;
  }
  
  //Write bytes into block. If the len is smaller than BLOCKSIZE nothing will be written.
  int n = _Block(d,p,len);
  p += n;
  len -= n;
  
  if( len > 0 ){
    //Copy remaining bytes into temporary buffer;
    memcpy(d->x,p,len);
    d->nx = len;
  }
  
  return nn;  
}

void Sum(struct digest *d,uint8_t digest[20]) {
  uint64_t tc = d->tc;
  
  uint8_t tmp[64];
  memset(tmp,0,sizeof(tmp));
  tmp[0]=0x80;
  
  if( tc%64 < 56 ){
    Write(d,tmp,56-tc%64);
  } else {
    Write(d,tmp,64+56-tc%64);
  }
  
  tc = tc << 3;
  for( uint64_t i = 0 ; i < 8 ;i++){
    tmp[i] = (byte)(tc >> (8ul*i));
  }
  
  Write(d,tmp,8);
  
#ifdef RMD160CHECKNX
  if( d->nx != 0 ){
    PANIC(PANIC_RMD160_SUM_NXNOTZERO);
  }
#endif
  
  for( int i = 0 ; i < 8 ;i++){
    uint32_t s = d->s[i];
    digest[i*4] = (byte)(s);
    digest[i*4+1] = (byte)(s>>8);
    digest[i*4+2] = (byte)(s>>16);
    digest[i*4+3] = (byte)(s>>24);
  }
  
}
