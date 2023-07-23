#include "tests.h"

int mov_imm32_test()
{
    printf("MOV (IMM32) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x45,
    };

    start(vm, ops, 2);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int mov_reg_test()
{
    printf("MOV (reg) Test\n");

    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x45,
        MCRR(MOV_OP, 0x0, EBX, EAX)};

    start(vm, ops, 3);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int mov_mem_test()
{
    printf("MOV (mem) Test\n");

    VM *vm = createVM();

    uint32_t ops[] = {
        MCM32(STR_OP, 0x1, 0x1),
        0x45,
        MCR16(MOV_OP, 0x2, EAX, 0x1)};

    start(vm, ops, 3);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}

int str_imm32_test()
{
    printf("STR (IMM32) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCM32(STR_OP, 0x1, 0x1),
        0x45};

    start(vm, ops, 2);

    uint32_t val = mem_readn(vm, 0x1, 4);

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int str_reg_test()
{
    printf("STR (reg) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x45,
        MCR16(STR_OP, 0x2, EAX, 0x1)};

    start(vm, ops, 3);

    uint32_t val = mem_readn(vm, 0x1, 4);

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int str_mem_test()
{
    printf("STR (mem) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCM32(STR_OP, 0x1, 0x1),
        0x8,
        MCM32(STR_OP, 0x0, 0x2),
        0x1};

    start(vm, ops, 4);

    uint32_t val = mem_read(vm, 0x2);

    free(vm);
    return ASSERT_EQ(val, 0x8);
}

test memory_tests[] = {
    mov_imm32_test,
    mov_reg_test,
    mov_mem_test,

    str_imm32_test,
    str_reg_test,
    str_mem_test,

    end
};