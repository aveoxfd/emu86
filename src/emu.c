#include <stdio.h>
#include "..\lib\include\emulib.h"
#define DEBUG 0
//modr/m: 11dddsss (d - destination; s - source)

uint_8 RAM[1024*1024];

static const Uop_instruct *MICROCODE_ROM[]={
    [0x00] = (Uop_instruct[]){

    },
    [0x01] = (Uop_instruct[]){

    },
    [0x02] = (Uop_instruct[]){

    },
    [0x03] = (Uop_instruct[]){

    },
    [0x04] = (Uop_instruct[]){
        MICRO_ADD_AL_IMM8,
        MICRO_END
    },//add al, ib (ib - immediate byte) or imm8
    [0x05] = (Uop_instruct[]){

    },
    [0x06] = (Uop_instruct[]){

    },
    [0x07] = (Uop_instruct[]){

    },
    [0x08] = (Uop_instruct[]){

    },
    [0x09] = (Uop_instruct[]){

    },
    [0x0A] = (Uop_instruct[]){

    },
    [0x0B] = (Uop_instruct[]){

    },
    [0x0C] = (Uop_instruct[]){

    },
    [0x0D] = (Uop_instruct[]){

    },
    [0x0E] = (Uop_instruct[]){

    },
    [0x0F] = (Uop_instruct[]){

    },
    [0x10] = (Uop_instruct[]){

    },
    [0x11] = (Uop_instruct[]){

    },
    [0x12] = (Uop_instruct[]){

    },
    [0x13] = (Uop_instruct[]){

    },
    [0x14] = (Uop_instruct[]){

    },
    [0x15] = (Uop_instruct[]){

    },
    [0x16] = (Uop_instruct[]){

    },
    [0x17] = (Uop_instruct[]){

    },
    [0x18] = (Uop_instruct[]){

    },
    [0x19] = (Uop_instruct[]){

    },
    [0x1A] = (Uop_instruct[]){

    },
    [0x1B] = (Uop_instruct[]){

    },
    [0x1C] = (Uop_instruct[]){

    },
    [0x1D] = (Uop_instruct[]){

    },
    [0x1E] = (Uop_instruct[]){

    },
    [0x1F] = (Uop_instruct[]){

    },
    [0x20] = (Uop_instruct[]){

    },
    [0x21] = (Uop_instruct[]){

    },
    [0x22] = (Uop_instruct[]){

    },
    [0x23] = (Uop_instruct[]){

    },
    [0x24] = (Uop_instruct[]){

    },
    [0x25] = (Uop_instruct[]){

    },
    [0x26] = (Uop_instruct[]){

    },
    [0x27] = (Uop_instruct[]){

    },
    [0x28] = (Uop_instruct[]){

    },
    [0x29] = (Uop_instruct[]){

    },
    [0x2A] = (Uop_instruct[]){

    },
    [0x2B] = (Uop_instruct[]){

    },
    [0x2C] = (Uop_instruct[]){

    },
    [0x2D] = (Uop_instruct[]){

    },
    [0x2E] = (Uop_instruct[]){

    },
    [0x2F] = (Uop_instruct[]){

    },
    [0x30] = (Uop_instruct[]){

    },
    [0x31] = (Uop_instruct[]){

    },
    [0x32] = (Uop_instruct[]){

    },
    [0x33] = (Uop_instruct[]){

    },
    [0x34] = (Uop_instruct[]){

    },
    [0x35] = (Uop_instruct[]){

    },
    [0x36] = (Uop_instruct[]){

    },
    [0x37] = (Uop_instruct[]){

    },
    [0x38] = (Uop_instruct[]){

    },
    [0x39] = (Uop_instruct[]){

    },
    [0x3A] = (Uop_instruct[]){

    },
    [0x3B] = (Uop_instruct[]){

    },
    [0x3C] = (Uop_instruct[]){

    },
    [0x3D] = (Uop_instruct[]){

    },
    [0x3E] = (Uop_instruct[]){

    },
    [0x3F] = (Uop_instruct[]){

    },
    [0x40] = (Uop_instruct[]){

    },
    [0x41] = (Uop_instruct[]){

    },
    [0x42] = (Uop_instruct[]){

    },
    [0x43] = (Uop_instruct[]){

    },
    [0x44] = (Uop_instruct[]){

    },
    [0x45] = (Uop_instruct[]){

    },
    [0x46] = (Uop_instruct[]){

    },
    [0x47] = (Uop_instruct[]){

    },
    [0x48] = (Uop_instruct[]){

    },
    [0x49] = (Uop_instruct[]){

    },
    [0x4A] = (Uop_instruct[]){

    },
    [0x4B] = (Uop_instruct[]){

    },
    [0x4C] = (Uop_instruct[]){

    },
    [0x4D] = (Uop_instruct[]){

    },
    [0x4E] = (Uop_instruct[]){

    },
    [0x4F] = (Uop_instruct[]){

    },
    [0x50] = (Uop_instruct[]){

    },
    [0x51] = (Uop_instruct[]){

    },
    [0x52] = (Uop_instruct[]){

    },
    [0x53] = (Uop_instruct[]){

    },
    [0x54] = (Uop_instruct[]){

    },
    [0x55] = (Uop_instruct[]){

    },
    [0x56] = (Uop_instruct[]){

    },
    [0x57] = (Uop_instruct[]){

    },
    [0x58] = (Uop_instruct[]){

    },
    [0x59] = (Uop_instruct[]){

    },
    [0x5A] = (Uop_instruct[]){

    },
    [0x5B] = (Uop_instruct[]){

    },
    [0x5C] = (Uop_instruct[]){

    },
    [0x5D] = (Uop_instruct[]){

    },
    [0x5E] = (Uop_instruct[]){

    },
    [0x5F] = (Uop_instruct[]){

    },
    [0x60] = (Uop_instruct[]){

    },
    [0x61] = (Uop_instruct[]){

    },
    [0x62] = (Uop_instruct[]){

    },
    [0x63] = (Uop_instruct[]){

    },
    [0x64] = (Uop_instruct[]){

    },
    [0x65] = (Uop_instruct[]){

    },
    [0x66] = (Uop_instruct[]){

    },
    [0x67] = (Uop_instruct[]){

    },
    [0x68] = (Uop_instruct[]){

    },
    [0x69] = (Uop_instruct[]){

    },
    [0x6A] = (Uop_instruct[]){

    },
    [0x6B] = (Uop_instruct[]){

    },
    [0x6C] = (Uop_instruct[]){

    },
    [0x6D] = (Uop_instruct[]){

    },
    [0x6E] = (Uop_instruct[]){

    },
    [0x6F] = (Uop_instruct[]){

    },
    [0x70] = (Uop_instruct[]){

    },
    [0x71] = (Uop_instruct[]){

    },
    [0x72] = (Uop_instruct[]){

    },
    [0x73] = (Uop_instruct[]){

    },
    [0x74] = (Uop_instruct[]){

    },
    [0x75] = (Uop_instruct[]){

    },
    [0x76] = (Uop_instruct[]){

    },
    [0x77] = (Uop_instruct[]){

    },
    [0x78] = (Uop_instruct[]){

    },
    [0x79] = (Uop_instruct[]){

    },
    [0x7A] = (Uop_instruct[]){

    },
    [0x7B] = (Uop_instruct[]){

    },
    [0x7C] = (Uop_instruct[]){

    },
    [0x7D] = (Uop_instruct[]){

    },
    [0x7E] = (Uop_instruct[]){

    },
    [0x7F] = (Uop_instruct[]){

    },
    [0x80] = (Uop_instruct[]){

    },
    [0x81] = (Uop_instruct[]){

    },
    [0x82] = (Uop_instruct[]){

    },
    [0x83] = (Uop_instruct[]){

    },
    [0x84] = (Uop_instruct[]){

    },
    [0x85] = (Uop_instruct[]){

    },
    [0x86] = (Uop_instruct[]){

    },
    [0x87] = (Uop_instruct[]){

    },
    [0x88] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_RM8_REG8,
        MICRO_END
    },//mov r/m8, r8
    [0x89] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_RM_REG,
        MICRO_END
    },//mov r/m16, r16
    [0x8A] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_REG8_RM8,
        MICRO_END
    },//mov r8, r/m8
    [0x8B] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_REG_RM,
        MICRO_END
    },//mov r16, r/m16
    [0x8C] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_RM_SEGREG,
        MICRO_END
    },//mov r/m16, segreg16
    [0x8D] = (Uop_instruct[]){

    },
    [0x8E] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_SEGREG_RM,
        MICRO_END
    },//mov segreg, r/m16
    [0x8F] = (Uop_instruct[]){

    },
    [0x90] = (Uop_instruct[]){
        MICRO_END
    },//nop
    [0x91] = (Uop_instruct[]){

    },
    [0x92] = (Uop_instruct[]){

    },
    [0x93] = (Uop_instruct[]){

    },
    [0x94] = (Uop_instruct[]){

    },
    [0x95] = (Uop_instruct[]){

    },
    [0x96] = (Uop_instruct[]){

    },
    [0x97] = (Uop_instruct[]){

    },
    [0x98] = (Uop_instruct[]){

    },
    [0x99] = (Uop_instruct[]){

    },
    [0x9A] = (Uop_instruct[]){

    },
    [0x9B] = (Uop_instruct[]){

    },
    [0x9C] = (Uop_instruct[]){

    },
    [0x9D] = (Uop_instruct[]){

    },
    [0x9E] = (Uop_instruct[]){

    },
    [0x9F] = (Uop_instruct[]){

    },
    [0xA0] = (Uop_instruct[]){

    },
    [0xA1] = (Uop_instruct[]){

    },
    [0xA2] = (Uop_instruct[]){

    },
    [0xA3] = (Uop_instruct[]){
        MICRO_LOAD_MEM_AX,
        MICRO_END
    },//mov mem, ax
    [0xA4] = (Uop_instruct[]){

    },
    [0xA5] = (Uop_instruct[]){

    },
    [0xA6] = (Uop_instruct[]){

    },
    [0xA7] = (Uop_instruct[]){

    },
    [0xA8] = (Uop_instruct[]){

    },
    [0xA9] = (Uop_instruct[]){

    },
    [0xAA] = (Uop_instruct[]){

    },
    [0xAB] = (Uop_instruct[]){

    },
    [0xAC] = (Uop_instruct[]){

    },
    [0xAD] = (Uop_instruct[]){

    },
    [0xAE] = (Uop_instruct[]){

    },
    [0xAF] = (Uop_instruct[]){

    },
    [0xB0] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov al, imm8
    [0xB1] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov cl, imm8
    [0xB2] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov dl, imm8
    [0xB3] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov bl, imm8
    [0xB4] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov ah, imm8
    [0xB5] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov ch, imm8
    [0xB6] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov dh, imm8
    [0xB7] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM8,
        MICRO_END
    },//mov bh, imm8
    [0xB8] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov ax, imm16
    [0xB9] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov cx, imm16
    [0xBA] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov dx, imm16
    [0xBB] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov bx, imm16
    [0xBC] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov sp, imm16
    [0xBD] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov bp, imm16
    [0xBE] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov si, imm16
    [0xBF] = (Uop_instruct[]){
        MICRO_LOAD_REG_IMM16,
        MICRO_END
    },//mov di, imm16
    [0xC0] = (Uop_instruct[]){

    },
    [0xC1] = (Uop_instruct[]){

    },
    [0xC2] = (Uop_instruct[]){

    },
    [0xC3] = (Uop_instruct[]){

    },
    [0xC4] = (Uop_instruct[]){

    },
    [0xC5] = (Uop_instruct[]){

    },
    [0xC6] = (Uop_instruct[]){

    },
    [0xC7] = (Uop_instruct[]){

    },
    [0xC8] = (Uop_instruct[]){

    },
    [0xC9] = (Uop_instruct[]){

    },
    [0xCA] = (Uop_instruct[]){

    },
    [0xCB] = (Uop_instruct[]){

    },
    [0xCC] = (Uop_instruct[]){

    },
    [0xCD] = (Uop_instruct[]){

    },
    [0xCE] = (Uop_instruct[]){

    },
    [0xCF] = (Uop_instruct[]){

    },
    [0xD0] = (Uop_instruct[]){

    },
    [0xD1] = (Uop_instruct[]){

    },
    [0xD2] = (Uop_instruct[]){

    },
    [0xD3] = (Uop_instruct[]){

    },
    [0xD4] = (Uop_instruct[]){

    },
    [0xD5] = (Uop_instruct[]){

    },
    [0xD6] = (Uop_instruct[]){

    },
    [0xD7] = (Uop_instruct[]){

    },
    [0xD8] = (Uop_instruct[]){

    },
    [0xD9] = (Uop_instruct[]){

    },
    [0xDA] = (Uop_instruct[]){

    },
    [0xDB] = (Uop_instruct[]){

    },
    [0xDC] = (Uop_instruct[]){

    },
    [0xDD] = (Uop_instruct[]){

    },
    [0xDE] = (Uop_instruct[]){

    },
    [0xDF] = (Uop_instruct[]){

    },
    [0xE0] = (Uop_instruct[]){

    },
    [0xE1] = (Uop_instruct[]){

    },
    [0xE2] = (Uop_instruct[]){

    },
    [0xE3] = (Uop_instruct[]){

    },
    [0xE4] = (Uop_instruct[]){

    },
    [0xE5] = (Uop_instruct[]){

    },
    [0xE6] = (Uop_instruct[]){

    },
    [0xE7] = (Uop_instruct[]){

    },
    [0xE8] = (Uop_instruct[]){

    },
    [0xE9] = (Uop_instruct[]){

    },
    [0xEA] = (Uop_instruct[]){

    },
    [0xEB] = (Uop_instruct[]){

    },
    [0xEC] = (Uop_instruct[]){

    },
    [0xED] = (Uop_instruct[]){

    },
    [0xEE] = (Uop_instruct[]){

    },
    [0xEF] = (Uop_instruct[]){

    },
    [0xF0] = (Uop_instruct[]){

    },
    [0xF1] = (Uop_instruct[]){

    },
    [0xF2] = (Uop_instruct[]){

    },
    [0xF3] = (Uop_instruct[]){

    },
    [0xF4] = (Uop_instruct[]){
        MICRO_HLT,
        MICRO_END
    },//halt
    [0xF5] = (Uop_instruct[]){

    },
    [0xF6] = (Uop_instruct[]){

    },
    [0xF7] = (Uop_instruct[]){

    },
    [0xF8] = (Uop_instruct[]){

    },
    [0xF9] = (Uop_instruct[]){

    },
    [0xFA] = (Uop_instruct[]){

    },
    [0xFB] = (Uop_instruct[]){

    },
    [0xFC] = (Uop_instruct[]){

    },
    [0xFD] = (Uop_instruct[]){

    },
    [0xFE] = (Uop_instruct[]){

    },
    [0xFF] = (Uop_instruct[]){

    },
};

