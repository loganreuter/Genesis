#include "helper.h"
#include "../src/genesis.h"

int main()
{
    printf("Hello, World!\n");
    printf("Output: 0x%08X\n", MCRR(MOV_OP, 0b000, EAX, EBX));

    return 0;
}