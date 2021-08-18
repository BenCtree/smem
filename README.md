# smem

A programmable stack machine emulator in c.

smem reads instructions from a stack program text file, creates an indexable instruction array containing these instructions and maintains an instruction pointer, then uses these to manipulate a virtual memory stack which stores integers.

It supports a simple instruction set with 8 different kinds of instructions:

- (integer): Pushes a positive integer from 0 to INT_MAX (+2,147,483,647) onto the stack

- DUP: Pushes another copy of the top element onto the stack

- ADD: Pops top two elements off stack, adds them together and pushes the result onto the stack

- SUB: Pops top two elements off stack, subtracts the first (top) from the second and pushes the result onto the stack

- SIZ: Pushes current stack size onto stack (eg If stack has four elements, will push 4 onto stack, and new stack size will be five elements)

- JGE: Pops top element i (jump index), second top element j (comparison value) and third top element k (counter) of the stack. If k is greater than or equal to j, jump to instruction in index i of the instruction array.

- JLE: Pops top element i (jump index), second top element j (comparison value) and third top element k (counter) of the stack. If k is less than or equal to j, jump to instruction in index i of the instruction array.

- JNE: Pops top element i (jump index), second top element j (comparison value) and third top element k (counter) of the stack. If k is not equal to j, jump to instruction in index i of the instruction array.

- (comment): Any line beginning with a ';' is treated as a comment and ignored (not added to instruction array or evaluated)

- Any blank line in the text file will also not be added to instruction array or evaluated

## Quick Start:

Clone the repo to your machine where gcc and make are installed, navigate to the project folder and type:

$ make

## To Run:

$ ./smem (stack_program.txt) (number of instructions)

## Examples:

There are two example stack programs included: eval_poly.txt, which evaluates a simple polynomial at a certain value and calc_mod.txt which calculates one number modulo another number.

You can try these by running:

$ ./smem eval_poly.txt 21

Evaluates 4x^2 at x = 3. This produces the result:

![eval_poly](eval_poly.png?raw=true "Eval Poly Example") 

And

$ ./smem calc_mod.txt 7

Calculates 21 mod 6. This produces the result:

![calc_mod](calc_mod.png?raw=true "Calc Mod Example") 

