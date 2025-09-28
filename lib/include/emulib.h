#ifndef EMULIB_H
#define EMULIB_H

#include "emutool.h"

#define PREFETCH_QUEUE_SIZE_MACRO 6
typedef enum{
    MICRO_LOAD_REG_IMM16,
    MICRO_FETCH_MODRM,
    MICRO_LOAD_REG_RM,
    MICRO_LOAD_RM_REG,
    MICRO_LOAD_SEGREG_RM,
    MICRO_LOAD_RM_SEGREG,
    MICRO_LOAD_REG_IMM8,
    MICRO_LOAD_REG8_RM8,
    MICRO_LOAD_RM8_REG8,
    MICRO_LOAD_MEM_REG,
    MICRO_LOAD_MEM_AX,
    MICRO_END
}Uop_instruct;

typedef enum{
    CS,
    DS,
    ES,
    SS,
    SR_COUNT
}Segment_registers;
typedef enum{
    AX, 
    CX, 
    DX, 
    BX, 
    SP, 
    BP, 
    SI, 
    DI,
    GPR_COUNT
}General_purpose_registers;
typedef enum{
    IP,
    FLAGS,
    S_COUNT,
}System_registers;

typedef struct CPU{
    uint_16 general_purpose_registers[GPR_COUNT];   //ax, cx, dx, bx, sp, bp, si, di
    uint_16 segments_registers[SR_COUNT];           //cs, ds, es, ss
    uint_16 system_registers[S_COUNT];              //ip, flags

    uint_8  prefetch_queue[PREFETCH_QUEUE_SIZE_MACRO];  // FF FF FF FF FF FF FF FF
    uint_16 prefetch_head;                              // 
    uint_16 prefetch_count;                             //

    uint_8  opcode;                                 //opcode shadow register
    uint_8  modrm;                                  //modr/m shadow register
    uint_16 disp;                                   //displacement
    uint_16 base;                                   //base
    uint_8  reset;                                  //on start value
}CPU;

#endif