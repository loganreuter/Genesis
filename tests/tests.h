#ifndef TESTS_H
#define TESTS_H

#include "../src/genesis.h"
#include "helper.h"

typedef int (*test)();
int end();
FILE *out;

void section(char *title, test* tests);

void SECTION_TITLE(char *s);
void LOG_RESULTS(int pass_cnt, int test_cnt);

test memory_tests[];
test arithmetic_tests[];
test bitwise_tests[];
test control_flow_tests[];
test loop_tests[];
test interrupt_tests[];

#endif TESTS_H