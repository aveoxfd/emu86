gcc -I lib/include src/emu.c src/cpu/cpu.c src/cpu/microcode.c lib/c/emutool.c src/bus/bus.c -o emu.exe
emu.exe
pause