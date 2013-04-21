// This code is derived from https://github.com/tz1/qrduino.git
// Copyright 2010, tz@execpc.com.
// Copyright 2013, Steven Pearson
// Released under ther terms of the GNU General Public License v3.
// that can be found in the GPLV3_LICENSE file.

#include <string.h>
#include "qrencode.h"

#define SETQRBIT(x,y) qrframe[((x)>>3) + (y) * WDB] |= 0x80 >> ((x) & 7)
#define TOGQRBIT(x,y) qrframe[((x)>>3) + (y) * WDB] ^= 0x80 >> ((x) & 7)

const unsigned char neccblk1 = 4;
const unsigned char neccblk2 = 0;
const unsigned char datablkw = 15;
const unsigned char eccblkwid = 28;
const unsigned char VERSION = 6;
const unsigned char ECCLEVEL = 4;
unsigned char rlens[42];

const unsigned char framebase[] PROGMEM = {
0xfe,0x00,0x00,0x00,0x3f,0x80, //3
0x82,0x00,0x00,0x00,0x20,0x80, //3
0xba,0x00,0x00,0x00,0x2e,0x80, //3
0xba,0x00,0x00,0x00,0x2e,0x80, //3
0xba,0x00,0x00,0x00,0x2e,0x80, //3
0x82,0x00,0x00,0x00,0x20,0x80, //3
0xfe,0xaa,0xaa,0xaa,0xbf,0x80, //6
/*
0x00,0x00,0x00,0x00,0x00,0x00, //0
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, //0
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, //0
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, //0
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, //0
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00,
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, 
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00,
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, 
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, 
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, 
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, 
0x02,0x00,0x00,0x00,0x00,0x00, //1
0x00,0x00,0x00,0x00,0x00,0x00, 
*/
0x02,0x00,0x00,0x00,0xf8,0x00, //1
0x00,0x80,0x00,0x00,0x88,0x00, //2
0xfe,0x00,0x00,0x00,0xa8,0x00, //2
0x82,0x00,0x00,0x00,0x88,0x00, //2
0xba,0x00,0x00,0x00,0xf8,0x00, //2
0xba,0x00,0x00,0x00,0x00,0x00, //1
0xba,0x00,0x00,0x00,0x00,0x00, //1
0x82,0x00,0x00,0x00,0x00,0x00, //1
0xfe,0x00,0x00,0x00,0x00,0x00, //1
};

const unsigned char framask[] PROGMEM = {
0xff,0xff,0xff,0xff,0xff,0xf8,
0x10,0x04,0x00,0x80,0x08,0x00,
0x40,0x01,0x00,0x02,0x00,0x02,
0x00,0x01,0x00,0x00,0x40,0x00,
0x08,0x00,0x00,0x80,0x00,0x04,
0x00,0x00,0x10,0x00,0x00,0x20,
0x00,0x00,0x20,0x00,0x00,0x10,
0x00,0x00,0x04,0x00,0x00,0x00,
0x80,0x00,0x00,0x08,0x00,0x00,
0x00,0x40,0x00,0x00,0x01,0x00,
0x00,0x00,0x02,0x00,0x00,0x00,
0x02,0x00,0x00,0x00,0xff,0xc0,
0x00,0x00,0x7f,0xf0,0x00,0x00,
0x1f,0xfe,0x00,0x00,0x03,0xff,
0xe0,0x00,0x00,0x3f,0xff,0x00,
0x00,0x00,0x07,0xfc,0x00,0x00,
0x00,0x0f,0xf8,0x00,0x00,0x00,
0x0f,0xf8,0x00,0x00,0x00,0x00,
};


//========================================================================
// Reed Solomon error correction
inline static unsigned modnn(unsigned x)
{
    while (x >= 255) {
        x -= 255;
        x = (x >> 8) + (x & 255);
    }
    return x;
}


