#include <stdio.h>
typedef unsigned short  uint_16;
typedef unsigned int    uint_32;
typedef unsigned char   uint_8;
typedef unsigned long long uint_64;
uint_8 RAM[1024*1024];

typedef enum{
    MICRO_STORE_MEM_REG,
    MICRO_LOAD_REG_MEM,
    MICRO_LOAD_REG_IMM16,
    MICRO_LOAD_REG_IMM8,
    MICRO_INC_REG,
    MICRO_DEC_REG,
    MICRO_FETCH_MODRM,
    MICRO_DECODE_MODRM,
    MICRO_FETCH_DISP8,
    MICRO_FETCH_DISP16,
    MICRO_CALC_EFF_ADDR,
    MICRO_LOAD_REG_RM,
    MICRO_END
}Uop_instruct;

static const Uop_instruct *MICROCODE_ROM[]={
    [0x8B] = (Uop_instruct[]){
        MICRO_FETCH_MODRM,
        MICRO_LOAD_REG_RM,
        MICRO_END
    }, //mov r16, r/m16
    [0x90] = (Uop_instruct[]){
        MICRO_END
    }, //nop
};

enum{
    CS,
    DS,
    ES,
    SS,
    SR_COUNT
}Segment_registers;
enum{
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
enum{
    IP,
    FLAGS,
    S_COUNT,
}System_registers;

typedef struct{
    uint_16 general_purpose_registers[GPR_COUNT];   //ax, cx, dx, bx, sp, bp, si, di
    uint_16 segments_registers[SR_COUNT];           //cs, ds, es, ss
    uint_16 system_registers[S_COUNT];              //ip, flags

    uint_8 prefetch_queue[6];
    uint_16 prefetch_head;
    uint_16 prefetch_count;
    uint_16 prefetch_next_ip;

    uint_8 opcode;
    uint_8 modrm;
    uint_16 disp;                                   //displacement
    uint_16 base;
    uint_8 reset;
}CPU;

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
    cpu->prefetch_head = 0x0000;
    cpu->prefetch_count = 0x0000;
    cpu->prefetch_next_ip = cpu->system_registers[IP];

    //fill queue
    while(cpu->prefetch_count<6){
        cpu->prefetch_queue[(cpu->prefetch_head + cpu->prefetch_count) % 6] 
        = 
        RAM[get_phys_address(cpu->segments_registers[CS], cpu->prefetch_next_ip++)];
        cpu->prefetch_count++;
    }
    return;
}

uint_8 fetch_prefetch_byte(CPU *cpu){
    if(cpu->prefetch_count == 0){
        init_prefetch_queue(cpu);
    }
    uint_8 byte = cpu->prefetch_queue[cpu->prefetch_head];
    cpu->prefetch_head = (cpu->prefetch_head+1) % 6;

    cpu->prefetch_count--;
    cpu->system_registers[IP]++;

    if(cpu->prefetch_count<6){
        cpu->prefetch_queue[(cpu->prefetch_head + cpu->prefetch_count) % 6] 
        = RAM[get_phys_address(cpu->segments_registers[CS], cpu->prefetch_next_ip)];
        cpu->prefetch_next_ip++;
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
        case MICRO_END:
        break;
        case MICRO_FETCH_MODRM:
        cpu->modrm = fetch_prefetch_byte(cpu);
        break;

        case MICRO_LOAD_REG_RM:
        if((cpu->modrm & 0b11000000) != 0b11000000){ //reg <- memory
            cpu->disp = 0x0000;
            if ((cpu->modrm & 0b01000000) == 0b01000000){
                cpu->disp = (uint_8)fetch_prefetch_byte(cpu);
            }
            if (((cpu->modrm & 0b10000000) == 0b10000000) || (((cpu->modrm & 0b11000000) == 0x00) && ((cpu->modrm & 0b00000110) == 0b00000110))){
                cpu->disp = (uint_16)fetch_prefetch_word(cpu);
            }
            cpu->base = 0x0000;
            switch(cpu->modrm & 0b00000111){
                case 0: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[SI]; break;
                case 1: cpu->base = cpu->general_purpose_registers[BX] + cpu->general_purpose_registers[DI]; break;
                case 2: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[SI]; break;
                case 3: cpu->base = cpu->general_purpose_registers[BP] + cpu->general_purpose_registers[DI]; break;
                case 4: cpu->base = cpu->general_purpose_registers[SI];                                      break;
                case 5: cpu->base = cpu->general_purpose_registers[DI];                                      break;
                case 6: cpu->base = ((cpu->modrm & 0b11000000) == 0x00) ? 0x00 : cpu->general_purpose_registers[BP]; break;
                case 7: cpu->base = cpu->general_purpose_registers[BX];   
            }
            cpu->general_purpose_registers[((cpu->modrm&0b00111000)>>3)] = fetch_word(cpu->segments_registers[DS], cpu->base+cpu->disp);
        }
        else { //reg <- reg
            cpu->general_purpose_registers[((cpu->modrm&0b00111000)>>3)] = cpu->general_purpose_registers[((cpu->modrm&0b00000111))];
        }
        break;
    }
    return;
}

void init_cpu(CPU* cpu){
    cpu->general_purpose_registers[AX] = 0x0000;
    cpu->general_purpose_registers[BX] = 0x0001;
    cpu->general_purpose_registers[CX] = 0x0000;
    cpu->general_purpose_registers[DX] = 0x0000;
    cpu->general_purpose_registers[SP] = 0x0000;
    cpu->general_purpose_registers[BP] = 0x0000;
    cpu->general_purpose_registers[SI] = 0x0000;
    cpu->general_purpose_registers[DI] = 0x0000;

    cpu->segments_registers[CS] = 0x0000;
    cpu->segments_registers[DS] = 0x0000;
    cpu->segments_registers[ES] = 0x0000;
    cpu->segments_registers[SS] = 0x0000;

    cpu->system_registers[IP] = 0x0000;
    cpu->system_registers[FLAGS] = 0x0000;

    cpu->opcode = 0x00;
    cpu->modrm = 0x00;
    cpu->disp = 0x0000;
    cpu->base = 0x0000;
    cpu->reset = 0x00;

    init_prefetch_queue(cpu);
    return;
}
//fetch->decode->execute
void run(CPU* cpu){
    while(!cpu->reset){
        cpu->opcode = fetch_prefetch_byte(cpu); //fetch opcode
        printf("AX = %d BX = %d\n", cpu->general_purpose_registers[AX], cpu->general_purpose_registers[BX]);
        //decode->execute
        for(int i = 0; MICROCODE_ROM[cpu->opcode][i]!=MICRO_END; i++){
            execute_uop(cpu, MICROCODE_ROM[cpu->opcode][i]);
        }
    }

    return;
}

int main(){
    uint_8 code[] = {
        0x8B, 0xC3,       // mov ax, bx
        0x90              // nop
    };
    memorycopy(RAM, code, sizeof(code));
    CPU cpu;
    init_cpu(&cpu);
    run(&cpu);
    return 0;
}