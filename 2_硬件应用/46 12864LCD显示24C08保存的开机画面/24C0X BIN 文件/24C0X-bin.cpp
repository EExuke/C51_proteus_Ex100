#include <stdio.h>
unsigned char bitmap[] = //128*40 车内图片(用Zimo取模)
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x09,0xA9,0x79,0xBB,0x79,
  0x31,0x09,0x81,0xC1,0xF2,0xFB,0xFA,0xFA,0xFA,0xF8,0xF8,0xEA,0xE8,0xF4,0xFC,0xFD,
  0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
  0xFE,0xFE,0xFE,0xFE,0xFE,0xFD,0xFD,0xFD,0xF9,0xFB,0xFA,0xFA,0xFE,0xFC,0xFC,0xFC,
  0x0C,0x0C,0x1C,0x3C,0xF4,0xBC,0xF4,0xF4,0xF4,0xF4,0xD4,0x14,0x14,0x14,0x14,0x14,
  0x14,0x10,0x10,0x10,0x10,0x14,0x10,0x10,0x14,0x10,0x10,0x90,0xF8,0xFA,0xFF,0x03,
  0x07,0x07,0x07,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x0B,0x03,0x03,0x03,
  0x03,0x03,0x03,0x07,0x07,0x07,0xFE,0xFF,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x7E,0x3E,0x8E,0xF6,0xF3,0xFD,0xFD,0xFE,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,
  0xDF,0xEF,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,
  0xFF,0xFF,0xEF,0xFF,0xFF,0xEF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xBF,0xDF,0x3E,0xFE,0xFC,0xB9,0xD3,0xE3,0xC3,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFE,
  0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xF7,0xF7,0x07,0x07,0x77,0x77,0x77,0x77,0x37,0x74,
  0x70,0x30,0x70,0x70,0x70,0x70,0x70,0x00,0x40,0x70,0x34,0x74,0x64,0x00,0x10,0x30,
  0x70,0x74,0x74,0x74,0x74,0x70,0x7F,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xFC,0xFF,0x8F,0xCF,0xCC,0xCD,0xCC,0xEC,
  0xD4,0xC9,0xCD,0xCF,0xC7,0xC5,0xC3,0x82,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
  0x00,0x01,0x07,0x01,0x0F,0x0B,0x25,0x03,0xE1,0xF1,0xE9,0xF7,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xCF,0xD7,0xFF,0xFF,0xFF,0xFF,0xFF,0x6F,0x6F,0x00,0x00,0xFF,0xFF,0xFF,0xEF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,
  0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00,0x00,0x7E,0x7E,0x3E,0x3E,
  0x3E,0x3E,0x5E,0x3E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x47,0x3F,0x3F,0xFF,0xDF,0xFB,0x1B,0x3F,
  0x1F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7C,0x78,0x38,0xE0,0x60,0xC0,
  0xC0,0xC0,0x00,0x00,0x00,0x00,0x40,0x50,0xCF,0xBF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0xDD,0xD0,0xC0,0xE0,0xF0,0xFF,0xFF,0xE7,0xE7,0xC7,
  0xC7,0xCF,0x0F,0x0F,0x0F,0x0F,0x3F,0xE0,0x00,0x00,0xFC,0xFC,0xFC,0xFC,0xFC,0xDC,
  0xFC,0xDC,0xBC,0xBC,0x9C,0xFC,0x3C,0x9C,0x1C,0x9C,0x98,0x98,0xF8,0x98,0x98,0x98,
  0x18,0x18,0x98,0xF8,0xD0,0xF0,0xF0,0xF0,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFC,0xFC,0xFF,0xFC,0xFC,0xBB,0xEB,0x8F,0x9E,
  0xBC,0xFC,0xFC,0xF8,0xFC,0x6C,0xFC,0xFC,0xF8,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0x6F,0x00,0x00,0xC0,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xBF,0x9F,
  0xFB,0xFF,0xFD,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xF0,0x80,0x00,0x00,0x83,0x00,0x00,0xFF,0xFF,0xFE,0xFE,0xFE,0xF7,
  0xF3,0xF3,0xF3,0xF3,0xF3,0xF2,0xF3,0xF2,0xF2,0xF2,0xF2,0xF2,0xF2,0xF2,0xF2,0xF2,
  0xF2,0xF2,0xFB,0xAF,0xFF,0xFF,0xFF,0xEB,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void main()
{
  FILE *fp;

  fp = fopen("c:\\24C0X.bin","wb");

  fwrite(bitmap,1,128*64,fp);

  fclose(fp);
}