void memorycopy(uint_8 *destination, const uint_8 *source, const int len){
    for (int i = 0; i<len; i++){
        destination[i] = source[i];
    }
    return;
}

uint_32 get_phys_address(const uint_16 segment, const uint_16 offset){
    return (uint_32)((segment<<4)|offset);
}

uint_8 fetch_byte(const uint_16 segment, const uint_16 offset){
    return RAM[get_phys_address(segment, offset)];
}

uint_16 fetch_word(const uint_16 segment, const uint_16 offset){
    uint_8 low = RAM[get_phys_address(segment, offset)];
    uint_8 high = RAM[get_phys_address(segment, offset)+1];
    return (uint_16)((high<<8) | low); 
}
//====================================================================
//pipeline

void init_prefetch_queue(CPU *cpu){
    cpu->prefetch_head  = 0x0000;
    cpu->prefetch_count = 0x0000;

    //fill queue
    while(cpu->prefetch_count<PREFETCH_QUEUE_SIZE_MACRO){
        cpu->prefetch_queue[get_circular_index(cpu->prefetch_head + cpu->prefetch_count, PREFETCH_QUEUE_SIZE_MACRO)] 
        = 
        RAM[get_phys_address(cpu->segments_registers[CS], cpu->system_registers[IP] + cpu->prefetch_count)];
        cpu->prefetch_count++;
    }
    return;
}

