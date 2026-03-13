# Stack Virtual Machine

A lightweight **stack-based virtual machine (VM)** written in C++.  
This project implements a simple assembly-like instruction set that operates on a stack, registers, and memory.

The goal of this project is to explore low-level computer architecture concepts such as:

- stack-based execution
- instruction set design
- virtual machine implementation
- assembly parsing and execution

Programs written for this VM consist of a sequence of instructions that manipulate registers, memory, and the stack.

---

# Features

Current features of the VM include:

- **Stack-based execution model**
- **16 general-purpose registers**
- **15 basic instructions**
- **Memory load and store operations**
- **Basic arithmetic operations**
- **Conditional and unconditional branching**
- **Debugging utilities for inspecting stack, registers, and memory**
- **Type checking assembler**
- **Debugging feature for all instructions**

# General purpose Registers

A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P

# Commands

```
PSH int             ; pushes int to the stack
RPSH reg            ; pushes content of register reg to the stack
ADD                 ; pop two values on top of the stack, add them and pushes to stack
POP                 ; pops the value on the stack, puts this value into a special purpose register, will also print it for debugging
MTR reg             ; If there is a value in the special purpose register for popping, move it into register reg
SET reg int         ; sets register reg to int
LDR reg int         ; load a value from memory address into a register
STR reg int         ; stores a value from a register into memory
CAT int             ; prints the value stored at memory address int
PREG reg            ; prints the value stored at reg
PEEK                ; prints the value at the top of the stack
MOV reg1 reg2       ; sets reg2 to be the value stored at reg1
BR int              ; unconditional branch, sets pc to pc = pc + int
CBE reg1 reg 2 int  ; conditional branch equals, if true, set pc to pc = pc + int
HLT                 ; stop the program
```

# Features to implement

## Commands

```
ADDR reg1 reg2 reg3 ; computes reg1 = reg2 + reg3
SUBR reg1 reg2 reg3 ; computes reg1 = reg2 - reg3
MLT                 ; computes second element in stack * tops of stack
MLTR reg1 reg2 reg3 ; computes reg1 = reg2 * reg3
DIV                 ; computes second element in stack / tops of stack
DIVR reg1 reg2 reg3 ; computes reg1 = reg2 / reg3
READ                ; reads an integer from stdin
```

## Features

- Add a **compiler flag** to convert printed numeric values into ASCII characters (allowing string output)
- Support **labels** for branching instead of manual offsets
- Add **jump instructions and register-based jumps** to better mimic traditional assembly languages

## Planned Features

- Add a **compiler flag** to convert printed numeric values into ASCII characters (allowing string output)
- Support **labels** for branching instead of manual offsets
- Add **jump instructions and register-based jumps** to better mimic traditional assembly languages
- Allow users to write comments in their code

---

# Dependencies

To build and run this project you will need:

- **g++** (C++17 or later recommended)
- **make**
- A Unix-like environment (Linux/macOS recommended, however I am using a WSL environment)

Typical installation commands:

```bash
sudo apt install g++ make
```

# Building the Project

Clone the repository using:
```bash
git clone https://github.com/CatalystKD1/First-Virtual-Machine.git
cd First-Virtual-Machine/svm/src
```
Then you can build the Virtual Machine using the Makefile
```bash
make
```

# Running the VM

Once compiled, you can run the VM with an input program file. There is a directory with example programs that you can copy.
One example is the sum.asm program, which will compute the sum from 0 to Reg A.
```
./svm sum.asm
```

# Author

** Jordan McCrank**
Computer Science Student interested in
- Software Development
- Systems programming
- Compilers and virtual machines

## Socials
* [Personal Portfolio](https://catalystkd1.github.io/JordanMcCrankPortfolio/)
* [LinkedIn Profile](https://www.linkedin.com/in/jordan-mccrank-b6a08a290/)
* [GitHub Progile](https://github.com/CatalystKD1)
