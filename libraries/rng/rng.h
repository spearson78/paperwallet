#ifndef  RNG_H
#define  RNG_H
// Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>

namespace rng{
  void generate(byte data[32]);
}

#endif
