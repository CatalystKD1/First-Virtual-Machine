#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

/*=============================
            OBJECTS
=============================*/
class Stack {
    int sp; // stack pointer
    vector<int> data; // the stack

    void pushInternal(int value);
    int popInternal();

    // New functions
    public:
        Stack();
        void push(int value);
        int pop();
        int peek();
        bool isEmpty();
};

Stack::Stack(): sp(-1), data() {}

// Effect: Adds elements to data and increments sp
void Stack::pushInternal(int value) {
    sp++; // increment stack pointer
    data.push_back(value);
}

// Effects: Removes elements from data and decrements sp
int Stack::popInternal() {
    if(sp == -1) {
        throw std::runtime_error("Stack underflow");
    }
    // gets last element from array
    int value = data.back();
    // decrement sp
    sp--;
    // removes last element from the vector
    data.pop_back();
    return value;
}

void Stack::push(int value) {
    pushInternal(value);
}

// Effects: Calls the popInternal function and prints to stdout
int Stack::pop() {
    return popInternal();
}

int Stack::peek() {
    if (sp == -1) {
        throw std::runtime_error("Stack empty");
    }

    return data[sp];
}

bool Stack::isEmpty() {
    return sp == -1;
}

/*=============================
        ENUM DEFINITIONS
=============================*/

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F,
    NUM_OF_REGISTERS
} Registers;

/*=============================
        GLOBAL VARIABLES
=============================*/

// Program Counter
int pc = 0;

bool running = true;

Stack stack = Stack();

int registers[NUM_OF_REGISTERS];

/*=============================
        BASIC PROGRAM
=============================*/
const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    SET, A, 4,
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
        case HLT: {
            running = false;
            break;
        } 
        case PSH: {
            pc++;
            stack.push(program[pc]);
            break;
        }
        case POP: {
            cout << stack.pop() << endl;
            break;
        }
        case ADD: {
            // first pop the stack and store is as a
            int a = stack.pop();

            // then we pop the top of the stack and store it as b
            int b = stack.pop();

            // we then add the result and push it to the stack
            stack.push(b + a);
            
            break;
        }
        // need to make sure users follow the strict way to implement an instruction
        // Make error handling code that make sure set is followed by a register, and then a value
        case SET: {
            pc++;
            // gets register from the program
            int reg = program[pc];
            pc++;
            int value = program[pc];
            registers[reg] = value;
            cout << "Register " << reg << " has value " << value << endl;
            break;
        }
    }
}

int main() {
    // Effects: Modifies PC
    while (running) {
        eval(fetch());
        pc++;
    }
}