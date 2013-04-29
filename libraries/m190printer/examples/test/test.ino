#include <m190printer.h>

static const byte ME[] PROGMEM=
{
0x00,0x00,0x00,0x00,0x00,0xcd,0x74,0xff,0x3a,0x40,0x00,0x10,0x32,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x9a,0x6b,0xdf,0xf6,0xc0,0x08,0x10,0x6e,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0xcf,0xba,0xef,0xbb,0x44,0x0a,0x18,0x77,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0xdc,0x7b,0xdf,0xf7,0xc4,0x1a,0x20,0xf7,0x19,0x00,0x0c,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0xef,0xaf,0xfd,0x76,0xf2,0x06,0x98,0x7e,0x08,0x00,0x01,0x00,0x00,
0x00,0x00,0x00,0x20,0xc0,0xee,0x1b,0xef,0xf7,0xa6,0x1d,0xb0,0xff,0x39,0x00,0x0d,0x00,0x00,
0x00,0x00,0x00,0x20,0xa0,0xff,0x8f,0x68,0x07,0xf5,0x16,0xa8,0xf7,0x08,0x80,0x0a,0x00,0x00,
0x00,0x00,0x00,0x20,0xd0,0xdf,0x3f,0x40,0xbd,0xf6,0x2e,0x70,0xff,0x19,0x81,0x1d,0x00,0x00,
0x00,0x00,0x00,0x10,0x50,0xef,0x07,0xa0,0xff,0xbf,0x1f,0xd4,0xff,0xaa,0xc0,0x96,0x01,0x00,
0x00,0x00,0x00,0x20,0x60,0xdf,0x02,0xfa,0xff,0xff,0x35,0xe8,0xff,0x9a,0x81,0x1d,0x03,0x00,
0x10,0x00,0x00,0x30,0xf0,0x14,0xc0,0xff,0xff,0xff,0x0f,0xf8,0xff,0x4d,0xd1,0x97,0x01,0x00,
0x20,0x00,0x00,0x50,0x40,0x00,0xd0,0xff,0xff,0xff,0xff,0xd5,0xff,0xdb,0xab,0x95,0x93,0x00,
0x10,0x00,0x20,0x00,0x60,0x00,0xfc,0xff,0xff,0xff,0xff,0xbb,0xef,0xb6,0xda,0xaf,0xa9,0x00,
0x20,0x00,0x00,0x00,0xc0,0x00,0xf8,0xff,0xff,0xff,0xff,0xef,0xdd,0xed,0xb2,0xae,0xab,0x00,
0x00,0x00,0x00,0x00,0x50,0x00,0xfe,0xff,0xff,0xff,0xff,0x5f,0xbf,0xd6,0xde,0xdf,0x5f,0x00,
0x00,0x00,0x00,0x00,0xe0,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xba,0xdd,0xb9,0xbb,0xdb,0x01,
0x00,0x00,0x00,0x00,0x50,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xd5,0x36,0xfb,0xed,0xb7,0x00,
0x00,0x00,0x00,0x00,0x40,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xab,0x6d,0xd5,0xdf,0xf7,0x01,
0x00,0x00,0x00,0x00,0xf0,0xe8,0xff,0xff,0xff,0xff,0xff,0xff,0xe7,0xda,0xba,0xea,0xd6,0x81,
0x00,0x00,0x00,0x00,0xc0,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0x0f,0xab,0xba,0xdf,0xb7,0x82,
0x00,0x00,0x00,0x00,0xb0,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x8f,0xd0,0x6a,0xf5,0x7b,0xc1,
0x00,0xa0,0x00,0x00,0xe0,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xa3,0xda,0xae,0xef,0x82,
0x01,0x00,0x00,0x00,0x5c,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x68,0x55,0xfb,0xaf,0xa1,
0x00,0x00,0x00,0x00,0x50,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x53,0xd5,0x5e,0xbf,0xa2,
0x01,0x00,0x00,0x00,0xe8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x62,0x5b,0xdb,0xef,0x51,
0x00,0x00,0x00,0x00,0xd0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x47,0xd6,0xba,0x5e,0xe3,
0x01,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x65,0xb5,0xd6,0xab,0xd2,
0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xea,0xba,0x7f,0xd3,
0x01,0x00,0x00,0x00,0xfc,0xff,0xff,0x7f,0x7f,0xf7,0xff,0xff,0xff,0x23,0xbd,0xfd,0xa7,0xaa,
0x00,0x00,0x00,0x00,0xfc,0xff,0xff,0xbf,0x4d,0xc4,0xff,0xff,0xff,0x47,0xfa,0xba,0x5f,0xd5,
0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0x5f,0x75,0x55,0xfc,0xff,0xff,0x2f,0x75,0xd5,0xdf,0xd2,
0x00,0x00,0x00,0x00,0xfc,0xff,0xff,0xaf,0x45,0x95,0xfd,0xff,0xff,0x2f,0xea,0xbd,0x5f,0xa5,
0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0xaf,0xfa,0x6f,0xff,0xff,0xff,0x1f,0xf5,0xea,0xd7,0x6a,
0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xe8,0xde,0x55,0x55,
0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xb4,0xa9,0xea,0x62,
0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xe8,0xf5,0xe5,0x45,
0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xf4,0xfa,0x75,0x81,
0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xe8,0xd5,0x72,0xc1,
0x01,0x00,0x00,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xf4,0xb6,0x7d,0xc0,
0x01,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xc0,0xaa,0x79,0xc0,
0x01,0x00,0x00,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x78,0xeb,0xfa,0xe0,
0x01,0x00,0x00,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x40,0xa5,0xf2,0x81,
0x01,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x00,0x68,0x75,0x80,
0x01,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x40,0xe5,0x00,
0x01,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0x70,0x80,
0x01,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x60,0x00,
0x01,0x00,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0x30,0x80,
0x01,0x00,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x30,0x00,
0x01,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x30,0x80,
0x01,0x00,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x14,
0x01,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0x5f,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xab,0x52,0x49,0xf5,0xff,0xff,0xff,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xf0,0xff,0xff,0x7f,0xad,0xae,0xb6,0xaa,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xf0,0xff,0xff,0x7f,0x7b,0xa9,0xaa,0xaa,0xfa,0xff,0xff,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xf8,0xff,0xff,0xff,0xbf,0x57,0x55,0x55,0xfd,0xff,0xff,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xf8,0xff,0xff,0xff,0xff,0x5b,0x55,0x6d,0xeb,0xff,0xff,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xf8,0xff,0xff,0x5f,0xff,0x6f,0xb5,0xfb,0xff,0xff,0xff,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xf8,0xff,0xff,0x7f,0xff,0xff,0x6d,0xff,0xff,0xff,0xff,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xff,0xfe,0xff,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xf8,0xbf,0xff,0xbf,0xf7,0xff,0xff,0xff,0xff,0xab,0xff,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0x7f,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xb6,0xfe,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xfb,0xfa,0xd7,0xff,0xff,0xff,0xfb,0xff,0xaf,0xfd,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0x5f,0xf7,0xbb,0xfa,0xff,0xff,0xff,0xff,0x77,0xfb,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xfb,0xed,0xef,0xfb,0xff,0xff,0xff,0xff,0xff,0xf6,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xbf,0xf6,0xb7,0x7e,0xf5,0xff,0xff,0xff,0x7f,0xfb,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xfb,0xf6,0xff,0x7e,0xf7,0xfb,0xfa,0xff,0xfd,0xf7,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0x7b,0xdb,0xff,0xbf,0xfa,0xfa,0xd7,0xff,0xbf,0xfe,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0x77,0x5b,0xff,0xff,0xf7,0xea,0xb6,0xfa,0xbf,0xfd,0x0f,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xff,0xed,0xfa,0xbf,0x7a,0xf5,0xed,0x57,0x7f,0xfb,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xff,0xad,0xeb,0x7f,0x7b,0xd5,0x5b,0x75,0xbb,0xde,0x0f,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xef,0x77,0xfd,0xdf,0xbe,0xea,0x6d,0xaf,0xd6,0xfe,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xaf,0xdf,0xf5,0xbf,0x7f,0x95,0xdb,0xea,0xb5,0xee,0x0f,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0x57,0xbf,0xfe,0x6f,0x5f,0xd5,0xb7,0x5f,0x6b,0xff,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0xbf,0xfe,0xfd,0xdf,0xaf,0x2a,0x6f,0xd5,0xde,0xff,0x0f,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xab,0xfe,0xff,0xff,0xb7,0xea,0xde,0xbe,0xf5,0xff,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfc,0x57,0xf5,0xff,0xff,0xaf,0x95,0xfe,0x6a,0xfd,0xfd,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xab,0xea,0xff,0xff,0x55,0x55,0xff,0xff,0x7f,0xfd,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xaf,0xaa,0xff,0xff,0x5b,0xab,0xfc,0xff,0x7f,0xfd,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xab,0xaa,0xea,0x5f,0x6a,0x55,0xfb,0xff,0x57,0xfd,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xab,0xaa,0x5a,0xd5,0x56,0xad,0xaa,0xff,0x56,0xfd,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0x7f,0x55,0x55,0x55,0xad,0xb5,0xaa,0xaa,0xaa,0x55,0xfd,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xab,0xaa,0xaa,0xaa,0xd6,0xaa,0x56,0x55,0x55,0xfd,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0x55,0x55,0x55,0xb5,0xb5,0xaa,0xaa,0xaa,0xaa,0xfe,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0x55,0x55,0x55,0x55,0x55,0xad,0xaa,0xaa,0xaa,0xfa,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0x55,0x55,0x55,0xb5,0xad,0xb5,0xaa,0xaa,0xaa,0xfe,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0xdc,0x55,0x55,0x55,0x55,0x6b,0xd7,0xaa,0xaa,0xaa,0xfc,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xbd,0xab,0xaa,0xaa,0xaa,0xde,0x5a,0x55,0x55,0x55,0x7d,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x55,0xab,0xaa,0xaa,0xd6,0xfa,0xdb,0x57,0x55,0x55,0x7d,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0xba,0xab,0xaa,0xaa,0xaa,0xff,0xed,0x5b,0x55,0x95,0x06,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x6a,0x57,0x55,0x55,0x55,0xfd,0xad,0xab,0xaa,0xaa,0x0c,0x00,0x00,0x00,0x00,
0x00,0x00,0x40,0xbd,0xab,0xaa,0xaa,0xaa,0xde,0x77,0x57,0x55,0x55,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0xba,0x6a,0xaf,0xaa,0xaa,0xaa,0xb5,0x7e,0x55,0x55,0x55,0x0e,0x00,0x00,0x00,0x00,
0x00,0xc0,0xaf,0xf5,0x57,0x55,0x55,0x55,0xed,0xd5,0x56,0x55,0x95,0x02,0x00,0x00,0x00,0x00,
0x00,0xd0,0xaf,0xd6,0x5f,0x55,0x55,0x55,0x5b,0xbf,0x55,0x55,0x55,0x0d,0x00,0x00,0x00,0x00,
0x00,0xfc,0xdf,0xfd,0xab,0xaa,0x56,0xdb,0xb6,0x55,0xab,0xaa,0xaa,0x02,0x00,0x00,0x00,0x00,
0x00,0xfd,0x7f,0xab,0xbf,0x5a,0x55,0x55,0x6d,0x77,0xad,0xaa,0x4a,0x05,0x00,0x00,0x00,0x00,
0x80,0xff,0xff,0xfd,0xaf,0xaa,0x6a,0xdb,0xaa,0xaa,0x55,0x55,0x55,0x05,0x00,0x00,0x00,0x00,
0x80,0xff,0xff,0xfb,0xbf,0xaa,0xda,0xaa,0xda,0x5e,0xd5,0xaa,0xaa,0x02,0x00,0x00,0x00,0x00,
0xe0,0xff,0xff,0xff,0x5f,0x55,0xb5,0x5b,0x55,0x55,0x55,0x55,0x95,0x00,0x00,0x00,0x00,0x00,
0xe0,0xff,0xff,0xff,0x7f,0x55,0xb5,0xd6,0xb6,0x55,0x55,0xad,0x2a,0x00,0x00,0x00,0x00,0x00,
0xf0,0xff,0xff,0xff,0xbf,0x55,0xeb,0xff,0x7f,0xbb,0xaa,0xab,0x2a,0x00,0x00,0x00,0x00,0x00,
0xe0,0xff,0xff,0xff,0x7f,0x55,0xad,0xff,0xff,0xf7,0xad,0xaf,0x2a,0x00,0x00,0x00,0x00,0x00,
0xf8,0xff,0xff,0xff,0xff,0xaa,0xda,0xfe,0xff,0xff,0xff,0x5a,0xd5,0x01,0x00,0x00,0x00,0x00,
0xf8,0xff,0xff,0xff,0xff,0x6b,0x55,0xf5,0xff,0xff,0x5f,0xab,0xea,0x07,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0x56,0xdb,0xaa,0xf5,0xaf,0x6a,0x55,0xf5,0x07,0x00,0x00,0x00,0x00,
0xf8,0xff,0xff,0xff,0xff,0x55,0xb5,0x6d,0xaf,0xfa,0x57,0xad,0xea,0x1f,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xdb,0xaa,0xda,0xfa,0x57,0xd5,0xaa,0xfa,0x1f,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0x57,0xdb,0xb6,0x77,0xfd,0xaa,0xaa,0xea,0x3f,0x00,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xef,0x56,0x6d,0xdd,0xab,0xaa,0xaa,0xda,0x3f,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xaf,0x6d,0xab,0xfb,0x6e,0xab,0xaa,0xfa,0x7f,0x00,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0x7f,0xdb,0x76,0xff,0xb7,0x6a,0x55,0xfd,0x7f,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0x7f,0x5b,0x6d,0xab,0xef,0x56,0x55,0xf5,0x7f,0x00,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xbf,0xed,0xda,0x7e,0x55,0x55,0x55,0xff,0xff,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xff,0xad,0xb7,0xd5,0xbf,0x55,0x55,0xf5,0xff,0x00,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0x77,0x6d,0xbb,0x6a,0xab,0xea,0xfe,0xff,0x00,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xff,0x6f,0xdb,0xb6,0xad,0x5a,0xd5,0xf6,0xff,0x01,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xbf,0xad,0x6d,0x5b,0x55,0x75,0xfb,0xff,0x01,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x7b,0xdb,0x6a,0x55,0xf5,0xf6,0xff,0x03,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xd6,0xb6,0x5b,0xab,0xba,0xfd,0xff,0x03,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0x6d,0x6b,0x55,0xfb,0xf5,0xff,0x07,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x6f,0xdb,0xae,0x6a,0x7d,0xef,0xff,0x03,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xb7,0x6d,0xdb,0x7a,0xed,0xff,0x07,0x00,0x00,0x00,
0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xd6,0xaa,0xfe,0xfb,0xff,0x07,0x00,0x00,0x00,
0xf8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xbd,0x7e,0xfd,0xea,0xff,0x0f,0x00,0x00,0x00,
0xf8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xeb,0x55,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xd7,0xfe,0xea,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xad,0xfe,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xaa,0xfe,0xf6,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0xd5,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x55,0xff,0xff,0xff,0x1f,0x00,0x00,0x00,
0xfe,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0xd5,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xab,0xff,0xff,0xff,0x1f,0x00,0x00,0x00,
0xfe,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xaf,0xea,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xaa,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xaf,0xf5,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xd6,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xfd,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfc,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xeb,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xfd,0xff,0xff,0xff,0x07,0x00,0x00,0x00,
0xfc,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xf7,0xff,0xff,0xff,0x1f,0x00,0x00,0x00,
0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x2f,0x00,0x00,0x00,
0xf8,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x00,0x00,0x00,
0xea,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x6f,0x00,0x00,0x00,
0xd4,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0x00,0x00,0x00,
};

