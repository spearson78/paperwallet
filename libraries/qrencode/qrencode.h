#ifndef QRENCODE_H
#define QRENCODE_H
// This code is derived from https://github.com/tz1/qrduino.git
// Copyright 2010, tz@execpc.com.
// Copyright 2013, Steven Pearson
// Released under ther terms of the GNU General Public License v3.
// that can be found in the GPLV3_LICENSE file.

#include <avr/pgmspace.h>

const unsigned char WD = 41;
const unsigned char WDB = 6;

struct qrcontext{
  public:
    void qrencode(const char* strinbuf);
    unsigned char getQRBit(int x,int y) const;

  public:
    //TODO: these lookup tables are only needed during encoding
    unsigned char g0log[256];
    unsigned char g0exp[256];
    //strinbuf is only needed during encoding
    unsigned char strinbuf[246];

    unsigned char qrframe[600];

    void gentables();
    void initrspoly(unsigned char eclen, unsigned char *genpoly);
    void appendrs(unsigned char*, unsigned char, unsigned char*, unsigned char, unsigned char*);
    void stringtoqr();
    void applymask();
    void addfmt();
    void fillframe();
};

#endif
