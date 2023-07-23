#include "tests.h"

int print_test()
{
    printf("INT (print) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x61,
        MCR16(INT_OP, 0, 0, 0x10)
    };
    int size = 3;

    start(vm, ops, size);

    uint32_t val = 0;

    free(vm);
    return ASSERT_EQ(val, 0);
}
int alphabet_test()
{
    printf("Alphabet Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x61,
        MCR16(INT_OP, 0, 0, 0x10),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(CMP_OP, 0x1, EAX),
        0x7a,
        MCR16(JMP_OP, 0x6, 0, 0x2)
    };
    int size = 7;

    start(vm, ops, size);

    uint32_t val = 0;

    free(vm);
    return ASSERT_EQ(val, 0);
}

test interrupt_tests[] = {
    print_test,
    alphabet_test,

    end
};