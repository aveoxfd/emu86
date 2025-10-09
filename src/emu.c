#include "../lib/include/emulib.h"

uint_8 RAM[1024*1024];

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