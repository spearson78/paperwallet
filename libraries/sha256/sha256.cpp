#include <sha256.h>

//Derived from https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c written by Brad Conte
//Ported to Arduino by Steven Pearson
//This code is released into the public domain free of any restrictions.
//The authors request acknowledgement if the code is used, but does not require it.
//This code is provided free of any liability and without any quality claims by the authors.

#include <avr/pgmspace.h>

const uint32_t k[] PROGMEM = {
   0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
   0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
   0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
   0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
   0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
   0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
   0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
   0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

const uint32_t SHA256INITIALSTATE[] PROGMEM = {
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
};


inline uint32_t ROTR(uint32_t number,uint32_t bits){
  return ((number << (32-bits)) | (number >> bits));
}

inline uint32_t SHR(uint32_t number,uint32_t bits){
  return number >> bits;
}

inline uint32_t Sigma0(uint32_t x){
  return ROTR(x,7) ^ ROTR(x,18) ^ SHR(x,3);
}

inline uint32_t Sigma1(uint32_t x){
  return ROTR(x,17) ^ ROTR(x,19) ^ SHR(x,10);
}

inline uint32_t Epsilon0(uint32_t x){
  return ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22);
}

inline uint32_t Epsilon1(uint32_t x){
  return ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25);
}

inline uint32_t Ch(uint32_t x,uint32_t y,uint32_t z){
  return (x&y)^(~x&z);
}

inline uint32_t Maj(uint32_t x,uint32_t y,uint32_t z){
  return (x&y)^(x&z)^(y&z);
}

inline void sha256_transform(struct SHA256_CTX *ctx, uint8_t data[])
{
   uint32_t a,b,c,d,e,f,g,h,i,j,t1,t2,m[64];
      
   for (i=0,j=0; i < 16; ++i, j += 4){
      m[i] = ((uint32_t)data[j] << 24ul) | ((uint32_t)data[j+1] << 16ul) | ((uint32_t)data[j+2] << 8ul) | ((uint32_t)data[j+3]);
   }
   for ( ; i < 64; ++i){
      m[i] = Sigma1(m[i-2]) + m[i-7] + Sigma0(m[i-15]) + m[i-16];
   }
     
   a = ctx->state[0];
   b = ctx->state[1];
   c = ctx->state[2];
   d = ctx->state[3];
   e = ctx->state[4];
   f = ctx->state[5];
   g = ctx->state[6];
   h = ctx->state[7];

   for (i = 0; i < 64; ++i) {
      t1 = h + Epsilon1(e) + Ch(e,f,g) + pgm_read_dword(k+i) + m[i];
      t2 = Epsilon0(a) + Maj(a,b,c);
      h = g;
      g = f;
      f = e;
      e = d + t1;
      d = c;
      c = b;
      b = a;
      a = t1 + t2;
   }   
   
   ctx->state[0] += a;
   ctx->state[1] += b;
   ctx->state[2] += c;
   ctx->state[3] += d;
   ctx->state[4] += e;
   ctx->state[5] += f;
   ctx->state[6] += g;
   ctx->state[7] += h;
}

void sha256_init(struct SHA256_CTX *ctx)
{ 
   ctx->datalen = 0; 
   ctx->bitlen = 0;
   memcpy_P(ctx->state,SHA256INITIALSTATE,8*sizeof(uint32_t));
}

void sha256_update(struct SHA256_CTX *ctx, uint8_t data[], size_t len)
{ 
   uint32_t t,i;
   
   for (i=0; i < len; ++i) { 
      ctx->data[ctx->datalen] = data[i]; 
      ctx->datalen++; 
      if (ctx->datalen == 64) { 
         sha256_transform(ctx,ctx->data);
         ctx->bitlen += 512;
         ctx->datalen = 0;
      }  
   }  
}

void sha256_final(struct SHA256_CTX *ctx, uint8_t hash[])
{
   uint32_t i; 
   
   i = ctx->datalen; 
   
   // Pad whatever data is left in the buffer. 
   if (ctx->datalen < 56) {
      ctx->data[i++] = 0x80; 
      while (i < 56) 
         ctx->data[i++] = 0x00; 
   }  
   else { 
      ctx->data[i++] = 0x80; 
      while (i < 64) 
         ctx->data[i++] = 0x00; 
      sha256_transform(ctx,ctx->data);
      memset(ctx->data,0,56); 
   }  
   
   // Append to the padding the total message's length in bits and transform. 
   ctx->bitlen += ctx->datalen * 8;
   ctx->data[63] = ctx->bitlen;
   ctx->data[62] = ctx->bitlen >> 8; 
   ctx->data[61] = ctx->bitlen >> 16;  
   ctx->data[60] = ctx->bitlen >> 24; 
   ctx->data[59] = ctx->bitlen >> 32;
   ctx->data[58] = ctx->bitlen >> 40; 
   ctx->data[57] = ctx->bitlen >> 48; 
   ctx->data[56] = ctx->bitlen >> 56; 
   sha256_transform(ctx,ctx->data);
   
   // Since this implementation uses little endian byte ordering and SHA uses big endian,
   // reverse all the bytes when copying the final state to the output hash. 
   for (i=0; i < 4; ++i) { 
      hash[i]    = (ctx->state[0] >> (24-i*8)) & 0x000000ff; 
      hash[i+4]  = (ctx->state[1] >> (24-i*8)) & 0x000000ff; 
      hash[i+8]  = (ctx->state[2] >> (24-i*8)) & 0x000000ff;
      hash[i+12] = (ctx->state[3] >> (24-i*8)) & 0x000000ff;
      hash[i+16] = (ctx->state[4] >> (24-i*8)) & 0x000000ff;
      hash[i+20] = (ctx->state[5] >> (24-i*8)) & 0x000000ff;
      hash[i+24] = (ctx->state[6] >> (24-i*8)) & 0x000000ff;
      hash[i+28] = (ctx->state[7] >> (24-i*8)) & 0x000000ff;
   }
}