#define glog(x) (g0log[x])
#define gexp(x) (g0exp[x])
void qrcontext::gentables() {
#define GFPOLY (0x11d)
    int i,j;
    
    this->g0log[0] = 255;
    this->g0exp[255] = 0;
    j = 1;
    for (i = 0; i < 255; i++) {
        this->g0log[j] = i;
        this->g0exp[i] = j;
        
        j <<= 1;
        if (j & 256)
            j ^= GFPOLY;
        j &= 255;
    }
}

void qrcontext::initrspoly(unsigned char eclen, unsigned char *genpoly)
{
    unsigned char i, j;

    gentables();

    genpoly[0] = 1;
    for (i = 0; i < eclen; i++) {
        genpoly[i + 1] = 1;
        for (j = i; j > 0; j--)
            genpoly[j] = genpoly[j]
                ? genpoly[j - 1] ^ gexp(modnn(glog(genpoly[j]) + i)) : genpoly[j - 1];
        genpoly[0] = gexp(modnn(glog(genpoly[0]) + i));
    }
    for (i = 0; i <= eclen; i++)
        genpoly[i] = glog(genpoly[i]);     // use logs for genpoly[]
}

void qrcontext::appendrs(unsigned char *data, unsigned char dlen, 
              unsigned char *ecbuf, unsigned char eclen, unsigned char *genpoly)
{
    unsigned char i, j, fb;

    memset(ecbuf, 0, eclen);
    for (i = 0; i < dlen; i++) {
        fb = this->g0log[data[i] ^ ecbuf[0]];
        if (fb != 255)          /* fb term is non-zero */
            for (j = 1; j < eclen; j++)
                ecbuf[j-1] = ecbuf[j] ^ gexp(modnn(fb + genpoly[eclen - j]));
        else
            memmove(ecbuf, ecbuf + 1, eclen - 1);
        ecbuf[eclen - 1] = fb == 255 ? 0 : this->g0exp[modnn(fb + genpoly[0])];
    }
}

//========================================================================
// 8 bit data to QR-coded 8 bit data
void qrcontext::stringtoqr()
{
    unsigned i;
    unsigned size, max;
    size = strlen((char *) strinbuf);

    max = datablkw * (neccblk1 + neccblk2) + neccblk2;
    if (size >= max - 2) {
        size = max - 2;
        if (VERSION > 9)
            size--;
    }

    i = size;
    if (VERSION > 9) {
        strinbuf[i + 2] = 0;
        while (i--) {
            strinbuf[i + 3] |= strinbuf[i] << 4;
            strinbuf[i + 2] = strinbuf[i] >> 4;
        }
        strinbuf[2] |= size << 4;
        strinbuf[1] = size >> 4;
        strinbuf[0] = 0x40 | (size >> 12);
    } else {
        strinbuf[i + 1] = 0;
        while (i--) {
            strinbuf[i + 2] |= strinbuf[i] << 4;
            strinbuf[i + 1] = strinbuf[i] >> 4;
        }
        strinbuf[1] |= size << 4;
        strinbuf[0] = 0x40 | (size >> 4);
    }
    i = size + 3 - (VERSION < 10);
    while (i < max) {
        strinbuf[i++] = 0xec;
        // buffer has room        if (i == max)            break;
        strinbuf[i++] = 0x11;
    }

    // calculate and append ECC
    unsigned char *ecc = &strinbuf[max];
    unsigned char *dat = strinbuf;
    initrspoly(eccblkwid,qrframe);

    for (i = 0; i < neccblk1; i++) {
        appendrs(dat, datablkw, ecc, eccblkwid, qrframe);
        dat += datablkw;
        ecc += eccblkwid;
    }
    for (i = 0; i < neccblk2; i++) {
        appendrs(dat, datablkw + 1, ecc, eccblkwid, qrframe);
        dat += datablkw + 1;
        ecc += eccblkwid;
    }
    unsigned j;
    dat = qrframe;
    for (i = 0; i < datablkw; i++) {
        for (j = 0; j < neccblk1; j++)
            *dat++ = strinbuf[i + j * datablkw];
        for (j = 0; j < neccblk2; j++)
            *dat++ = strinbuf[(neccblk1 * datablkw) + i + (j * (datablkw + 1))];
    }
    for (j = 0; j < neccblk2; j++)
        *dat++ = strinbuf[(neccblk1 * datablkw) + i + (j * (datablkw + 1))];
    for (i = 0; i < eccblkwid; i++)
        for (j = 0; j < neccblk1 + neccblk2; j++)
            *dat++ = strinbuf[max + i + j * eccblkwid];
    memcpy(strinbuf, qrframe, max + eccblkwid * (neccblk1 + neccblk2));

}

