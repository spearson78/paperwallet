#ifndef BIGNAT_H
#define BIGNAT_H
// This code is derived from golangs math/big package
// Copyright 2009 The Go Authors. All rights reserved.
// Arduino Port Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <Arduino.h>

typedef unsigned char WORD;

struct bignat {
  public:
    WORD *data;
    int cap;
    int len;

  public:
    void make(int n);
    void norm();

    static WORD addWW(WORD *z0,WORD x,WORD y,WORD c);
    static WORD addVW(WORD *z,int zlen,const WORD *x,WORD y);

    static WORD subWW(WORD *z0,WORD x,WORD y,WORD c);
    static WORD subVW(WORD *z,int zlen,const WORD *x,WORD y);
    
    static WORD mulAddVWW(WORD *z,int zlen,const WORD *x,WORD y,WORD r);
    static WORD addMulVVW(WORD *z,int zlen,const WORD *x,WORD y);
    static WORD mulAddWWW(WORD *z0,WORD x,WORD y,WORD c);
    static WORD mulWW(WORD *z0,WORD x,WORD y);

    static WORD divWVW(WORD *z,int zlen,WORD xn,const WORD *x,WORD y);

    static WORD leadingZeros(WORD x);
    static WORD divWW(WORD u1,WORD u0,WORD v,WORD *r);
    static void reverseInPlace(char *in,int l);
    
    static WORD shlVU(WORD *z,int n,const WORD *x,unsigned int s);
    static WORD shrVU(WORD *z,int lenz,const WORD *x,unsigned int s);
    static int greaterThan(WORD x1,WORD x2,WORD y1,WORD y2);

    static WORD addVV(WORD *t,int limit,const WORD *x,const WORD *y);
    static WORD subVV(WORD *z,int limit,const WORD *x,const WORD *y);

    void mulAddWW(const struct bignat &x,WORD y,WORD r);
    void basicMul(const struct bignat &x,const struct bignat &y);

    WORD divW(const struct bignat &u,WORD v);
    void divLarge(const struct bignat &u,const struct bignat &v,struct bignat &r,WORD vbuf[33]);

  public:
    bignat(WORD *data,int cap);
    void Set(const struct bignat &b);
    void Set(WORD w);

    void Add(const struct bignat &x,const struct bignat &y);
    void Sub(const struct bignat &x,const struct bignat &y);
    
    void Mul(const struct bignat &x,const struct bignat&y);
    void Div(const struct bignat &x,const struct bignat& y,struct bignat &r,WORD vbuf[33]);

    void Shl(const struct bignat &x,unsigned int n);
    
    void SetBytes(const uint8_t *buf,int len);
    void SetBytesP(const uint8_t *buf,int len);
    int Cmp(const struct bignat &x) const;
    WORD Word() const;
    
    void String(WORD base,const char *map,char *out,int limit) const;
    void Bytes(uint8_t *out,int limit) const;

    friend class bigint;
    friend class bitcurve;
};

#endif
