#ifndef EMUTOOL_H
#define EMUTOOL_H

#include "types.h"
typedef struct CPU CPU;

void pipeline_info(CPU* cpu);
int get_circular_index(const uint_32, const uint_32);
void raminfo(uint_8*, uint_32);
void cpuinfo(CPU*);

#endif