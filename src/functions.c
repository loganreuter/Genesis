#include "genesis.h"
#include "../debug/debug.h"

//Move
void MOV(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //Register-Register
        case 0x0:
            debug("MOV", "MOV %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] = vm->registers[SR2(i)];
            break;
        //Register-IMM32
        case 0x1:
            debug("MOV", "MOV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] = prog_read(vm, vm->registers[PC]++);
            break;
        //Register-Memory
        case 0x2:
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
        case 0x0:
            debug("STR", "STR [%Xh] [%Xh]", IMM16(i), prog_read(vm, vm->registers[PC]));
            mem_write(vm, IMM16(i), mem_read(vm, prog_read(vm, vm->registers[PC]++)));
            break;
        //Memory-IMM32
        case 0x1:
            debug("STR", "STR [%Xh] %Xh", IMM16(i), prog_read(vm, vm->registers[PC]));
            for (uint16_t j = 0; j < 5; j++)
            {
                mem_write(vm, IMM16(i) + j, ENCODE(prog_read(vm, vm->registers[PC]), j));
            }
            vm->registers[PC]++;
            break;
        //Memory-Register
        case 0x2:
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
        case 0x0:
            debug("ADD", "ADD %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] += vm->registers[SR2(i)];
            break;
        //IADD
        case 0x1:
            debug("ADD", "IADD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] += prog_read(vm, vm->registers[PC]++);
            break;
        //INC
        case 0x2:
            debug("ADD", "INC %s", name(SR1(i)));
            vm->registers[SR1(i)]++;
            break;
        default:
            perror("ADD - Unknown mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

//Subtract
void SUB(VM *vm, uint32_t i)
{
    switch(MODE(i)){
        //SUB
        case 0x0:
            debug("SUB", "SUB %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] -= vm->registers[SR2(i)];
            break;
        //ISUB
        case 0x1:
            debug("SUB", "ISUB %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] -= prog_read(vm, vm->registers[PC]++);
            break;
        //DEC
        case 0x2:
            debug("SUB", "DEC %s", name(SR1(i)));
            vm->registers[SR1(i)]--;
            break;
        default:
            perror("SUB - Unknown mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

//Multiply
void MUL(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {  
        //MUL
        case 0x0:
            debug("MUL", "MUL %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] *= vm->registers[SR2(i)];
            break;
        //IMUL
        case 0x1:
            debug("MUL", "IMUL %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] *= prog_read(vm, vm->registers[PC]++);
            break;
        default:
            perror("MUL - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

//Divide
void DIV(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //DIV
        case 0x0:
            debug("DIV", "DIV %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] /= vm->registers[SR2(i)];
            break;
        //IDIV
        case 0x1:
            debug("DIV", "IDIV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] /= prog_read(vm, vm->registers[PC]++);
            break;
        default:
            perror("DIV - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

//Modulus
void MOD(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //MOD
        case 0x0:
            debug("MOD", "MOD %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] %= vm->registers[SR2(i)];
            break;
        //IMOD
        case 0x1:
            debug("MOD", "IMOD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] %= prog_read(vm, vm->registers[PC]++);
            break;
        default:
            perror("MOD - Unknown Mode");
            exit(EXIT_FAILURE);
    }
    update_flag(vm, SR1(i));
}

/********************************************/
// Bitwise
/********************************************/

// Shift
void SH(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //SHR (register-register)
        case 0x0:
            debug("SH", "SHR %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] >>= vm->registers[SR2(i)];
            break;
        //SHR (register-IMM32)
        case 0x1:
            debug("SH", "SHR %s 0x%X", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] >>= prog_read(vm, vm->registers[PC]++);
            break;
        //SHL (register-register)
        case 0x2:
            debug("SH", "SHL %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] <<= prog_read(vm, vm->registers[PC]++);
            break;
        //SHL (register-IMM32)
        case 0x3:
            debug("SH", "SHL %s 0x%X", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] <<= prog_read(vm, vm->registers[PC]++);
            break;
        default:
            perror("SH - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

void AND(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //AND (register-register)
        case 0x0:
            debug("AND", "AND %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] &= vm->registers[SR2(i)];
            break;
        //AND (register-IMM32)
        case 0x1:
            debug("AND", "AND %s 0x%X", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] &= prog_read(vm, vm->program[PC]++);
            break;
        default:
            perror("AND - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

void OR(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //OR (register-register)
        case 0x0:
            debug("OR", "OR %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] |= vm->registers[SR2(i)];
            break;
        //OR (register-IMM32)
        case 0x1:
            debug("OR", "OR %s 0x%X", name(SR1(i)), prog_read(vm, vm->program[PC]));
            vm->registers[SR1(i)] |= prog_read(vm, vm->program[PC]++);
            break;
        default:
            perror("OR - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

void XOR(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //XOR (register)
        case 0x0:
            debug("XOR", "XOR %s %s", name(SR1(i)), name(SR2(i)));
            vm->registers[SR1(i)] ^= vm->registers[SR2(i)];
            break;
        //XOR (IMM32)
        case 0x1:
            debug("XOR", "XOR %s 0x%X", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            vm->registers[SR1(i)] ^= prog_read(vm, vm->registers[PC]++);
            break;
        default:
            perror("XOR - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, SR1(i));
}

void TEST(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //TEST (register-register)
        case 0x0:
            debug("TEST", "TEST %s %s", name(SR1(i)), name(SR2(i)));
            update_flag_imm(vm, vm->registers[SR1(i)] & vm->registers[SR2(i)]);
            break;
        //TEST (register-IMM32)
        case 0x1:
            debug("TEST", "TEST %s 0x%X", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            update_flag_imm(vm, vm->registers[SR1(i)] & prog_read(vm, vm->registers[PC]++));
            break;
        default:
            perror("TEST - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
}

void NOT(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //NOT (register)
        case 0x0:
            debug("NOT", "NOT %s", name(SR1(i)));
            vm->registers[SR1(i)] = ~vm->registers[SR1(i)];
            break;
        default:
            perror("NOT - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
    update_flag(vm, vm->registers[SR1(i)]);
}

/********************************************/
// Control Flow
/********************************************/

//Compare
void CMP(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //CMP (register-register)
        case 0x0:
            debug("CMP", "CMP %s %s", name(SR1(i)), name(SR2(i)));
            update_flag_imm(vm, vm->registers[SR1(i)] - vm->registers[SR2(i)]);
            break;
        //CMP (register-IMM32)
        case 0x1:
            debug("CMP", "CMP %s 0x%X", name(SR1(i)), prog_read(vm, vm->registers[PC]));
            update_flag_imm(vm, vm->registers[SR1(i)] - prog_read(vm, vm->registers[PC]++));
            break;
        default:
            perror("CMP - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
}

void JMP(VM *vm, uint32_t i)
{
    switch (MODE(i))
    {
        //JMP
        case 0x0:
            debug("JMP", "JMP %Xh", IMM16(i));
            vm->registers[PC] = IMM16(i);
            break;
        // JE
        case 0x1:
            debug("JMP", "JE %Xh", IMM16(i));
            if (vm->registers[FLAG] & ZF)
                vm->registers[PC] = IMM16(i);
            break;
        // JNE
        case 0x2:
            debug("JMP", "JNE %Xh", IMM16(i));
            if (!(vm->registers[FLAG] & ZF))
                vm->registers[PC] = IMM16(i);
            break;
        // JG
        case 0x3:
            debug("JMP", "JG %Xh", IMM16(i));
            if (!(vm->registers[FLAG] & SF))
                vm->registers[PC] = IMM16(i);
            break;
        // JGE
        case 0x4:
            debug("JMP", "JGE %Xh", IMM16(i));
            if (!(vm->registers[FLAG] & SF) || vm->registers[FLAG] & ZF)
                vm->registers[PC] = IMM16(i);
            break;
        // JL
        case 0x5:
            debug("JMP", "JL %Xh", IMM16(i));
            if (vm->registers[FLAG] & SF)
                vm->registers[PC] = IMM16(i);
            break;
        // JLE
        case 0x6:
            debug("JMP", "JLE %Xh", IMM16(i));
            if (vm->registers[FLAG] & (SF | ZF))
                vm->registers[PC] = IMM16(i);
            break;
        default:
            perror("JMP - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
}

/********************************************/
// Stack
/********************************************/

void PUSH(VM *vm, uint32_t i)
{
    switch(MODE(i))
    {
        //PUSH (register)
        case 0x0:
            debug("PUSH", "PUSH %s", name(SR1(i)));
            vm->registers[ESP] -= 4;
            for(uint16_t j = 0; j < 4; j++)
            {
                mem_write(vm, vm->registers[ESP] - j, ENCODE(vm->registers[EAX], j));
            }
            break;
        //PUSH (IMM32)
        case 0x1:
            debug("PUSH", "PUSH 0x%X", prog_read(vm, vm->registers[PC]));
            vm->registers[ESP] -= 4;
            uint32_t val = prog_read(vm, vm->registers[PC]++);
            for (uint16_t j = 0; j < 4; j++)
            {
                mem_write(vm, vm->registers[ESP] - j, ENCODE(val, j));
            }
            break;
        default:
            perror("PUSH - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
}

void POP(VM *vm, uint32_t i)
{
    switch(MODE(i))
    { 
        //POP (register)
        case 0x0:
            debug("POP", "POP %s", name(SR1(i)));
            vm->registers[SR1(i)] = mem_readn(vm, vm->registers[ESP], 4);
            vm->registers[ESP] += 4;
            break;
        default:
            perror("POP - Unknown Mode");
            exit(EXIT_FAILURE);
            break;
    }
}

void CALL(VM *vm, uint32_t i){}

void RET(VM *vm, uint32_t i){}

/********************************************/
// Interrupt
/********************************************/

void INT(VM *vm, uint32_t i)
{
    debug("INT", "INT x%X", IMM16(i));
    switch (IMM16(i))
    {
    case 0x0:
        break;
    case 0x1:
        break;
    case 0x2:
        break;
    //Print Character
    case 0x10:
        char c = vm->registers[EAX];
        fputc(c, stdout);
        break;
    default:
        perror("INT - Unknown Interrupt");
        exit(EXIT_FAILURE);
        break;
    }
}

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
    PUSH,
    POP,
    CALL,
    RET,
    INT
};