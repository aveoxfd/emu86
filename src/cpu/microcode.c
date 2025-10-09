#include "microcode"

const Uop_instruct *MICROCODE_ROM[]={
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
        MICRO_LOAD_AL_MEM,
        MICRO_END
    },//mov al, [address] 
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