#ifndef PANIC_H
#define PANIC_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

typedef unsigned char paniccode;

const paniccode PANIC_UNKNOWN_ERROR=0;

void PANIC(paniccode p);

#endif

