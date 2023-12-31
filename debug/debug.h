#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdarg.h>

#define DEBUGGING 1

inline int __cdecl debug(const char *name, const char *_format, ...){
    int done = 0;
    
    if(DEBUGGING){
        va_list arg;

        printf("\033[0;35m(%s): ", name);

        va_start(arg, _format);
        done = vfprintf(stdout, _format, arg);
        va_end(arg);

        printf("\033[0m\n");
    }

    return done;
}

#endif