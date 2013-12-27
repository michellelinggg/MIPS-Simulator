#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/* WARNING: DO NOT CHANGE THIS FILE. 
 YOU SHOULD DEFINITELY CONSULT IT THOUGH... */

/* convenient(?) data definitions */
typedef uint8_t  Byte; /* unsigned, 8-bit */
typedef uint16_t Half; /* unsigned, 16-bit */
typedef uint32_t Word; /* unsigned, 32-bit */
typedef uint64_t Double; /* unsigned, 64-bit */

typedef int8_t  sByte; /* signed, 8-bit */
typedef int16_t sHalf; /* signed, 16-bit */
typedef int32_t sWord; /* signed, 32-bit */
typedef int64_t sDouble; /* signed, 64-bit */

/* A memory address */
typedef Word Address; /* unsigned, 32-bit */

/* A register value */
typedef Word Register; /* unsigned 32-bit*/

/* The processor data: 
    32 registers
    LO & HI special registers
    PC program counter */
typedef struct {
    Register R[32];
    Register RHI;
    Register RLO;
    Register PC;
} Processor;

/* Possible lengths of data, and their lengths in bytes.
 These are used to align memory*/
typedef enum {
    LENGTH_BYTE = 1,
    LENGTH_HALF_WORD = 2,
    LENGTH_WORD = 4,
} Alignment;

/* This is the length of the memory space */
#define MEMORY_SPACE (1024*1024) /* 1 MByte of Memory */

/* If you haven't seen a union before, go look it up.
   Seriously. They're fun. */
typedef union {
    
    /* access opcode with: instruction.opcode */
    struct {
        unsigned int : 26;
        unsigned int opcode : 6;
    };
    
    /* access rtype with: instruction.rtype.(opcode|rs|rt|rd|shamt|funct) */
    struct {
        unsigned int funct : 6;
        unsigned int shamt : 5;
        unsigned int rd : 5;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int opcode : 6;
    } rtype;
    
    /* access itype with: instruction.rtype.(oppcode|rs|rt|imm) */
    struct {
        unsigned int imm : 16;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int opcode : 6;
    } itype;
    
    /* access jtype with: instruction.rtype.(opcode|addr) */
    struct {
        unsigned int addr : 26;
        unsigned int opcode : 6;
    } jtype;
    
    /* basically ignore this stuff*/
    int16_t chunks16[2];
    uint32_t bits;
} Instruction;


#endif
