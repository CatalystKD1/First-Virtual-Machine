# General purpose Registers
A, B, C, D, E and F

# Commands
```
PSH 5       ; pushes 5 to the stack
PSH 10      ; pushes 10 to the stack
ADD         ; pop two values on top of the stack, add them and pushes to stack
POP         ; pops the value on the stack, will also print it for debugging
SET A 0     ; sets register A to 0
HLT         ; stop the program
```

# Extra Idea
### Create a new branch
Implement a STR to store value of register to the stack

Implement LDR to load value from stack to a register

Implement a MOV A, B to move the content from register A into register B

Implement branching (use PC to increment the program)

Read instructions from the stdin instead of a program array (so people can make programs)


# Instruction cycle
Fetch; Decode; Execute

# Directories
C Virtual Machine (cvm)
----> src