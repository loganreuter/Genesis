#include "genesis.h"
#include "../debug/debug.h"

//Move
void MOV(VM *vm, uint32_t i)
{
    //Register-Memory
    if(MODE(i) >> 2)
    {
        debug("MOV", "MOV %s [%Xh]", name(SR1(i)), IMM16(i));
        vm->registers[SR1(i)] = IMM16(i);
    } 
    //Register-IMM32
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("MOV", "MOV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] = prog_read(vm, vm->registers[PC]++);
    }
    //Register-Register
    else if (MODE(i) & 0x1)
    {
        debug("MOV", "MOV %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR2(i)];
    }
}

//Store
void STR(VM *vm, uint32_t i)
{   
    //Memory-Register
    if(MODE(i) >> 2)
    {
        debug("STR", "STR [%Xh] %s", IMM16(i), SR1(i));
        for(uint16_t j = 0; j < 5; j++){
            mem_write(vm, IMM16(i) + j, ENCODE(vm->registers[SR1(i)], j));
        }
    }
    //Memory-IMM32
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("STR", "STR [%Xh] %Xh", IMM16(i), prog_read(vm, vm->registers[PC]));
        for(uint16_t j = 0; j < 5; j++){
            mem_write(vm, IMM16(i) + j, ENCODE(vm->registers[PC], j));
        }
        vm->registers[PC]++;
    }
    //Memory-Memory
    else if (MODE(i) & 0x1)
    {
        debug("STR", "STR [%Xh] [%Xh]", IMM16(i), prog_read(vm, vm->registers[PC]));
        mem_write(vm, IMM16(i), mem_read(vm, prog_read(vm, vm->registers[PC]++)));
    }
}

/********************************************/
//Arithmetics
/********************************************/

//Add
void ADD(VM *vm, uint32_t i)
{
    //INC
    if(MODE(i) >> 2)
    {
        debug("ADD", "INC %s", name(SR1(i)));
        vm->registers[SR1(i)]++;
    }
    //IADD
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("ADD", "IADD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] += prog_read(vm, vm->registers[PC]++);
    }
    //ADD
    else if (MODE(i) & 0x1)
    {
        debug("ADD", "ADD %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] += vm->registers[SR2(i)];
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

//Shift
void SH(VM *vm, uint32_t i)
{
    //SHR
    if((MODE(i) >> 1) & 0x1)
    {
        debug("SH", "SHR %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] >>= prog_read(vm, vm->registers[PC]++);
    } 
    //SHL
    else if(MODE(i) & 0x1)
    {
        debug("SH", "SHL %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
        vm->registers[SR1(i)] <<= prog_read(vm, vm->registers[PC]++);
    }
}

/********************************************/
// Logical
/********************************************/

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
    update_flag(vm, vm->registers[SR1(i)] & vm->registers[SR2(i)]);
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
    SUB
};