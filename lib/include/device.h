#include "types.h"

typedef enum {
    DEVICE_NONE = 0,
    DEVICE_RAM,
    DEVICE_ROM,
    DEVICE_PIC,      // Interrupt Controller 8259A
    DEVICE_PIT,      // Timer 8253/8254
    DEVICE_PPI,      // 8255 programmable peripheral interface
    DEVICE_DMA,      // DMA 8237 Controller
    DEVICE_VGA,      // Video controller
    DEVICE_KEYBOARD, // Keyboard Controller
    DEVICE_FLOPPY,   // Disk Drive Controller
    DEVICE_HDD       // Hard Disk Controller
} DeviceType;

typedef struct BusDevice {
    DeviceType type;
    char name[32];
    
    // Device address space
    uint_32 base_address;
    uint_32 size;
    
    // Device functions
    uint_8 (*read_byte)(struct BusDevice* dev, uint_32 address);
    void (*write_byte)(struct BusDevice* dev, uint_32 address, uint_8 value);
    uint_16 (*read_word)(struct BusDevice* dev, uint_32 address);
    void (*write_word)(struct BusDevice* dev, uint_32 address, uint_16 value);
    
    // I/O Port Functions
    uint_8 (*io_read)(struct BusDevice* dev, uint_16 port);
    void (*io_write)(struct BusDevice* dev, uint_16 port, uint_8 value);
    
    // Device data
    void* device_data;
    
    // Time(delay) characteristics
    uint_32 access_time;  // Access time in clock cycles
    uint_32 wait_states;  // Additional waiting cycles
    
    struct BusDevice* next;
} BusDevice;