#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <vector>
#include <string>
#include "isa.h"

std::vector<Instruction> assembleProgram(std::istream &input);

enum OperandType {
    REG,
    INT
};

#endif