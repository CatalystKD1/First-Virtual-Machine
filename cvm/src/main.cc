#include <iostream>

using namespace std;

/*=============================
        GLOBAL VARIABLES
=============================*/

// Program Counter
int pc = 0;

bool running = true;

/*=============================
    INSTRUCTION DEFINITIONS
=============================*/

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

/*=============================
        BASIC PROGRAM
=============================*/
const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

/*=============================
        HELPER FUNCTIONS
=============================*/

// fetches the current instruction from PC
int fetch() {
    return program[pc];
}

// detect what instruction is being passed from PC
// Effect: Can modify running to be false (stop the program)
void eval(int instr) {
    switch (instr) {
        case HLT:
            running = false;
            break;
    }
}

int main() {
    // Effects: Modifies PC
    while (running) {
        eval(fetch());
        pc++;
    }
}