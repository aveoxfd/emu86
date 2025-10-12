#include "bus"
#include "bool.h"
#include <stdio.h>

void bus_init(Bus* bus, uint_8 *ram, unsigned long long ram_size){
    bus->address_bus    = 0x00000000;
    bus->control_bus    = MEM_READ;
    bus->data_bus       = 0x0000;
    bus->ram            = ram;
    bus->ram_size       = ram_size;
    bus->device_count   = 0;
    return;
}

void bus_attach_device(Bus *bus, void *device, uint_32 base_addr, uint_32 size, uint_8 (*read)(void*, uint_32), void (*write)(void*, uint_32, uint_8)){
    if (bus->device_count < MAX_DEVICE_COUNT_MACRO){
        bus->devices[bus->device_count].device      = device;
        bus->devices[bus->device_count].base_addr   = base_addr;
        bus->devices[bus->device_count].size        = size;
        bus->devices[bus->device_count].read        = read;
        bus->devices[bus->device_count].write       = write;
        bus->device_count++;
    }
    return;
}

uint_16 bus_cycle(Bus *bus, uint_32 address, BusControl control, uint_16 data){
    bus->address_bus = address;
    bus->control_bus = control;

    if (control == MEM_WRITE || control == IO_WRITE){
        bus->data_bus = data;
    }

    bool handled = false;

    for (int i = 0; i < bus->device_count; i++){
        if(address >= bus->devices[i].base_addr && address < bus->devices[i].base_addr + bus->devices[i].size){
            uint_32 relative_address = address - bus->devices[i].base_addr;

            if(control == MEM_READ || control == IO_READ){
                bus->data_bus = bus->devices[i].read(bus->devices[i].device, relative_address);
            }
            else{
                bus->devices[i].write(bus->devices[i].device, relative_address, data & 0xFF);
            }
            handled = true;
            break;
        }
    }
    if(!handled){
        if(address < bus->ram_size){
            if(control == MEM_READ){
                if(address + 1 < bus->ram_size){
                    bus->data_bus = bus->ram[address] | (bus->ram[address + 1] << 8);
                }
                else{
                    bus->data_bus = bus->ram[address];
                }
            }
            else if (control == MEM_WRITE){
                bus->ram[address] = data & 0xFF;
                if(address + 1 < bus->ram_size){
                    bus->ram[address + 1] = (data << 8) & 0xFF;
                }
            }
        }
        else{
            printf("Address is out of RAM");
        }
    }
    return bus->data_bus;
}