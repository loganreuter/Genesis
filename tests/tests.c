#include "tests.h"

int main()
{
    out = stdout;
    section("Memory Tests", memory_tests);
    section("Arithmetic Tests", arithmetic_tests);
    section("Bitwise Tests", bitwise_tests);
    section("Control Flow Tests", control_flow_tests);
    section("Loop Tests", loop_tests);
    section("Interrupt Tests", interrupt_tests);

    // for_loop_test();

    return 0;
}