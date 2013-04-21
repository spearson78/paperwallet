#ifndef RMD160_H
#define RMD160_H
// This code is derived from http://code.google.com/p/go/source/browse/ripemd160
// Copyright 2010 The Go Authors. All rights reserved.
// Arduino Port Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <Arduino.h>

const int BLOCKSIZE=64;

struct digest {
  uint32_t s[8];
  uint8_t x[BLOCKSIZE];
  int nx;
  uint64_t tc;
};

int Write(struct digest *d,uint8_t *p , int len);
void Sum(struct digest *d,uint8_t digest[20]);
void Reset(struct digest *d);

#endif