//========================================================================
// Frame data insert following the path rules
inline static unsigned char ismasked(unsigned char x, unsigned char y)
{
    unsigned bt;
    if (x > y) {
        bt = x;
        x = y;
        y = bt;
    }
    bt = y;
    bt += y * y;
    bt >>= 1;
    bt += x;
    return (__LPM(&framask[bt >> 3]) >> (7 - (bt & 7))) & 1;
}

inline void copyframebasetoqrframe(unsigned char *qrframe){
  //memcpy_P(qrframe, framebase, WDB * WD);
  
  //This saves 100 bytes
  int y;
  
  memset(qrframe,0,WDB*WD);
  
  memcpy_P(qrframe, framebase, WDB * 7);
  memcpy_P(qrframe + (WDB*32), framebase + (WDB*7), WDB * 11);

  for( y = 0 ; y < WD ; y+=2 ){
      qrframe[WDB*y] |= 0x2;
  }
  
}

void qrcontext::fillframe()
{
    unsigned i;
    unsigned char d, j;
    unsigned char x, y, ffdecy, ffgohv;

    copyframebasetoqrframe(qrframe);
    x = y = WD - 1;
    ffdecy = 1;                 // up, minus
    ffgohv = 1;

    /* inteleaved data and ecc codes */
    for (i = 0; i < ((datablkw + eccblkwid) * (neccblk1 + neccblk2) + neccblk2); i++) {
        d = strinbuf[i];
        for (j = 0; j < 8; j++, d <<= 1) {
            if (0x80 & d)
                SETQRBIT(x, y);
            do {                // find next fill position
                if (ffgohv)
                    x--;
                else {
                    x++;
                    if (ffdecy) {
                        if (y != 0)
                            y--;
                        else {
                            x -= 2;
                            ffdecy = !ffdecy;
                            if (x == 6) {
                                x--;
                                y = 9;
                            }
                        }
                    } else {
                        if (y != WD - 1)
                            y++;
                        else {
                            x -= 2;
                            ffdecy = !ffdecy;
                            if (x == 6) {
                                x--;
                                y -= 8;
                            }
                        }
                    }
                }
                ffgohv = !ffgohv;
            } while (ismasked(x, y));
        }
    }

}

//========================================================================
// Masking 
void qrcontext::applymask()
{
    unsigned char x, y;

    for (y = 0; y < WD; y++)
        for (x = 0; x < WD; x++)
            if (!((x + y) & 1) && !ismasked(x, y))
                TOGQRBIT(x, y);
    return;
}

void qrcontext::addfmt()
{
    unsigned fmtbits;
    unsigned char i;

    fmtbits = 0x1689;
    // low byte
    for (i = 0; i < 8; i++, fmtbits >>= 1)
        if (fmtbits & 1) {
            SETQRBIT(WD - 1 - i, 8);
            if (i < 6)
                SETQRBIT(8, i);
            else
                SETQRBIT(8, i + 1);
        }
    // high byte
    for (i = 0; i < 7; i++, fmtbits >>= 1)
        if (fmtbits & 1) {
            SETQRBIT(8, WD - 7 + i);
            if (i)
                SETQRBIT(6 - i, 8);
            else
                SETQRBIT(7, 8);
        }
}

void qrcontext::qrencode(const char* str)
{
    strcpy((char *)this->strinbuf,str);
    stringtoqr();
    fillframe();               // Inisde loop to avoid having separate mask buffer
    applymask();
    addfmt();               // add in final format bytes
}

unsigned char qrcontext::getQRBit(int x,int y)  const{
  return ( qrframe[((x)>>3) + (y) * WDB] >> (7-((x) & 7 ))) & 1;
}
