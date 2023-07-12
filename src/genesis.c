#include "genesis.h"

//Creates a new instance of the virtual machine
VM* createVM(){
    return (VM*)malloc(sizeof(VM));
}

//Update the flag register
void update_flag(VM *vm, enum regist r)
{
    vm->registers[FLAG] = 0;
    
    if (vm->registers[r] == 0)
        vm->registers[FLAG] = ZF;

    if (vm->registers[r] >> 31)
        vm->registers[FLAG] = SF;
}
//Update the flag register with an immediate value
void update_flag_imm(VM *vm, uint32_t val)
{
    vm->registers[FLAG] = 0;

    if(val == 0)
        vm->registers[FLAG] = ZF;
    
    if(val >> 31)
        vm->registers[FLAG] = SF;
}

//Read from program memory
uint32_t prog_read(VM *vm, uint16_t address){
    return vm->program[address];
}

//Read value from memory
uint8_t mem_read(VM *vm, uint16_t address){
    return vm->memory[address];
}
uint32_t mem_readn(VM *vm, uint16_t address, int size){
    uint32_t val = 0;
    for(int i = 0; i < size; i++){
        val |= (vm->memory[address + i] << (8*i));
    }
    return val;
}

//Write value to memory
void mem_write(VM *vm, uint16_t address, uint8_t val){
    vm->memory[address] = val;
}

//Clear all data in virtual machine
void clear(VM *vm){
    memset(vm->memory, 0, sizeof(vm->memory));
    memset(vm->program, 0, sizeof(vm->program));
    memset(vm->registers, 0, sizeof(vm->registers));
}

//Starts the virtual machine
void start(VM *vm, uint32_t *ops, uint32_t size){
    //loads instructions into memory
    for (uint32_t i = 0; i < size; i++){
        vm->program[i] = *(ops++);
    }

    vm->registers[PC] = 0x0;

    while (vm->registers[PC] < size){
        uint32_t i = prog_read(vm, vm->registers[PC]++);

        op_ex[OpCode(i)](vm, i);
    }
}