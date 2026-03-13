#ifndef ISA_H
#define ISA_H

#include <vector>
#include <cstdint>

/*=============================
        INSTRUCTION SET
=============================*/

enum InstructionSet {
    PSH,
    RPSH,
    ADD,
    POP,
    MTR,
    SET,
    LDR,
    STR,
    CAT,
    PREG,
    PEEK,
    MOV,
    BR,
    CBE,
    HLT
};

/*=============================
            REGISTERS
=============================*/

enum Registers {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I, 
    J, 
    K, 
    L, 
    M, 
    N, 
    O, 
    P,
    NUM_OF_REGISTERS
};

/*=============================
        INSTRUCTION OBJECT
=============================*/

struct Instruction {
    InstructionSet opcode;
    std::vector<int32_t> operands;

    Instruction(InstructionSet op) : opcode(op) {}

    Instruction(InstructionSet op, const std::vector<int32_t>& ops)
        : opcode(op), operands(ops) {}
};

#endif