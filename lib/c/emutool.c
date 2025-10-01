#include <stdio.h>
#include "emutool.h"
#include "emulib.h"

int get_circular_index(const uint_32 index, const uint_32 len){
    int result = (index%len) < 0 ? (index%len)+len : index%len;
    return result;
}

void pipeline_info(CPU* cpu){
    printf("pipeline: ");
    for (int i = 0; i<PREFETCH_QUEUE_SIZE_MACRO; i++){
        printf("%d  ", i);
    }
    printf("\n          ");
    for(int i = 0; i<PREFETCH_QUEUE_SIZE_MACRO; i++){
        printf("%02x ", cpu->prefetch_queue[i]);
    }
    printf("\n");
    return;
}

void cpuinfo(CPU *cpu){
    printf("======================================================================================================\n");
    printf("AX = %d\tCX = %d\tDX = %d\tBX = %d\tSP = %d\tBP = %d\tSI = %d\tDI = %d\n", 
        cpu->general_purpose_registers[AX],
        cpu->general_purpose_registers[CX],
        cpu->general_purpose_registers[DX],
        cpu->general_purpose_registers[BX],
        cpu->general_purpose_registers[SP],
        cpu->general_purpose_registers[BP],
        cpu->general_purpose_registers[SI],
        cpu->general_purpose_registers[DI]
    );
    printf("CS = %d\tDS = %d\tES = %d\tSS = %d\n",
        cpu->segments_registers[CS],
        cpu->segments_registers[DS],
        cpu->segments_registers[ES],
        cpu->segments_registers[SS]
    );
    printf("IP = %d\tFLAGS = %d\n", 
    cpu->system_registers[IP],
    cpu->system_registers[FLAGS]
    );
    printf ("OPCODE = 0x%02x\tMODR\\M = %d\n", cpu->opcode, cpu->modrm);
    pipeline_info(cpu);
    printf("======================================================================================================\n");
    return;
}
void raminfo(uint_8 *ram, uint_32 len) {
    // head
    printf("          ");
    for(int i = 0; i < 16; i++) {
        printf("%02x ", i);
    }
    printf("\n");
    // data
    for(uint_32 i = 0; i < len; i += 16) {
        // adress
        printf("%08x: ", i);
        // hex
        for(int j = 0; j < 16; j++) {
            if(i + j < len) {
                printf("%02x ", ram[i + j]);
            } else {
                printf("   "); // align for nofully string
            }
        }
        //ascii associations
        printf(" ");
        for(int j = 0; j < 16; j++) {
            if(i + j >= len) break;
            
            unsigned char c = ram[i + j];
            //replace noreadable -> dot
            if(c < 32 || c > 126) {
                printf(".");
            } else {
                printf("%c", c);
            }
        }
        printf("\n");
    }
    return;
}