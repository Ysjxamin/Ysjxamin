#ifndef _encoder_h
#define _encoder_h

#include "headfile.h"

extern int16 encoder1;
extern int16 encoder2;
extern int16 encoder3;
extern int16 encoder4;

void encoder_init(void);
void encoder_get(void);

#endif
