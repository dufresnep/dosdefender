#ifndef INIT_H
#define INIT_H

/* NOTICE: This must be included first! */
asm (".code16gcc\n"
     "call  dosmain\n"
     "mov   $0x4C,%ah\n"
     "int   $0x21\n");

#endif
