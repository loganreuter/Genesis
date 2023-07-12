#include "helper.h"

// Create machine code for Register-Register operation
uint32_t MCRR(OPCODES op, uint8_t mode, enum regist r1, enum regist r2)
{
    uint32_t mc = 0;

    mc |= (op << 26);
    mc |= (mode << 23);
    mc |= (r1 << 19);
    mc |= r2;

    return mc;
}

// Create machine code for Register-IMM16 operation
uint32_t MCR16() { return 0; }

// Create machine code for Register-IMM32 operation
uint32_t MCR32() { return 0; }

void ASSERT_EQ(uint32_t val, uint32_t check){
    
}
