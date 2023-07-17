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
uint32_t MCR16(OPCODES op, uint8_t mode, enum regist r1, uint16_t val) 
{
    uint32_t mc = 0;

    mc |= (op << 26);
    mc |= (mode << 23);
    mc |= (r1 << 19);
    mc |= val;

    return mc;
}

// Create machine code for Register-IMM32 operation
uint32_t MCR32(OPCODES op, uint8_t mode, enum regist r1)
{ 
    uint32_t mc = 0;

    mc |= (op << 26);
    mc |= (mode << 23);
    mc |= (r1 << 19);

    return mc; 
}

uint32_t MCM32(OPCODES op, uint8_t mode, uint16_t addr)
{
    uint32_t mc = 0;

    mc |= (op << 26);
    mc |= (mode << 23);
    mc |= addr;

    return mc;
}

int ASSERT_EQ(uint32_t val, uint32_t check)
{
    if(val == check)
    {
        printf("\033[32mTest Passed!\033[0m\n");
    } else 
    {
        printf("\033[31mFAILED!\033[0m\nExpected: x%X\nFound: x%X\n", check, val);
    }   
    return val == check;
}

int ASSERT_NEQ(uint32_t val, uint32_t check)
{
    if (val != check)
    {
        printf("\033[32mTest Passed!\033[0m\n");
    }
    else
    {
        printf("\033[31mFAILED!\033[0m\nExpected: x%X\nFound: x%X\n", check, val);
    }
    return val != check;
}
