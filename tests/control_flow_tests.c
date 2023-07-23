#include "tests.h"

int cmp_eq_test()
{
    printf("CMP (EQ) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x4,
        MCR32(MOV_OP, 0x1, EBX),
        0x4,
        MCRR(CMP_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[FLAG];

    free(vm);
    return ASSERT_EQ(val, ZF);
}
int cmp_l_test()
{
    printf("CMP (Less) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x1,
        MCR32(MOV_OP, 0x1, EBX),
        0x3,
        MCRR(CMP_OP, 0x0, EAX, EBX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[FLAG];

    free(vm);
    return ASSERT_EQ(val, SF);
}
int cmp_g_test()
{
    printf("CMP (Greater) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x1,
        MCR32(MOV_OP, 0x1, EBX),
        0x3,
        MCRR(CMP_OP, 0x0, EBX, EAX)};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[FLAG];

    free(vm);
    return ASSERT_EQ(val, 0);
}

int jmp_test()
{
    printf("JMP Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR16(JMP_OP, 0x0, 0, 0x3),
        MCR32(MOV_OP, 0x1, EAX),
        0x1,
        MCR32(MOV_OP, 0x1, EBX),
        0x3};
    int size = 5;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_NEQ(val, 0x1);
}
int je_test()
{
    printf("JE Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x1, 0, 0x8),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(ADD_OP, 0x2, EBX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int je_n_test()
{
    printf("JE (N) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x1, 0, 0x8),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(ADD_OP, 0x2, EBX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}
int jne_test()
{
    printf("JNE Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x2, 0, 0x8),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(ADD_OP, 0x2, EBX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int jne_n_test()
{
    printf("JNE (N) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x2, 0, 0x8),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(ADD_OP, 0x2, EBX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}
int jg_test()
{
    printf("JG Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x3, 0, 0x7),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(ADD_OP, 0x2, EBX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int jg_n_test()
{
    printf("JG (N) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x3, 0, 0x7),
        MCR32(ADD_OP, 0x2, EAX),
        MCR32(ADD_OP, 0x2, EBX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int jge_g_test()
{
    printf("JGE (G) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x4, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x1);
}
int jge_e_test()
{
    printf("JGE (E) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x4, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int jge_n_test()
{
    printf("JGE (N) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x3,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x4, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x4);
}
int jl_test()
{
    printf("JL Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x1,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x5, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int jl_n_test()
{
    printf("JL (N) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x5, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}
int jle_e_test()
{
    printf("JLE (E) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x6, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)
    };
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x2);
}
int jle_l_test()
{
    printf("JLE (L) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x2,
        MCR32(MOV_OP, 0x1, EBX),
        0x4,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x6, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)
    };
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x4);
}
int jle_n_test()
{
    printf("JLE (N) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0x1, EAX),
        0x4,
        MCR32(MOV_OP, 0x1, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JMP_OP, 0x6, 0, 0x7),
        MCR32(ADD_OP, 0x2, EBX),
        MCR32(ADD_OP, 0x2, EAX)
    };
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}

test control_flow_tests[] = {
    cmp_eq_test,
    cmp_g_test,
    cmp_l_test,

    jmp_test,
    
    je_test,
    je_n_test,

    jne_test,
    jne_n_test,

    jg_test,
    jg_n_test,

    jge_e_test,
    jge_g_test,
    jge_n_test,

    jl_test,
    jl_n_test,

    jle_e_test,
    jle_l_test,
    jle_n_test,

    end
};