uint_8 fetch_prefetch_byte(CPU *cpu){
    if(cpu->prefetch_count == 0){
        init_prefetch_queue(cpu);
    }
    uint_8 byte = cpu->prefetch_queue[cpu->prefetch_head];
    cpu->prefetch_head = (cpu->prefetch_head + 1) % PREFETCH_QUEUE_SIZE_MACRO;

    cpu->prefetch_count--;
    cpu->system_registers[IP]++;

    if(cpu->prefetch_count<PREFETCH_QUEUE_SIZE_MACRO){
        cpu->prefetch_queue[get_circular_index(cpu->prefetch_head + cpu->prefetch_count, PREFETCH_QUEUE_SIZE_MACRO)] 
        = RAM[get_phys_address(cpu->segments_registers[CS], cpu->system_registers[IP] + cpu->prefetch_count)];
        cpu->prefetch_count++;
    }
    return byte;
}
uint_16 fetch_prefetch_word(CPU *cpu) {
    uint_8 lo = fetch_prefetch_byte(cpu);
    uint_8 hi = fetch_prefetch_byte(cpu);
    return (uint_16)(lo | (hi << 8));
}
//====================================================================

void execute_uop(CPU *cpu, Uop_instruct uop){
    switch(uop){
        case MICRO_UNSUPPORTED:
        printf("Unsupported opcode 0x%02x.\n", cpu->opcode);
        cpu->reset = 0x01;
        break;

        case MICRO_END:
        break;

        case MICRO_HLT:
        cpu->reset = 0x01;
        break;

        case MICRO_ADD_AL_IMM8:
        cpu->general_purpose_registers[AX] = cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0xFF00) | 
                                     ((cpu->general_purpose_registers[AX] & 0x00FF) + (uint_8)fetch_prefetch_byte(cpu));
        //TODO: update flags
        break;

        case MICRO_LOAD_MEM_AX:
        uint_32 phys_address = get_phys_address(cpu->segments_registers[DS], fetch_prefetch_word(cpu));
        RAM[phys_address] = cpu->general_purpose_registers[AX] & 0xFF;
        RAM[phys_address + 1] = (cpu->general_purpose_registers[AX]>>8) & 0xFF;
        break;

        case MICRO_FETCH_MODRM:
        cpu->modrm = fetch_prefetch_byte(cpu);
        break;

        case MICRO_LOAD_REG_IMM16:
        cpu->general_purpose_registers[cpu->opcode & 0b00000111] = (uint_16)fetch_prefetch_word(cpu);
        break;

        case MICRO_LOAD_REG_RM:
        if((cpu->modrm & 0b11000000) != 0b11000000){ //reg <- memory
            cpu->disp = 0x0000;
            if ((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000110) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
                printf("cpu disp = %d", cpu->disp);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0b000: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 0b001: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 0b010: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 0b011: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 0b100: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 0b101: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 0b110: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 0b111: cpu->base = cpu->general_purpose_registers[BX];   
            }
            cpu->general_purpose_registers[((cpu->modrm & 0b00111000) >> 3)] = fetch_word(cpu->segments_registers[DS], cpu->base + cpu->disp);
        }
        else { //reg <- reg
            cpu->general_purpose_registers[((cpu->modrm & 0b00111000) >> 3)] = cpu->general_purpose_registers[((cpu->modrm & 0b00000111))];
        }
        break;

        case MICRO_LOAD_RM_REG:
        if((cpu->modrm & 0b11000000) != 0b11000000){ //memory <- reg
            cpu->disp = 0x0000;
            if((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000111) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0b000: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 0b001: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 0b010: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 0b011: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 0b100: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 0b101: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 0b110: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 0b111: cpu->base = cpu->general_purpose_registers[BX];   
            }

            uint_32 phys_address = get_phys_address(cpu->segments_registers[DS], cpu->base+cpu->disp);
            RAM[phys_address] = cpu->general_purpose_registers[(cpu->modrm & 0b00111000)>>3] & 0xFF;
            RAM[phys_address+1] = (cpu->general_purpose_registers[(cpu->modrm & 0b00111000)>>3] >> 8) & 0xFF;
        }
        else { //reg <- reg
            cpu->general_purpose_registers[(cpu->modrm & 0b00000111)] = cpu->general_purpose_registers[(cpu->modrm & 0b00111000)>>3];
        }
        break;

        case MICRO_LOAD_SEGREG_RM:
        if((cpu->modrm & 0b11000000) != 0b11000000){ // segreg <- memory
            cpu->disp = 0x0000;
            if((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000111) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0b000: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 0b001: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 0b010: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 0b011: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 0b100: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 0b101: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 0b110: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 0b111: cpu->base = cpu->general_purpose_registers[BX];   
            }
            cpu->segments_registers[(cpu->modrm>>3) & 0b00000111] = fetch_word(cpu->segments_registers[DS], cpu->base + cpu->disp);
        }
        else{ //segreg <- reg
            cpu->segments_registers[(cpu->modrm>>3) & 0b00000111] = cpu->general_purpose_registers[cpu->modrm & 0b00000111];
        }
        break;

        case MICRO_LOAD_RM_SEGREG:
        if((cpu->modrm & 0b11000000) != 0b11000000){ // memory <- segreg
            cpu->disp = 0x0000;
            if((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000111) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0b000: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 0b001: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 0b010: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 0b011: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 0b100: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 0b101: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 0b110: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 0b111: cpu->base = cpu->general_purpose_registers[BX];   
            }
            uint_32 phys_address = get_phys_address(cpu->segments_registers[DS], cpu->base+cpu->disp);
            RAM[phys_address] = cpu->segments_registers[cpu->modrm>>3 & 0b00000111] & 0xFF;
            RAM[phys_address+1] = (cpu->segments_registers[cpu->modrm>>3 & 0b00000111]>>8) & 0xFF;
        }
        else{//reg <- segreg
            cpu->general_purpose_registers[cpu->modrm & 0b00000111] = cpu->segments_registers[(cpu->modrm>>3) & 0b00000111];
        }
        break;

        case MICRO_LOAD_REG_IMM8:
        switch(cpu->opcode & 0b00000111){
            case 0b000: //AL
            cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0xFF00) | (uint_8)fetch_prefetch_byte(cpu);
            break;
            case 0b001: //CL
            cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0xFF00) | (uint_8)fetch_prefetch_byte(cpu);
            break;
            case 0b010: //DL
            cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0xFF00) | (uint_8)fetch_prefetch_byte(cpu);
            break;
            case 0b011: //BL
            cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0xFF00) | (uint_8)fetch_prefetch_byte(cpu);
            break;
            case 0b100: //AH
            cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0x00FF) | (((uint_8)fetch_prefetch_byte(cpu))<<8);
            break;
            case 0b101: //CH
            cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0x00FF) | (((uint_8)fetch_prefetch_byte(cpu))<<8);
            break;
            case 0b110: //DH
            cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0x00FF) | (((uint_8)fetch_prefetch_byte(cpu))<<8);
            break;
            case 0b111: //BH
            cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0x00FF) | (((uint_8)fetch_prefetch_byte(cpu))<<8);
            break;
        }
        break;

        case MICRO_LOAD_REG8_RM8:
        if((cpu->modrm & 0b11000000) != 0b11000000){ // reg <- memory
            cpu->disp = 0x0000;
            if((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000111) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0b000: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 0b001: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 0b010: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 0b011: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 0b100: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 0b101: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 0b110: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 0b111: cpu->base = cpu->general_purpose_registers[BX];   
            }
            switch((cpu->modrm>>3) & 0b00000111){
                case 0b000: //AL
                cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0xFF00) | (uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp);
                break;
                case 0b001: //CL
                cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0xFF00) | (uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp);
                break;
                case 0b010: //DL
                cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0xFF00) | (uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp);
                break;
                case 0b011: //BL
                cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0xFF00) | (uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp);
                break;
                case 0b100: //AH
                cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0x00FF) | (((uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp))<<8);
                break;
                case 0b101: //CH
                cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0x00FF) | (((uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp))<<8);
                break;
                case 0b110: //DH
                cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0x00FF) | (((uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp))<<8);
                break;
                case 0b111: //BH
                cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0x00FF) | (((uint_8)fetch_byte(cpu->segments_registers[DS], cpu->base + cpu->disp))<<8);
                break;
            }
        }
        else{ //reg <- reg

            uint_8 source_value;
            switch((cpu->modrm>>3) & 0b00000111){
                case 0b000: //AL
                source_value = cpu->general_purpose_registers[AX] & 0xFF;
                break;
                case 0b001: //CL
                source_value = cpu->general_purpose_registers[CX] & 0xFF;
                break;
                case 0b010: //DL
                source_value = cpu->general_purpose_registers[DX] & 0xFF;
                break;
                case 0b011: //BL
                source_value = cpu->general_purpose_registers[BX] & 0xFF;
                break;
                case 0b100: //AH
                source_value = (cpu->general_purpose_registers[AX]>>8) & 0xFF;
                break;
                case 0b101: //CH
                source_value = (cpu->general_purpose_registers[CX]>>8) & 0xFF;
                break;
                case 0b110: //DH
                source_value = (cpu->general_purpose_registers[DX]>>8) & 0xFF;
                break;
                case 0b111: //BH
                source_value = (cpu->general_purpose_registers[BX]>>8) & 0xFF;
                break;
            }

            switch((cpu->modrm>>3) & 0b00000111){
                case 0b000: //AL
                cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0xFF00) | source_value;
                break;
                case 0b001: //СL
                cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0xFF00) | source_value;
                break;
                case 0b010: //DL
                cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0xFF00) | source_value;
                break;
                case 0b011: //BL
                cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0xFF00) | source_value;
                break;
                case 0b100: //AH
                cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0x00FF) | source_value<<8;
                break;
                case 0b101: //CH
                cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0x00FF) | source_value<<8;
                break;
                case 0b110: //DH
                cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0x00FF) | source_value<<8;
                break;
                case 0b111: //BH
                cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0x00FF) | source_value<<8;
                break;
            }
        }
        break;

        case MICRO_LOAD_RM8_REG8:
        if((cpu->modrm & 0b11000000) != 0b11000000){ // memory <- reg
            cpu->disp = 0x0000;
            if((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000111) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0b000: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 0b001: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 0b010: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 0b011: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 0b100: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 0b101: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 0b110: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 0b111: cpu->base = cpu->general_purpose_registers[BX];   
            }
            uint_32 phys_address = get_phys_address(cpu->segments_registers[DS], cpu->base+cpu->disp);
            switch((cpu->modrm>>3) & 0b00000111){
                case 0b000: //AL
                RAM[phys_address] = cpu->general_purpose_registers[AX] & 0xFF;
                break;
                case 0b001: //CL
                RAM[phys_address] = cpu->general_purpose_registers[CX] & 0xFF;
                break;
                case 0b010: //DL
                RAM[phys_address] = cpu->general_purpose_registers[DX] & 0xFF;
                break;
                case 0b011: //BL
                RAM[phys_address] = cpu->general_purpose_registers[BX] & 0xFF;
                break;
                case 0b100: //AH
                RAM[phys_address] = (cpu->general_purpose_registers[AX]>>8) & 0xFF;
                break;
                case 0b101: //CH
                RAM[phys_address] = (cpu->general_purpose_registers[CX]>>8) & 0xFF;
                break;
                case 0b110: //DH
                RAM[phys_address] = (cpu->general_purpose_registers[DX]>>8) & 0xFF;
                break;
                case 0b111: //BH
                RAM[phys_address] = (cpu->general_purpose_registers[BX]>>8) & 0xFF;
                break;
            }
        }
        else{ // reg <- reg
            uint_8 source_value;
            switch((cpu->modrm>>3) & 0b00000111){
                case 0b000: //AL
                source_value = cpu->general_purpose_registers[AX] & 0xFF;
                break;
                case 0b001: //CL
                source_value = cpu->general_purpose_registers[CX] & 0xFF;
                break;
                case 0b010: //DL
                source_value = cpu->general_purpose_registers[DX] & 0xFF;
                break;
                case 0b011: //BL
                source_value = cpu->general_purpose_registers[BX] & 0xFF;
                break;
                case 0b100: //AH
                source_value = (cpu->general_purpose_registers[AX]>>8) & 0xFF;
                break;
                case 0b101: //CH
                source_value = (cpu->general_purpose_registers[CX]>>8) & 0xFF;
                break;
                case 0b110: //DH
                source_value = (cpu->general_purpose_registers[DX]>>8) & 0xFF;
                break;
                case 0b111: //BH
                source_value = (cpu->general_purpose_registers[BX]>>8) & 0xFF;
                break;
            }

            switch((cpu->modrm>>3) & 0b00000111){
                case 0b000: //AL
                cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0xFF00) | source_value;
                break;
                case 0b001: //СL
                cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0xFF00) | source_value;
                break;
                case 0b010: //DL
                cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0xFF00) | source_value;
                break;
                case 0b011: //BL
                cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0xFF00) | source_value;
                break;
                case 0b100: //AH
                cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0x00FF) | source_value<<8;
                break;
                case 0b101: //CH
                cpu->general_purpose_registers[CX] = (cpu->general_purpose_registers[CX] & 0x00FF) | source_value<<8;
                break;
                case 0b110: //DH
                cpu->general_purpose_registers[DX] = (cpu->general_purpose_registers[DX] & 0x00FF) | source_value<<8;
                break;
                case 0b111: //BH
                cpu->general_purpose_registers[BX] = (cpu->general_purpose_registers[BX] & 0x00FF) | source_value<<8;
                break;
            }
        }
        break;
    }
    return;
}

