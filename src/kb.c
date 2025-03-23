// src/kb.c
#include "kb.h"

int kbhit(void) {
    uint16_t result;
      asm volatile (
        "mov $0x01, %%ah\n"
        "int $0x16\n"
        "jz no_key\n"
        "mov $1, %0\n"
        "jmp end\n"
        "no_key:\n"
        "mov $0, %0\n"
        "end:\n"
        : "=r" (result)
        :
        : "ax", "cc" // Clobber ax and condition codes
    );
    return result;
}
int getch(void)
{
    uint16_t ch;
    asm volatile (
        "xor %%ah, %%ah\n"
        "int $0x16\n"
        :"=a"(ch)
    );
    return ch;
}