static const byte ARD[] PROGMEM =
{
0x00,0x00,0x00,0xc0,0xff,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0x0f,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xff,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x80,0xff,0xff,0xff,0x03,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x07,0x00,0x00,
0x00,0x00,0xf0,0xff,0xff,0xff,0x1f,0x00,0x00,0x00,0x00,0xe0,0xff,0xff,0xff,0x1f,0x00,0x2a,
0x00,0x00,0xfc,0xff,0xff,0xff,0x3f,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0xff,0x7f,0x00,0x3a,
0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0x01,0x3a,
0x00,0x80,0xff,0xff,0xff,0xff,0xff,0x03,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x03,0x00,
0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0x07,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0x0f,0x00,
0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0x1f,0x00,
0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0x3f,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0x3f,0x00,
0x00,0xfc,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0xf8,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,
0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x00,
0x00,0xfe,0xff,0x7f,0x00,0xfe,0xff,0xff,0x01,0x00,0xfe,0xff,0xff,0x00,0xf8,0xff,0xff,0x01,
0x00,0xff,0xff,0x07,0x00,0xe0,0xff,0xff,0x03,0x00,0xff,0xff,0x0f,0x00,0xc0,0xff,0xff,0x03,
0x80,0xff,0xff,0x01,0x00,0x00,0xff,0xff,0x07,0x80,0xff,0xff,0x03,0x00,0x00,0xff,0xff,0x07,
0xc0,0xff,0x7f,0x00,0x00,0x00,0xfc,0xff,0x0f,0xc0,0xff,0xff,0x00,0x00,0x00,0xfc,0xff,0x07,
0xc0,0xff,0x3f,0x00,0x00,0x00,0xf8,0xff,0x0f,0xe0,0xff,0x3f,0x00,0x00,0x00,0xf0,0xff,0x0f,
0xe0,0xff,0x1f,0x00,0x00,0x00,0xe0,0xff,0x1f,0xf0,0xff,0x1f,0x00,0x00,0x00,0xe0,0xff,0x0f,
0xe0,0xff,0x07,0x00,0x00,0x00,0xc0,0xff,0x3f,0xf0,0xff,0x0f,0x00,0x00,0x00,0xc0,0xff,0x1f,
0xf0,0xff,0x03,0x00,0x00,0x00,0x80,0xff,0x7f,0xf8,0xff,0x07,0x00,0x00,0x00,0x80,0xff,0x3f,
0xf0,0xff,0x03,0x00,0x00,0x00,0x00,0xff,0x7f,0xfc,0xff,0x03,0x00,0x00,0x00,0x00,0xff,0x3f,
0xf8,0xff,0x01,0x00,0x00,0x00,0x00,0xfe,0xff,0xfe,0xff,0x01,0x00,0x00,0x00,0x00,0xfe,0x3f,
0xf8,0xff,0x00,0x00,0x00,0x00,0x00,0xfc,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0xfe,0x7f,
0xfc,0x7f,0x00,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0x7f,0x00,0x00,0x7e,0x00,0x00,0xfc,0x7f,
0xfc,0x7f,0x00,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0x3f,0x00,0x00,0x7e,0x00,0x00,0xf8,0x7f,
0xfc,0x3f,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0x1f,0x00,0x00,0x7e,0x00,0x00,0xf8,0xff,
0xfc,0x3f,0x00,0x00,0x00,0x00,0x00,0xe0,0xff,0xff,0x1f,0x00,0x00,0x7e,0x00,0x00,0xf0,0xff,
0xfe,0x3f,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0xff,0x0f,0x00,0x00,0x7e,0x00,0x00,0xf0,0xff,
0xfe,0x1f,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0xff,0x07,0x00,0x00,0x7e,0x00,0x00,0xf0,0xff,
0xfe,0x1f,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0x07,0x00,0x00,0xff,0x00,0x00,0xf0,0xff,
0xff,0x1f,0x00,0xfe,0xff,0xff,0x00,0x00,0xff,0xff,0x03,0x00,0xfc,0xff,0x3f,0x00,0xe0,0xff,
0xff,0x1f,0x00,0xfe,0xff,0xff,0x01,0x00,0xff,0xff,0x01,0x00,0xfc,0xff,0x3f,0x00,0xe0,0xff,
0xff,0x1f,0x00,0xfe,0xff,0xff,0x01,0x00,0xfe,0xff,0x01,0x00,0xfc,0xff,0x3f,0x00,0xe0,0xff,
0xff,0x1f,0x00,0xfe,0xff,0xff,0x01,0x00,0xfc,0xff,0x00,0x00,0xfc,0xff,0x3f,0x00,0xe0,0xff,
0xff,0x1f,0x00,0xfe,0xff,0xff,0x01,0x00,0xfe,0xff,0x00,0x00,0xfc,0xff,0x3f,0x00,0xe0,0xff,
0xff,0x1f,0x00,0xfe,0xff,0xff,0x01,0x00,0xfe,0xff,0x01,0x00,0xfc,0xff,0x3f,0x00,0xe0,0xff,
0xff,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x03,0x00,0x00,0xff,0x00,0x00,0xe0,0xff,
0xff,0x1f,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0x03,0x00,0x00,0x7e,0x00,0x00,0xe0,0xff,
0xff,0x1f,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0x07,0x00,0x00,0x7e,0x00,0x00,0xf0,0xff,
0xff,0x1f,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0xff,0x0f,0x00,0x00,0x7e,0x00,0x00,0xf0,0xff,
0xfe,0x3f,0x00,0x00,0x00,0x00,0x00,0xe0,0xff,0xff,0x0f,0x00,0x00,0x7e,0x00,0x00,0xf0,0xff,
0xfc,0x3f,0x00,0x00,0x00,0x00,0x00,0xe0,0xff,0xff,0x1f,0x00,0x00,0x7e,0x00,0x00,0xf8,0xff,
0xfc,0x3f,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0x3f,0x00,0x00,0x7e,0x00,0x00,0xf8,0xff,
0xfc,0x7f,0x00,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,0x00,0xf8,0x7f,
0xfc,0xff,0x00,0x00,0x00,0x00,0x00,0xfc,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,0x00,0xfc,0x7f,
0xf8,0xff,0x00,0x00,0x00,0x00,0x00,0xfc,0xff,0xfe,0xff,0x00,0x00,0x00,0x00,0x00,0xfe,0x7f,
0xf8,0xff,0x01,0x00,0x00,0x00,0x00,0xfe,0xff,0xfc,0xff,0x01,0x00,0x00,0x00,0x00,0xfe,0x3f,
0xf0,0xff,0x03,0x00,0x00,0x00,0x00,0xff,0x7f,0xf8,0xff,0x03,0x00,0x00,0x00,0x00,0xff,0x3f,
0xf0,0xff,0x03,0x00,0x00,0x00,0x80,0xff,0x3f,0xf8,0xff,0x07,0x00,0x00,0x00,0x80,0xff,0x3f,
0xe0,0xff,0x07,0x00,0x00,0x00,0xc0,0xff,0x3f,0xf0,0xff,0x0f,0x00,0x00,0x00,0xc0,0xff,0x1f,
0xe0,0xff,0x1f,0x00,0x00,0x00,0xe0,0xff,0x1f,0xe0,0xff,0x1f,0x00,0x00,0x00,0xe0,0xff,0x0f,
0xc0,0xff,0x3f,0x00,0x00,0x00,0xf8,0xff,0x0f,0xc0,0xff,0x3f,0x00,0x00,0x00,0xf0,0xff,0x0f,
0xc0,0xff,0x7f,0x00,0x00,0x00,0xfc,0xff,0x07,0xc0,0xff,0x7f,0x00,0x00,0x00,0xfc,0xff,0x07,
0x80,0xff,0xff,0x01,0x00,0x00,0xff,0xff,0x07,0x80,0xff,0xff,0x01,0x00,0x00,0xff,0xff,0x07,
0x00,0xff,0xff,0x07,0x00,0xc0,0xff,0xff,0x03,0x00,0xff,0xff,0x07,0x00,0xc0,0xff,0xff,0x03,
0x00,0xfe,0xff,0x7f,0x00,0xf8,0xff,0xff,0x01,0x00,0xfe,0xff,0x7f,0x00,0xf8,0xff,0xff,0x01,
0x00,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x00,
0x00,0xf8,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0xf8,0xff,0xff,0xff,0xff,0xff,0x7f,0x00,
0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0x3f,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0x3f,0x00,
0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0x1f,0x00,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0x1f,0x00,
0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0x07,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0x0f,0x00,
0x00,0x80,0xff,0xff,0xff,0xff,0xff,0x03,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x03,0x00,
0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0x01,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0x01,0x00,
0x00,0x00,0xfc,0xff,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0xff,0x7f,0x00,0x00,
0x00,0x00,0xf0,0xff,0xff,0xff,0x1f,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0x1f,0x00,0x00,
0x00,0x00,0x80,0xff,0xff,0xff,0x07,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0xff,0x07,0x00,0x00,
0x00,0x00,0x00,0xfe,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xc0,0xff,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0x0f,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xfe,0x00,0xfe,0x0f,0xe0,0xff,0x00,0x3e,0xc0,0x87,0xff,0x3f,0xfc,0x80,0x0f,0xf8,0x0f,
0x00,0xfe,0x01,0xfe,0x3f,0xe0,0xff,0x03,0x3e,0xc0,0x87,0xff,0x3f,0xfc,0x81,0x0f,0xfc,0x1f,
0x00,0xfe,0x01,0xfe,0xff,0xe0,0xff,0x0f,0x3e,0xc0,0x87,0xff,0x3f,0xfc,0x81,0x0f,0xfe,0x3f,
0x00,0xff,0x01,0xfe,0xff,0xe0,0xff,0x1f,0x3e,0xc0,0x87,0xff,0x3f,0xfc,0x83,0x0f,0xff,0x7f,
0x00,0xff,0x01,0x3e,0xfe,0xe1,0xe3,0x3f,0x3e,0xc0,0x07,0xf0,0x01,0xfc,0x83,0x8f,0x3f,0xfe,
0x00,0xff,0x03,0x3e,0xf8,0xe1,0x03,0x3f,0x3e,0xc0,0x07,0xf0,0x01,0xfc,0x87,0x8f,0x0f,0xfc,
0x80,0xef,0x03,0x3e,0xf0,0xe1,0x03,0x3e,0x3e,0xc0,0x07,0xf0,0x01,0xfc,0x87,0xcf,0x0f,0xf8,
0x80,0xef,0x03,0x3e,0xf0,0xe1,0x03,0x7e,0x3e,0xc0,0x07,0xf0,0x01,0xfc,0x8f,0xcf,0x07,0xf8,
0x81,0xef,0x07,0x3e,0xf8,0xe1,0x03,0x7e,0x3e,0xc0,0x07,0xf0,0x01,0xfc,0x8f,0xcf,0x07,0xf8,
0xc1,0xc7,0x07,0x3e,0xfc,0xe1,0x03,0x7c,0x3e,0xc0,0x07,0xf0,0x01,0xfc,0x8f,0xcf,0x07,0xf0,
0xc1,0xc7,0x07,0xfe,0xff,0xe0,0x03,0x7c,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0x9f,0xcf,0x07,0xf0,
0xc1,0xc7,0x0f,0xfe,0x7f,0xe0,0x03,0x7c,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0x9f,0xef,0x07,0xf0,
0xc1,0x87,0x0f,0xfe,0x1f,0xe0,0x03,0x7c,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0xbe,0xef,0x07,0xf0,
0xe1,0x83,0x0f,0xfe,0x3f,0xe0,0x03,0x7c,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0xbe,0xcf,0x07,0xf0,
0xe1,0x83,0x1f,0x3e,0x3f,0xe0,0x03,0x7e,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0xfc,0xcf,0x07,0xf0,
0xe1,0xff,0x1f,0x3e,0x7e,0xe0,0x03,0x7e,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0xfc,0xcf,0x07,0xf8,
0xf1,0xff,0x1f,0x3e,0x7c,0xe0,0x03,0x3e,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0xf8,0xcf,0x07,0xf8,
0xf1,0xff,0x1f,0x3e,0xfc,0xe0,0x03,0x3f,0x3e,0xc0,0x07,0xf0,0x01,0x7c,0xf8,0xcf,0x0f,0xf8,
0xf0,0xff,0x3f,0x3e,0xf8,0xe0,0x83,0x3f,0x7e,0xe0,0x03,0xf0,0x01,0x7c,0xf0,0x8f,0x1f,0xfc,
0xf8,0x00,0x3e,0x3e,0xf8,0xe1,0xff,0x1f,0xfc,0xf0,0x83,0xff,0x3f,0x7c,0xf0,0x8f,0xff,0x7f,
0xf8,0x00,0x3e,0x3e,0xf0,0xe1,0xff,0x0f,0xfc,0xff,0x81,0xff,0x3f,0x7c,0xf0,0x0f,0xff,0x7f,
0xf8,0x00,0x7e,0x3e,0xf0,0xe3,0xff,0x07,0xf8,0xff,0x81,0xff,0x3f,0x7c,0xe0,0x0f,0xfe,0x3f,
0xf8,0x00,0x7e,0x3e,0xe0,0xe3,0xff,0x01,0xf0,0x7f,0x80,0xff,0x3f,0x7c,0xe0,0x0f,0xfc,0x0f,
0x78,0x00,0x7c,0x3e,0xe0,0xe3,0x1f,0x00,0xc0,0x1f,0x80,0xff,0x3f,0x3c,0xc0,0x07,0xf0,0x03
};

void setup(){
  m190::initialize();

  //Don't print until button is pressed
  pinMode(3,INPUT);
  while(digitalRead(3)==LOW){
  }

  m190::formfeed(30);
  m190::print(F("       Epson M-190"));
  m190::print(F("    Printer Driver Demo"));
  m190::print(F("        Powered by"));
  m190::printP(ARD,18,98);
  m190::print(F("        Written by"));
  m190::print(F("      Steven Pearson"));
  m190::printP(ME,18,144);
  m190::formfeed(20);
  m190::print(F("  Thanks for Watching"));
  m190::formfeed(20);
}

void loop(){
}