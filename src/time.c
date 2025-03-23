// src/time.c
#include "time.h"

volatile tick_t ticks = 0; //Definition
uint32_t get_tick(void)
{
    unsigned long result;
    asm volatile ("push  %%es\n"
                  "mov   $0,%%bx\n"
                  "mov   %%bx,%%es\n"
                  "mov   $0x046C,%%bx\n"
                  "mov   %%es:(%%bx),%%eax\n"
                  "pop   %%es\n"
                  : "=a"(result)
                  : /* no inputs */
                  : "bx");
    return result;
}

uint32_t get_time(void)
{
    uint16_t high, low;
    asm volatile ("mov  $0x2C, %%ah\n"
                  "int  $0x21\n"
                  : "=c"(high), "=d"(low)
                  :
                  : "ah");
    return (((uint32_t) high) << 16) | (uint32_t)low; // Cast 'low' to uint32_t
}
