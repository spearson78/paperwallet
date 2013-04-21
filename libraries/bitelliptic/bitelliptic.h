#ifndef BITELLIPTIC_H
#define BITELLIPTIC_H
//This code is derived form https://github.com/ThePiachu/Golang-Koblitz-elliptic-curve-DSA-library/tree/master/bitelliptic
// Copyright 2010 The Go Authors. All rights reserved.
// Copyright 2011 ThePiachu. All rights reserved.
// Copyright 2013 Steven Pearson. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <bigint.h>
#include <Arduino.h>

const uint8_t _P[] PROGMEM  ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFC,0x2F};
const uint8_t _Gx[] PROGMEM ={0x79,0xBE,0x66,0x7E,0xF9,0xDC,0xBB,0xAC,0x55,0xA0,0x62,0x95,0xCE,0x87,0x0B,0x07,0x02,0x9B,0xFC,0xDB,0x2D,0xCE,0x28,0xD9,0x59,0xF2,0x81,0x5B,0x16,0xF8,0x17,0x98};
const uint8_t _Gy[] PROGMEM ={0x48,0x3A,0xDA,0x77,0x26,0xA3,0xC4,0x65,0x5D,0xA4,0xFB,0xFC,0x0E,0x11,0x08,0xA8,0xFD,0x17,0xB4,0x48,0xA6,0x85,0x54,0x19,0x9C,0x47,0xD0,0x8F,0xFB,0x10,0xD4,0xB8};
const uint8_t _B[] PROGMEM  ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07};

struct bitcurve{
  
  const struct bigint &P;
  const struct bigint &Gx;
  const struct bigint &Gy;
  
  void ScalarMult(const struct bigint &Bx,const struct bigint &By,const uint8_t *k,int klen,struct bigint &x,struct bigint &y);
  void ScalarBaseMult(const uint8_t *k,int klen,struct bigint &x,struct bigint &y);
  void doubleJacobian(struct bigint &x,struct bigint &y,struct bigint &z);
  void _doubleJacobianZ(const struct bigint &y,struct bigint &z);
  void _doubleJacobianX(const struct bigint &f,const struct bigint &d,struct bigint &x);
  void _doubleJacobianY(const struct bigint &d,const struct bigint &e,const struct bigint &c,const struct bigint &x,struct bigint &y);
  void _doubleJacobianE(const struct bigint &x,struct bigint &e);
  void _doubleJacobianCD(const struct bigint &x,const struct bigint &y,struct bigint &c,struct bigint &dout);
  
  void addJacobian(const struct bigint &Bx,const struct bigint &By,const struct bigint &Bz,struct bigint &x,struct bigint &y,struct bigint &z);

  void _addJacobianZ(const struct bigint &z1,const struct bigint &z1z1,const struct bigint &z2z2,const struct bigint &h,struct bigint &z2);
  void _addJacobianY(const struct bigint &r,struct bigint &v,struct bigint &s1,const struct bigint &x3,const struct bigint &j,struct bigint &y2,struct bigint &vrstomp);
  void _addJacobianX(const struct bigint &r,const struct bigint &v,const struct bigint &j,struct bigint &x2);
  void _addJacobianS1R(const struct bigint &y1,const struct bigint &z2,const struct bigint &z2z2,const struct bigint &y2,const struct bigint &z1,const struct bigint &z1z1,const struct bigint &h,struct bigint &s1,struct bigint &r);
  void _addJacobianJV(const struct bigint &h,const struct bigint &u1,struct bigint &j,struct bigint &v);
  void _addJacobianHU1(const struct bigint &x1,const struct bigint &x2,const struct bigint &z1z1,const struct bigint &z2z2,struct bigint &u1,struct bigint &h);
  void _addJacobianZ12(const struct bigint &z1,const struct bigint &z2,struct bigint &z1z1,struct bigint &z2z2);
  
  void affineFromJacobian(struct bigint &x,struct bigint &y,struct bigint &z);
  void _affineFromJacobianXY(struct bigint &x,struct bigint &y,const struct bigint &zinv);
  
  int isOnCurve(const struct bigint &x,const struct bigint &y) const;
  
  bitcurve(const struct bigint &P,const struct bigint &Gx,const struct bigint &Gy);
};

#endif
