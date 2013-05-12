#ifndef PANIC_H
#define PANIC_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

typedef unsigned char paniccode;

const paniccode PANIC_UNKNOWN_ERROR=1;
const paniccode PANIC_NAT_MAKE_OVERFLOW=2;
const paniccode PANIC_NAT_SUB_UNDERFLOW=3;
const paniccode PANIC_NAT_SUB_CNONZERO=4;
const paniccode PANIC_NAT_TOWORD_OVERFLOW=5;
const paniccode PANIC_NAT_DIVZERO=6;
const paniccode PANIC_NAT_TOSTRING_OVERFLOW=7;
const paniccode PANIC_NAT_MUL_ALIAS=8;
const paniccode PANIC_NAT_DIV_ALIAS=9;
const paniccode PANIC_NAT_DIV_SHIFTOFF=10;
const paniccode PANIC_INT_MOD_ALIAS=11;
const paniccode PANIC_RMD160_SUM_NXNOTZERO=12;
const paniccode PANIC_BITADDRESS_PK_NOTONCURVE=13;
const paniccode PANIC_NAT_BYTES_OVERFLOW=14;
const paniccode PANIC_RNG_FAIL_DEBIAS=15;
const paniccode PANIC_RNG_FAIL_NIST=16;
const paniccode PANIC_NAT_SET_ALIAS=17;

void PANIC(paniccode p);

#endif

