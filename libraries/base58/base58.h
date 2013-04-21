#ifndef  BASE58_H
#define  BASE58_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>

namespace base58{
  void encode(byte *data,int dataLen,char *out,int outlen);
}

#endif
