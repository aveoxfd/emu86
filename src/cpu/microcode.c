#include "microcode"

const MicroInstruction *MICROCODE_ROM[256] = {
    [0x00] = { //add, rm8, r8
        {MICRO_FETCH_MODRM, OP_TYPE_NONE}
    }
};