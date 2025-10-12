#ifndef EMUTOOL_H
#define EMUTOOL_H

#include "types.h"
typedef struct CPU CPU;

//show pipeline status into console
void pipeline_info(CPU* cpu);

//useless func
int get_circular_index(const uint_32 index, const uint_32 len);

//show RAM status into console
void raminfo(uint_8 *ram, uint_32 len);

//show CPU status into console
void cpuinfo(CPU* cpu);

//copy bytes into RAM
void memorycopy(uint_8 *destination, const uint_8 *source, const int len, const int disp);

#endif