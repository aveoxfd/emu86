#ifndef EMUTOOL_H
#define EMUTOOL_H

#include "types.h"
typedef struct CPU CPU;

void pipeline_info(CPU* cpu);
int get_circular_index(const uint_32 index, const uint_32 len);
void raminfo(uint_8 *ram, uint_32 len);
void cpuinfo(CPU* cpu);
void memorycopy(uint_8 *destination, const uint_8 *source, const int len);

#endif