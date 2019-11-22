#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern unsigned char verboseMode;

#define DBG(msg) if (verboseMode) puts(msg);
#define DBGf(fmt, ...) if (verboseMode) printf(fmt, __VA_ARGS__);

#endif /* _COMMON_H_ */
