#ifndef sha256_h
#define sha256_h
//Derived from https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c written by Brad Conte
//Ported to Arduino by Steven Pearson
//This code is released into the public domain free of any restrictions.
//The authors request acknowledgement if the code is used, but does not require it.
//This code is provided free of any liability and without any quality claims by the authors.

#include <Arduino.h>

struct SHA256_CTX {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
};

void sha256_init(struct SHA256_CTX *ctx);
void sha256_update(struct SHA256_CTX *ctx, uint8_t data[], size_t len);
void sha256_final(struct SHA256_CTX *ctx, uint8_t hash[]);

#endif

