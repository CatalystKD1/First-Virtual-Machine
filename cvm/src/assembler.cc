#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "assembler.h"

using namespace std;

unordered_map<string, InstructionSet> instructionMap = {
    {"PSH", PSH},
    {"RPSH", RPSH},
    {"ADD", ADD},
    {"POP", POP},
    {"MTR", MTR},
    {"SET", SET},
    {"LDR", LDR},
    {"STR", STR},
    {"CAT", CAT},
    {"PREG", PREG},
    {"PEEK", PEEK},
    {"MOV", MOV},
    {"BR", BR},
    {"CBE", CBE},
    {"HLT", HLT}
};

unordered_map<InstructionSet, vector<OperandType>> instructionSignature = {
    {PSH,  {INT}},
    {RPSH, {REG}},
    {ADD,  {}},
    {POP,  {}},
    {MTR,  {REG}},
    {SET,  {REG, INT}},
    {LDR,  {REG, INT}},
    {STR,  {REG, INT}},
    {CAT,  {INT}},
    {PREG, {REG}},
    {PEEK, {}},
    {MOV,  {REG, REG}},
    {BR,   {INT}},
    {CBE,  {REG, REG, INT}},
    {HLT,  {}}
};

unordered_map<string, Registers> registerMap = {
    {"A", A}, {"B", B}, {"C", C}, {"D", D},
    {"E", E}, {"F", F}, {"G", G}, {"H", H},
    {"I", I}, {"J", J}, {"K", K}, {"L", L},
    {"M", M}, {"N", N}, {"O", O}, {"P", P},
};

void parseLine(const string &line, vector<Instruction> &program) {

    stringstream ss(line);
    string instr;
    ss >> instr;

    if (instructionMap.count(instr) == 0)
        throw runtime_error("Unknown instruction: " + instr);

    InstructionSet opcode = instructionMap[instr];
    auto &signature = instructionSignature[opcode];

    vector<int32_t> operands;
    string token;

    for (size_t i = 0; i < signature.size(); i++) {

        if (!(ss >> token))
            throw runtime_error("Too few operands for instruction: " + instr);

        OperandType expected = signature[i];

        if (expected == REG) {
            if (!registerMap.count(token))
                throw runtime_error(instr + " expects register operand");
            operands.push_back(registerMap[token]);

        } else if (expected == INT) {

            try {
                operands.push_back(stoi(token));
            }
            catch (...) {
                throw runtime_error(instr + " expects integer operand");
            }
        }
    }

    if (ss >> token)
        throw runtime_error("Too many operands for instruction: " + instr);

    program.push_back(Instruction(opcode, operands));
}

vector<Instruction> assembleProgram(istream &input) {

    vector<Instruction> program;
    string line;

    while (getline(input, line)) {
        if (line.empty()) continue;
        parseLine(line, program);
    }

    return program;
}
