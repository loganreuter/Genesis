#include "genesis.h"
#include "../debug/debug.h"

//Move
void MOV(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //Register-Register
        case 0b001:
            debug("MOV", "MOV %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] = vm->registers[SR2(i)];
            break;
        //Register-IMM32
        case 0b010:
            debug("MOV", "MOV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] = prog_read(vm, vm->registers[PC]++);
            break;
        //Register-Memory
        case 0b100:
            debug("MOV", "MOV %s [%Xh]", name(SR1(i)), IMM16(i));
            vm->registers[SR1(i)] = mem_readn(vm, IMM16(i), 4);
            break;
        default:
            perror("MOV - Unknown mode");
            exit(EXIT_FAILURE);
            break;
    }
}

//Store
void STR(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //Memory-Memory
        case 0b001:
            debug("STR", "STR [%Xh] [%Xh]", IMM16(i), prog_read(vm, vm->registers[PC]));
            mem_write(vm, IMM16(i), mem_read(vm, prog_read(vm, vm->registers[PC]++)));
            break;
        //Memory-IMM32
        case 0b010:
            debug("STR", "STR [%Xh] %Xh", IMM16(i), prog_read(vm, vm->registers[PC]));
            for (uint16_t j = 0; j < 5; j++)
            {
                mem_write(vm, IMM16(i) + j, ENCODE(prog_read(vm, vm->registers[PC]), j));
            }
            vm->registers[PC]++;
            break;
        //Memory-Register
        case 0b100:
            debug("STR", "STR [%Xh] %s", IMM16(i), name(SR1(i)));
            for (uint16_t j = 0; j < 5; j++)
            {
                mem_write(vm, IMM16(i) + j, ENCODE(vm->registers[SR1(i)], j));
            }
            break;
        default:
            perror("STR - Unknown mode");
            exit(EXIT_FAILURE);
            break;
    }   
}

/********************************************/
//Arithmetics
/********************************************/

