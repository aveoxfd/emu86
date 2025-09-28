#ifndef EMUTOOL_H
#define EMUTOOL_H

#include "types.h"
typedef struct CPU CPU;

void raminfo(uint_8*, uint_32);
void cpuinfo(CPU*);
#endif