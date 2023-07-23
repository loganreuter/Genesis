#include "tests.h"

int add_test()
{
    printf("Add Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x44,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(ADD_OP, 0x0, EAX, EBX)};

    start(vm, ops, 5);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int iadd_test()
{
    printf("IADD Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x44,
        MCR32(ADD_OP, 0x1, EAX),
        0x1};

    start(vm, ops, 4);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int inc_test()
{
    printf("INC Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x44,
        MCR32(ADD_OP, 0x2, EAX)};

    start(vm, ops, 3);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}

int sub_test()
{
    printf("SUB Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x1,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(SUB_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, -1);
}
int isub_test()
{
    printf("ISUB Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, ECX),
        0x45,
        MCR32(SUB_OP, 0x1, ECX),
        0x44};
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[ECX];

    free(vm);
    return ASSERT_EQ(val, 0x1);
}
int dec_test()
{
    printf("DEC Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EDX),
        0x46,
        MCR32(SUB_OP, 0x2, EDX)};
    int size = 3;

    start(vm, ops, size);

    uint32_t val = vm->registers[EDX];

    free(vm);
    return ASSERT_EQ(val, 0x45);
}

int mul_test()
{
    printf("MUL Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0xD2,
        MCR32(MOV_OP, 0x1, EDX),
        0x2,
        MCRR(MUL_OP, 0x0, EAX, EDX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x1A4);
}
int imul_test()
{
    printf("IMUL Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EFX),
        0x2,
        MCR32(MUL_OP, 0x1, EFX),
        0x2};
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[EFX];

    free(vm);
    return ASSERT_EQ(val, 0x4);
}

int div_test()
{
    printf("DIV Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x4,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(DIV_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int idiv_test()
{
    printf("IDIV Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x4,
        MCR32(DIV_OP, 0x1, EAX),
        0x2};
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}

int mod_test()
{
    printf("Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x4,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(MOD_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0);
}
int imod_test()
{
    printf("IMOD Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x1B,
        MCR32(MOD_OP, 0x1, EAX),
        0x8};
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}

test arithmetic_tests[] = {
    add_test,
    iadd_test,
    inc_test,

    sub_test,
    isub_test,
    dec_test,

    mul_test,
    imul_test,

    div_test,
    idiv_test,

    mod_test,
    imod_test,

    end
};