//Add
void ADD(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //ADD
        case 0b001:
            debug("ADD", "ADD %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] += vm->registers[SR2(i)];
            break;
        case 0b010:
            debug("ADD", "IADD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] += prog_read(vm, vm->registers[PC]++);
            break;
        case 0b100:
            debug("ADD", "INC %s", name(SR1(i)));
            vm->registers[SR1(i)]++;
            break;
        default:
            perror("ADD - Unknown mode");
            exit(EXIT_FAILURE);
    }
    update_flag(vm, SR1(i));
}

//Subtract
void SUB(VM *vm, uint32_t i)
{
    //DEC
    if(MODE(i) >> 2)
    {
        debug("SUB", "DEC %s", name(SR1(i)));
        vm->registers[SR1(i)]--;
    }
    //ISUB
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("SUB", "ISUB %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] -= prog_read(vm, vm->registers[PC]++);
    }
    //SUB
    else if (MODE(i) & 0x1)
    {
        debug("SUB", "SUB %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] -= vm->registers[SR2(i)];
    }
    update_flag(vm, SR1(i));
}

//Multiply
void MUL(VM *vm, uint32_t i)
{
    //IMUL
    if((MODE(i) >> 1) & 0x1)
    {
        debug("MUL", "IMUL %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] *= prog_read(vm, vm->registers[PC]++);
    }
    //MUL
    else if (MODE(i) & 0x1)
    {
        debug("MUL", "MUL %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] *= vm->registers[SR2(i)];
    }
}

//Divide
void DIV(VM *vm, uint32_t i)
{
    //IDIV
    if((MODE(i) >> 1) & 0x1)
    {
        debug("DIV", "IDIV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] /= prog_read(vm, vm->registers[PC]++);
    }
    //DIV
    else if (MODE(i) & 0x1)
    {   
        debug("DIV", "DIV %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] /= vm->registers[SR2(i)];
    }

    update_flag(vm, SR1(i));
}

//Modulus
void MOD(VM *vm, uint32_t i)
{
    //IMOD
    if((MODE(i) >> 1) & 0x1)
    {
        debug("MOD", "IMOD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] %= prog_read(vm, vm->registers[PC]++);
    }
    else if(MODE(i) & 0x1)
    {
        debug("MOD", "MOD %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] %= vm->registers[SR2(i)];
    }

    update_flag(vm, SR1(i));
}

/********************************************/
// Bitwise
/********************************************/

// Shift
void SH(VM *vm, uint32_t i)
{
    // SHR
    if ((MODE(i) >> 1) & 0x1)
    {
        debug("SH", "SHR %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] >>= prog_read(vm, vm->registers[PC]++);
    }
    // SHL
    else if (MODE(i) & 0x1)
    {
        debug("SH", "SHL %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] <<= prog_read(vm, vm->registers[PC]++);
    }
}

void AND(VM *vm, uint32_t i)
{
    debug("AND", "AND %s %s", name(SR1(i)), name(SR2(i)));
    vm->registers[SR1(i)] &= vm->registers[SR2(i)];

    update_flag(vm, SR1(i));
}

void OR(VM *vm, uint32_t i)
{
    debug("OR", "OR %s %s", name(SR1(i)), name(SR2(i)));
    vm->registers[SR1(i)] |= vm->registers[SR2(i)];

    update_flag(vm, SR1(i));
}

void XOR(VM *vm, uint32_t i)
{
    debug("XOR", "XOR %s %s", name(SR1(i)), name(SR2(i)));
    vm->registers[SR1(i)] ^= vm->registers[SR2(i)];

    update_flag(vm, SR1(i));
}

void TEST(VM *vm, uint32_t i)
{
    debug("TEST", "TEST %s %s", name(SR1(i)), name(SR2(i)));
    update_flag_imm(vm, vm->registers[SR1(i)] & vm->registers[SR2(i)]);
}

void NOT(VM *vm, uint32_t i)
{
    debug("NOT", "NOT %s", name(SR1(i)));
    vm->registers[SR1(i)] = ~vm->registers[SR1(i)];

    update_flag(vm, vm->registers[SR1(i)]);
}

/********************************************/
// Control Flow
/********************************************/

//Compare
void CMP(VM *vm, uint32_t i)
{
    debug("CMP", "CMP %s %s", name(SR1(i)), name(SR2(i)));
    update_flag_imm(vm, vm->registers[SR1(i)] - vm->registers[SR2(i)]);
}

void JMP(VM *vm, uint32_t i)
{
    debug("JMP", "JMP %Xh", IMM16(i));
    vm->registers[PC] = IMM16(i);
}

void JUMP(VM *vm, uint32_t i)
{
    switch(MODE(i)){
        //JE
        case 0x0:
            debug("JUMP", "JE %Xh", IMM16(i));
            if(vm->registers[FLAG] & ZF)
                vm->registers[PC] = IMM16(i);
            break;
        //JNE
        case 0x1:
            debug("JUMP", "JNE %Xh", IMM16(i));
            if(!(vm->registers[FLAG] & ZF))
                vm->registers[PC] = IMM16(i);
            break;
        //JG
        case 0x2:
            debug("JUMP", "JG %Xh", IMM16(i));
            if(!(vm->registers[FLAG] & SF))
                vm->registers[PC] = IMM16(i);
            break;
        //JGE
        case 0x3:
            debug("JUMP", "JGE %Xh", IMM16(i));
            if(!(vm->registers[FLAG] - ZF))
                vm->registers[PC] = IMM16(i);
            break;
        //JL
        case 0x4:
            debug("JUMP", "JL %Xh", IMM16(i));
            if(vm->registers[FLAG] & SF)
                vm->registers[PC] = IMM16(i);
            break;
        //JLE
        case 0x5:
            debug("JUMP", "JLE %Xh", IMM16(i));
            if(vm->registers[FLAG] & (SF | ZF))
                vm->registers[PC] = IMM16(i);
            break;
        default:
            break;
    }
}

/********************************************/
// Stack
/********************************************/

void PUSH(VM *vm, uint32_t i)
{
    //IMM   
    if(MODE(i) & 0x1){

    }
}

void POP(VM *vm, uint32_t i){}

void CALL(VM *vm, uint32_t i){}

void RET(VM *vm, uint32_t i){}

/********************************************/
// Interrupt
/********************************************/

void INT(VM *vm, uint32_t i){}

op_ex_f op_ex[NOPS] = {
    MOV,
    STR,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    SH,
    AND,
    OR,
    XOR,
    TEST,
    NOT,
    CMP,
    JMP,
    JUMP
};