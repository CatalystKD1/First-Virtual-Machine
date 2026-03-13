#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <cstdint>

using namespace std;
/*=============================
            OBJECTS
=============================*/
class Stack {
    int32_t sp; // stack pointer
    unordered_map<int32_t, int32_t> memory;

    void pushInternal(int32_t value);
    int32_t popInternal();

    // New functions
    int32_t loadInternal(int32_t mem);
    void storeInternal(int32_t value, int32_t mem);

    void checkAddress(int32_t addr);
    int32_t catInternal(int32_t mem);

    public:
        Stack();
        void push(int32_t value);
        int32_t pop();
        int32_t peek();
        bool isEmpty();

        int32_t load(int32_t mem);
        void store(int32_t value, int32_t mem);
        int32_t cat(int32_t mem);
};

/*=============================
        ENUM DEFINITIONS
=============================*/

typedef enum {
    PSH,
    RPSH, // push reg value to stack
    ADD,
    POP,
    PTR, // stands for Pop To Reg takes what is in pop_reg and puts it into a register
    SET,
    LDR,
    STR,
    CAT, // reads from memory
    PREG, // Peek at register
    PEEK,
    HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F,
    NUM_OF_REGISTERS
} Registers;


/*=============================
        GLOBAL VARIABLES
=============================*/

const int32_t MEMORY_LIMIT = 1024;

// Program Counter
uint32_t pc = 0;

int pop_full = false; //there is or is not somehting at pop_reg
int32_t pop_reg = 0;

bool running = true;

Stack stack;

int32_t registers[NUM_OF_REGISTERS];


/*=============================
        Constructor
=============================*/
Stack::Stack(): sp(-1), memory() {}

/*=============================
        Private Methods
=============================*/
// Effect: Adds elements to data and increments sp
void Stack::pushInternal(int32_t value) {
    sp++; // increment stack pointer
    memory[sp] = value;
}

// Effects: Removes elements from data and decrements sp
int32_t Stack::popInternal() {
    if(sp == -1) {
        throw std::runtime_error("Stack underflow");
    }
    int32_t value = memory[sp];
    memory.erase(sp);
    sp--; // decreases sp to "remove" top of stack
    return value;
}

void Stack::checkAddress(int32_t addr) {
    if (addr < 0 || addr > MEMORY_LIMIT) {
        throw runtime_error("Memory access out of bounds");
    }
}

// Effects: Changes value of register based on memory
int32_t Stack:: loadInternal(int32_t mem) {
    checkAddress(mem);

    if(memory.find(mem) == memory.end()) {
        throw runtime_error("Accessed garbage/uninitialized memory. Exiting program");
    }

    return cat(mem);
}

// Effects: Changes memory with the value stored at register reg
void Stack::storeInternal(int32_t value, int32_t mem) {
    checkAddress(mem);
    memory[mem] = value;
}

int32_t Stack::catInternal(int32_t mem) {
    return memory[mem];
}

/*=============================
        Public Methods
=============================*/

void Stack::push(int32_t value) {
    pushInternal(value);
}

// Effects: Calls the popInternal function and prints to stdout
int32_t Stack::pop() {
    return popInternal();
}

int32_t Stack::peek() {
    if (sp == -1) {
        throw std::runtime_error("Stack empty");
    }

    return memory[sp];
}

bool Stack::isEmpty() {
    return sp == -1;
}

int32_t Stack::load(int32_t mem) {
    return loadInternal(mem);
}

void Stack::store(int32_t value, int32_t mem) {
    storeInternal(value, mem);
}

int32_t Stack::cat(int32_t mem) {
    return catInternal(mem);
}

/*=============================
        BASIC PROGRAM
=============================*/
const int32_t program[] = {
    SET, A, 5,
    RPSH, A,
    PEEK,
    POP,
    PTR, B,
    PREG, B,
    HLT
};

uint32_t instruction_count = size(program);

/*=============================
        HELPER FUNCTIONS
=============================*/

// fetches the current instruction from PC
uint32_t fetch() {
    return program[pc];
}

// detect what instruction is being passed from PC
// Effect: Can modify running to be false (stop the program), write to stdout
void eval(uint32_t instr) {
    switch (instr) {
        case HLT: {
            running = false;
            #if DEBUG
            cout << "Program has halted" << endl;
            #endif
            break;
        } 
        case PSH: {
            pc++;
            stack.push(program[pc]);
            #if DEBUG
            cout << program[pc] << " was pushed ot the stack." << endl;
            #endif
            break;
        }
        case POP: {
            int32_t value = stack.pop();
            #if DEBUG
            cout << value << endl;
            pop_reg = value;
            #else
            pop_reg = value;
            #endif
            pop_full = true;
            break;
        }
        case ADD: {
            // first pop the stack and store is as a
            int32_t a = stack.pop();

            // then we pop the top of the stack and store it as b
            int32_t b = stack.pop();

            // we then add the result and push it to the stack
            stack.push(b + a);

            #if DEBUG
            cout << "added " << a << "+" << b << " and pushed it to the stack" << endl;
            #endif
            
            break;
        }
        // need to make sure users follow the strict way to implement an instruction
        // Make error handling code that make sure set is followed by a register, and then a value
        case SET: {
            pc++;
            // gets register from the program
            int32_t reg = program[pc];
            pc++;
            int32_t value = program[pc];
            registers[reg] = value;

            #if DEBUG
            cout << "Register " << reg << " has value " << value << endl;
            #endif

            break;
        }
        case LDR: { // format LDR, reg, mem
            pc++;
            int32_t reg = program[pc]; // gets reg from pc
            pc++;
            int32_t mem = program[pc]; // gets mem from pc
            registers[reg] = stack.load(mem);
            #if DEBUG
            cout << "Loaded value from memory address " << mem << " into register " << reg << endl;
            #endif
            break;
        }
        case STR: {
            pc++;
            int32_t reg = program[pc]; // gets reg from pc
            pc++;
            int32_t mem = program[pc]; // gets mem from pc
            stack.store(registers[reg], mem);

            #if DEBUG
            cout << "Stored value from register " << reg << " into memory address " << mem << endl;
            #endif
            break;
        }
        case PREG: {
            pc++;
            int reg = program[pc];
            cout << registers[reg] << endl;
            break;
        }
        case CAT: { // Format CAT, mem
            pc++;
            int mem = program[pc];
            cout << stack.cat(mem) << endl;
            break;
        }
        case PEEK: {
            cout << stack.peek() << endl;
            break;
        }
        case PTR: {
            if (pop_full) {
                pop_full = false;
                pc++;
                registers[program[pc]] = pop_reg;
            } else {
                throw std::runtime_error("Pop Register is empty");
            }
            #if DEBUG
            cout << "Moved value from Pop Register into a general purpose register" << endl;
            #endif
            break;
        }
        case RPSH: { // format RPSH, reg
            pc++;
            stack.push(registers[program[pc]]);

            #if DEBUG
            cout << "Pushed " << registers[program[pc]] << "to the stack from register " << program[pc] << endl;
            #endif
            
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