void init_cpu(CPU* cpu){
    cpu->opcode                         = 0x00;
    cpu->modrm                          = 0x00;
    cpu->disp                           = 0x0000;
    cpu->base                           = 0x0000;
    cpu->reset                          = 0x00;

    cpu->general_purpose_registers[AX]  = 0x0000;
    cpu->general_purpose_registers[BX]  = 0x0000;
    cpu->general_purpose_registers[CX]  = 0x0000;
    cpu->general_purpose_registers[DX]  = 0x0000;
    cpu->general_purpose_registers[SP]  = 0x0000;
    cpu->general_purpose_registers[BP]  = 0x0000;
    cpu->general_purpose_registers[SI]  = 0x0000;
    cpu->general_purpose_registers[DI]  = 0x0000;

    cpu->segments_registers[CS]         = 0x0000;
    cpu->segments_registers[DS]         = 0x0000;
    cpu->segments_registers[ES]         = 0x0000;
    cpu->segments_registers[SS]         = 0x0000;

    cpu->system_registers[IP]           = (0x00|cpu->reset);
    cpu->system_registers[FLAGS]        = 0x0000;

    init_prefetch_queue(cpu);
    return;
}
//fetch->decode->execute
void run(CPU* cpu){
    pipeline_info(cpu);
    while(!cpu->reset){
        #if DEBUG == 1
        raminfo(RAM, 512);
        #endif
        cpu->opcode = fetch_prefetch_byte(cpu); //fetch opcode
        //decode->execute
        for(int i = 0; MICROCODE_ROM[cpu->opcode][i]!=MICRO_END && !cpu->reset; i++){

            //check by proggram (it's not an emulation)
            if(MICROCODE_ROM[cpu->opcode][i]==0x00){
                execute_uop(cpu,MICRO_UNSUPPORTED);
            }
            //========================================
            execute_uop(cpu, MICROCODE_ROM[cpu->opcode][i]);
        }
        cpuinfo(cpu);
    }
    raminfo(RAM, 512);
    return;
}

int main(){
    uint_8 code[] = {
        0x04, 0x01,                 //add al, 0x01
        0xB4, 0xFF,                 //mov ah, 0xFF
        0x04, 0x02,                 //add al, 0x02
        0xB0, 0xFF,                 //mov al, 0xFF
        0xB8, 0x00, 0xFF,           //mov ax, 0xFF00
        0xA3, 0x00, 0x00,           //mov [0x0000], ax
        0x8B, 0x0E, 0x00, 0x00,     //mov cx, [0x0000]      
        0x90,                       //nop
        0xF4                        //hlt               
    };
    memorycopy(RAM, code, sizeof(code));
    raminfo(RAM, 512);
    CPU cpu;
    init_cpu(&cpu);
    run(&cpu);
    return 0;
}