#include "tests.h"

int for_loop_test()
{
    printf("For Loop Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x0,
        MCR32(MOV_OP, 0x1, EBX), // Move number of times to repeat into EBX
        0x5,
        MCR32(ADD_OP, 0x2, EAX), // INCR EAX until it is 5
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x2, 0, 0x4),
    };
    int size = 7;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x5);
}

test loop_tests[] = {
    for_loop_test,

    end
};