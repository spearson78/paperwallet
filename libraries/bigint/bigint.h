#ifndef BIGINT_H
#define BIGINT_H
// This code is derived from golangs math/big package
// Copyright 2009 The Go Authors. All rights reserved.
// Arduino Port Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <bignat.h>
#include <Arduino.h>

struct bigint{
  public:
    struct bignat _abs;
    byte neg;

  public:

    bigint(byte neg,WORD *data,int cap);
    bigint(WORD *data,int cap);
  
    void Mul(const struct bigint &x,const struct bigint &y);
    void Add(const struct bigint &x,const struct bigint &y);
    void Sub(const struct bigint &x,const struct bigint &y);
    void Mod(const struct bigint &x,const struct bigint &y);
    void QuoRem(const struct bigint &x,const struct bigint &y,struct bigint &r,WORD vbuf[33]);
    void Lsh(const struct bigint &x,unsigned int n);
    void GCD(struct bigint &x,const struct bigint &a,const struct bigint &b);
    void ModInverse(struct bigint &g,const struct bigint &p);

    int Cmp(const struct bigint &y) const;
  
    void Set(WORD val);
    void Set(const struct bigint &x);
    void SetBytesP(const uint8_t *data,int len);
    void SetBytes(byte neg,const uint8_t *data,int len);

    const struct bignat &Abs() const;
    int Sign() const;
    void String(WORD base,const char *map,char *out,int limit) const;

    friend class bitcurve;
};

#endif
