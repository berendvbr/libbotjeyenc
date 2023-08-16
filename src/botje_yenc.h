#ifndef BOTJE_YENC_H
#define BOTJE_YENC_H

#include <stdbool.h>
#include <stdlib.h>

int64_t botje_yenc__decode(unsigned char *, unsigned char *, int64_t);
int64_t botje_yenc__encode(unsigned char *, unsigned char *, int64_t);

#endif
