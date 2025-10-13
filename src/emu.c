#include "../lib/include/emulib.h"

//main system

uint_8 RAM[RAM_SIZE_MACRO];
Bus system_bus;
CPU cpu;

int main(){
    uint_8 code[] = {
        0xB8, 0xA0, 0x00,
        0x8E, 0xC8, 0x2E,
        0xA0, 0x00, 0x00,           //mov al, [DS:0x0000]
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
    memorycopy(RAM, code, sizeof(code), 0x0000);
    raminfo(RAM, 512);
    bus_init(&system_bus, RAM, RAM_SIZE_MACRO);
    init_cpu(&cpu);
    run(&cpu);
    return 0;
}