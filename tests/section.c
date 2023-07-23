#include "tests.h"

void section(char *title, test *tests)
{
    SECTION_TITLE(title);

    int ret = 0; 
    int test_cnt = 0;
    int pass_cnt = 0;
    for(;;)
    {
        ret = tests[test_cnt]();
        if (ret == -1)
            break;
        
        pass_cnt += ret;
        test_cnt++;
    }

    LOG_RESULTS(pass_cnt, test_cnt);
}

void SECTION_TITLE(char *s)
{
    fprintf(out, "\n\n\n*********************\n%s\n*********************\n", s);
}

void LOG_RESULTS(int pass_cnt, int test_cnt)
{
    fputs("\nResults:\n", out);
    fprintf(out, "%d of %d passed\n", pass_cnt, test_cnt);
    if (pass_cnt == test_cnt)
        fputs("\033[32mALL PASSED\033[0m", out);
}

int end() { return -1; }