
#include "types.h"

typedef struct Bus {
    // main memory
    uint_8* ram;
    uint_32 ram_size;
    
    // ROM (BIOS)
    uint_8* rom;
    uint_32 rom_size;
    uint_32 rom_base;
    
    // devices on bus
    BusDevice* devices;
    int device_count;
    
    // system controllers
    PIC pic_master;
    PIC pic_slave;
    PIT pit;
    DMAController dma;
    
    // bus state
    BusState state;
    uint_8 current_owner;
    
    // timing model
    uint_64 total_cycles;
    uint_32 current_cycle;
    uint_32 bus_cycle_length;  // bus cycle length in CPU clock cycles
    
    // buses signals
    uint_8 address_valid;
    uint_8 data_valid;
    uint_8 mem_read;
    uint_8 mem_write;
    uint_8 io_read;
    uint_8 io_write;
    
    // current transaction
    uint_32 current_address;
    uint_16 current_data;
    uint_8 current_size;  // 1 - byte, 2 - word
    
    // interrupts
    uint_8 interrupt_request;
    uint_8 interrupt_vector;
    uint_8 nmi_request;
    uint_8 ack_pending;
    
    // DMA
    uint_8 dma_request;
    uint_8 dma_ack;
    uint_8 dma_eop;  // End Of Process
    
    // statistics
    uint_64 memory_accesses;
    uint_64 io_accesses;
    uint_64 dma_transfers;
    
    // debug
    uint_8 debug;
    void (*bus_trace)(struct Bus* bus, const char* operation, uint_32 address, uint_16 data);
} Bus;