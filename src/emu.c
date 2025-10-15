#include "../lib/include/emulib.h"

//main system

uint_8 RAM[RAM_SIZE_MACRO];
Bus system_bus;
CPU cpu;

int main(){
    uint_8 code[] = {
        0x04, 0x02,                 //add al, 0x02
        0x04, 0x02,                 //add al, 0x02    
        0x90,                       //nop
        0xF4                        //hlt               
    };
    memorycopy(RAM, code, sizeof(code), 0x0000);
    raminfo(RAM, 512);
    bus_init(&system_bus, RAM, RAM_SIZE_MACRO);
    init_cpu(&cpu);
    run(&cpu);
    return 0;
}