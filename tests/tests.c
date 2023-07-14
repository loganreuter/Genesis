#include "helper.h"
#include "../src/genesis.h"

void mov_imm32_test()
{
    printf("MOV (IMM32) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x45,
    };

    start(vm, ops, 2);

    uint32_t val = vm->registers[EAX];

    ASSERT_EQ(val, 0x45);
    
    free(vm);
}
void mov_reg_test()
{
    printf("MOV (reg) Test\n");

    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x45,
        MCRR(MOV_OP, 0b001, EBX, EAX)
    };

    start(vm, ops, 3);

    uint32_t val = vm->registers[EBX];

    ASSERT_EQ(val, 0x45);

    free(vm);
}
void mov_mem_test()
{
    printf("MOV (mem) Test\n");

    VM *vm = createVM();

    uint32_t ops[] = {
        MCM32(STR_OP, 0b010, 0x1),
        0x45,
        MCR16(MOV_OP, 0b100, EAX, 0x1)
    };

    start(vm, ops, 3);

    uint32_t val = vm->registers[EAX];

    ASSERT_EQ(val, 0x45);

    free(vm);
}

void str_imm32_test()
{
    printf("STR (IMM32) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCM32(STR_OP, 0b010, 0x1),
        0x45
    };

    start(vm, ops, 2);

    uint32_t val = mem_readn(vm, 0x1, 4);

    ASSERT_EQ(val, 0x45);

    free(vm);
}
void str_reg_test()
{
    printf("STR (reg) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x45,
        MCR16(STR_OP, 0b100, EAX, 0x1)
    };

    start(vm, ops, 3);

    uint32_t val = mem_readn(vm, 0x1, 4);

    ASSERT_EQ(val, 0x45);

    free(vm);
}
void str_mem_test()
{
    printf("STR (mem) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCM32(STR_OP, 0b010, 0x1),
        0x8,
        MCM32(STR_OP, 0b001, 0x2),
        0x1
    };

    start(vm, ops, 4);

    uint32_t val = mem_read(vm, 0x2);

    ASSERT_EQ(val, 0x8);

    free(vm);
}

////////////////////////////
// Arithmetic
////////////////////////////
void add_test()
{
    printf("Add Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x44,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(ADD_OP, 0b001, EAX, EBX)
    };

    start(vm, ops, 5);

    uint32_t val = vm->registers[EAX];

    ASSERT_EQ(val, 0x45);
    free(vm);
}
void iadd_test()
{
    printf("IADD Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x44,
        MCR32(ADD_OP, 0b010, EAX),
        0x1
    };

    start(vm, ops, 4);

    uint32_t val = vm->registers[EAX];

    ASSERT_EQ(val, 0x45);
    free(vm);
}
void incr_test()
{
    printf("INC Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x44,
        MCR32(ADD_OP, 0b100, EAX)
    };

    start(vm, ops, 3);

    uint32_t val = vm->registers[EAX];

    ASSERT_EQ(val, 0x45);
}

int main()
{
    mov_imm32_test();
    mov_reg_test();
    mov_mem_test();

    str_imm32_test();
    str_reg_test();
    str_mem_test();

    add_test();
    iadd_test();
    incr_test();

    return 0;
}