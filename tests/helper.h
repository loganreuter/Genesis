#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>
#include <stdio.h>

#include "../src/genesis.h"

void ASSERT_EQ(uint32_t val, uint32_t check);

uint32_t MCRR(OPCODES op, uint8_t mode, enum regist r1, enum regist r2);

uint32_t MCR16(OPCODES op, uint8_t mode, enum regist r1, uint16_t val);

uint32_t MCR32(OPCODES op, uint8_t mode, enum regist r1);

uint32_t MCM32(OPCODES op, uint8_t mode, uint16_t addr);

#endif