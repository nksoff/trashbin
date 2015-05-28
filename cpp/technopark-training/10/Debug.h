#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <ctime>

#ifndef DEBUG_H
#define DEBUG_H

#ifndef DEBUG
#define DEBUG 0
#endif

inline void debug(int level, const char *fmt, ...)
{
    if(level > DEBUG) return;

    time_t t;
    time(&t);
    tm *tinfo = localtime(&t);
    char fileName[100], dateTime[20];
    strftime(fileName, 100, "debug-%Y-%m-%d-%H.txt", tinfo);
    strftime(dateTime, 20, "[%T] ", tinfo);

    FILE *file = fopen(fileName, "a+");
    
    va_list args;
    va_start(args, fmt);
    fprintf(file, "%s", dateTime);
    vfprintf(file, fmt, args);
    fprintf(file, "\n");
    va_end(args);

    fclose(file);
}
#endif