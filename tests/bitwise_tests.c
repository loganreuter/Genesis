#include "tests.h"

int shl_test()
{
    printf("SHL Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x1,
        MCR32(SH_OP, 0x3, EAX),
        0x1};
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int shr_test()
{
    printf("SHR Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCM32(SH_OP, 0x1, EAX),
        0x1};
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 1);
}

int and_test()
{
    printf("AND Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x3,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(AND_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}

int or_test()
{
    printf("OR Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(OR_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}

int xor_test()
{
    printf("XOR Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x3,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(XOR_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x1);
}

int test_test()
{
    printf("TEST Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x3,
        MCR32(MOV_OP, 0x1, EBX),
        0x3,
        MCRR(TEST_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[FLAG] & SF;

    free(vm);
    return ASSERT_EQ(val, 0);
}
int test_zf_test()
{
    printf("TEST (ZF) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(TEST_OP, 0x0, EBX, EAX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[FLAG] & ZF;

    free(vm);
    return ASSERT_EQ(val, ZF);
}

int not_test()
{
    printf("NOT Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x0,
        MCR32(NOT_OP, 0x0, EAX)};
    int size = 3;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, -1);
}

test bitwise_tests[] = {
    shl_test,
    shr_test,

    and_test,
    or_test,
    xor_test,

    test_test,
    test_zf_test,

    not_test,

    end
};