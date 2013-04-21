#ifndef BITADDRESS_H
#define BITADDRESS_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <bigint.h>

namespace bitaddress{
  void generatePublicKey(uint8_t *PRIVATE,struct bigint &pubx,struct bigint &puby);
  void generatePrivateWIF(uint8_t *PRIVATE,char *out,int limit);
  void generateAddress(const struct bigint &pubx,const struct bigint &puby,char *out,int limit);
}

#endif
