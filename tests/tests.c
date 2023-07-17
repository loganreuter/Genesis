#include "helper.h"
#include "../src/genesis.h"

int mov_imm32_test()
{
    printf("MOV (IMM32) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
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
        MCR32(MOV_OP, 0b010, EAX),
        0x45,
        MCRR(MOV_OP, 0b001, EBX, EAX)
    };

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
        MCM32(STR_OP, 0b010, 0x1),
        0x45,
        MCR16(MOV_OP, 0b100, EAX, 0x1)
    };

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
        MCM32(STR_OP, 0b010, 0x1),
        0x45
    };

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
        MCR32(MOV_OP, 0b010, EAX),
        0x45,
        MCR16(STR_OP, 0b100, EAX, 0x1)
    };

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
        MCM32(STR_OP, 0b010, 0x1),
        0x8,
        MCM32(STR_OP, 0b001, 0x2),
        0x1
    };

    start(vm, ops, 4);

    uint32_t val = mem_read(vm, 0x2);

    free(vm);
    return ASSERT_EQ(val, 0x8);
}

////////////////////////////
// Arithmetic
////////////////////////////
int add_test()
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

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int iadd_test()
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

    free(vm);
    return ASSERT_EQ(val, 0x45);
}
int inc_test()
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

    free(vm);
    return ASSERT_EQ(val, 0x45);
}

int sub_test()
{
    printf("SUB Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x1,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(SUB_OP, 0b001, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, ECX),
        0x45,
        MCR32(SUB_OP, 0b010, ECX),
        0x44
    };
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
        MCR32(MOV_OP, 0b010, EDX),
        0x46,
        MCR32(SUB_OP, 0b100, EDX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0xD2,
        MCR32(MOV_OP, 0b010, EDX),
        0x2,
        MCRR(MUL_OP, 0b001, EAX, EDX)
    };
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
        MCR32(MOV_OP, 0b010, EFX),
        0x2,
        MCR32(MUL_OP, 0b010, EFX),
        0x2
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x4,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(DIV_OP, 0b001, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x4,
        MCR32(DIV_OP, 0b010, EAX),
        0x2
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x4,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(MOD_OP, 0b001, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x1B,
        MCR32(MOD_OP, 0b010, EAX),
        0x8
    };
    int size = 4;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}

int shl_test()
{
    printf("SHL Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x1,
        MCM32(SH_OP, 0b001, EAX),
        0x1
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCM32(SH_OP, 0b010, EAX),
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
        MCR32(MOV_OP, 0b010, EAX),
        0x3,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(AND_OP, 0, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(OR_OP, 0, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x3,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(XOR_OP, 0, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x3,
        MCR32(MOV_OP, 0b010, EBX),
        0x3,
        MCRR(TEST_OP, 0, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(TEST_OP, 0, EBX, EAX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x0,
        MCR32(NOT_OP, 0, EAX)
    };
    int size = 3;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, -1);
}

int cmp_eq_test()
{
    printf("CMP (EQ) Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x4,
        MCR32(MOV_OP, 0b010, EBX),
        0x4,
        MCRR(CMP_OP, 0, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x1,
        MCR32(MOV_OP, 0b010, EBX),
        0x3,
        MCRR(CMP_OP, 0, EAX, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x1,
        MCR32(MOV_OP, 0b010, EBX),
        0x3,
        MCRR(CMP_OP, 0, EBX, EAX)};
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
        MCR16(JMP_OP, 0, 0, 0x3),
        MCR32(MOV_OP, 0b010, EAX),
        0x1,
        MCR32(MOV_OP, 0b010, EBX),
        0x3
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x0, 0, 0x8),
        MCR32(ADD_OP, 0b100, EAX),
        MCR32(ADD_OP, 0b100, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x0, 0, 0x8),
        MCR32(ADD_OP, 0b100, EAX),
        MCR32(ADD_OP, 0b100, EBX)};
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x1, 0, 0x8),
        MCR32(ADD_OP, 0b100, EAX),
        MCR32(ADD_OP, 0b100, EBX)};
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x1, 0, 0x8),
        MCR32(ADD_OP, 0b100, EAX),
        MCR32(ADD_OP, 0b100, EBX)};
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x2, 0, 0x7),
        MCR32(ADD_OP, 0b100, EAX),
        MCR32(ADD_OP, 0b100, EBX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x2, 0, 0x7),
        MCR32(ADD_OP, 0b100, EAX),
        MCR32(ADD_OP, 0b100, EBX)};
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x1,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x2, 0, 0x7),
        MCR32(ADD_OP, 0b100, EBX),
        MCR32(ADD_OP, 0b100, EAX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x2, 0, 0x7),
        MCR32(ADD_OP, 0b100, EBX),
        MCR32(ADD_OP, 0b100, EAX)};
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x3,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x2, 0, 0x7),
        MCR32(ADD_OP, 0b100, EBX),
        MCR32(ADD_OP, 0b100, EAX)};
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
        MCR32(MOV_OP, 0b010, EAX),
        0x1,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x4, 0, 0x7),
        MCR32(ADD_OP, 0b100, EBX),
        MCR32(ADD_OP, 0b100, EAX)
    };
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
        MCR32(MOV_OP, 0b010, EAX),
        0x2,
        MCR32(MOV_OP, 0b010, EBX),
        0x2,
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x4, 0, 0x7),
        MCR32(ADD_OP, 0b100, EBX),
        MCR32(ADD_OP, 0b100, EAX)};
    int size = 8;

    start(vm, ops, size);

    uint32_t val = vm->registers[EBX];

    free(vm);
    return ASSERT_EQ(val, 0x3);
}

int for_loop_test()
{
    printf("For Loop Test\n");
    VM *vm = createVM();

    uint32_t ops[] = {
        MCR32(MOV_OP, 0b010, EAX),
        0x0,
        MCR32(MOV_OP, 0b010, EBX), // Move number of times to repeat into EBX
        0x5,
        MCR32(ADD_OP, 0b100, EAX), //INCR EAX until it is 5
        MCRR(CMP_OP, 0, EAX, EBX),
        MCR16(JUMP_OP, 0x1, 0, 0x4),
    };
    int size = 7;

    start(vm, ops, size);

    uint32_t val = vm->registers[EAX];

    free(vm);
    return ASSERT_EQ(val, 0x5);
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
    inc_test();

    sub_test();
    isub_test();
    dec_test();

    mul_test();
    imul_test();

    div_test();
    idiv_test();

    mod_test();
    imod_test();

    shl_test();
    shr_test();

    and_test();

    or_test();

    xor_test();

    test_test();
    test_zf_test();

    not_test();

    cmp_eq_test();
    cmp_l_test();
    cmp_g_test();

    jmp_test();

    je_test();
    je_n_test();
    jne_test();
    jne_n_test();
    jg_test();
    jg_n_test();
    jge_g_test();
    jge_e_test();
    jge_n_test();
    jl_test();
    jl_n_test();

    // for_loop_test();

    return 0;
}