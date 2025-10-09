#include <stdio.h>
#include "cpu"
#include "microcode"

#define DEBUG 0
//modr/m: 11dddsss (d - destination; s - source)

extern uint_8 RAM[];

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

        case MICRO_LOAD_AL_MEM:
        cpu->general_purpose_registers[AX] = (cpu->general_purpose_registers[AX] & 0xFF00); //| RAM[]
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

        if(cpu->opcode == PREFIX_CS_MACRO || cpu->opcode == PREFIX_DS_MACRO || cpu->opcode == PREFIX_ES_MACRO || cpu->opcode == PREFIX_SS_MACRO){
            switch(cpu->opcode){
                case PREFIX_CS_MACRO:
                cpu->segment = cpu->segments_registers[CS];
                break;
                case PREFIX_DS_MACRO:
                cpu->segment = cpu->segments_registers[DS];
                break;
                case PREFIX_ES_MACRO:
                cpu->segment = cpu->segments_registers[ES];
                break;
                case PREFIX_SS_MACRO:
                cpu->segment = cpu->segments_registers[SS];
                break;
            }
            continue;
        }
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
    cpu->segment = cpu->segments_registers[DS];
    raminfo(RAM, 512);
    return;
};