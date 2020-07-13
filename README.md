# COAproject
## Project Details
This project implements a custom made architecture, with 8 bit fixed length instruction set, and is included with an assembler and simulator for the architecure.

With the help of this project, we are showing how divide and conquor algorithms work, by implementing `MergeSort` algorithm in assembly language, and then executing it on a simulator.

## How to use
The project works on a linux pc(maybe on windows too, if you have make and gcc in your shell).  

To compile binaries, just write `make` in the terminal, and it should compile binaries into the `bin` folder.

The assmebly code for `MergeSort` algorithm is kept in `data` folder.  
To assemble the code, type `make Assemble` into terminal and hit enter.  
This will generate symbol table and binFile in `data` folder.  

To simulate the program, enter `make Simulate` in terminal.  
This will simulate the program, and will generate `opFile` in data folder, which holds the variables after execution of each line, and `ramDump` file, which holds the values of each word of ram after completition of execution.  

To show the parsed version of ram dump of the simulator after execution, enter `make RamDump`.  
This will make a file ramDump.parsed, which will hold the token(word) number, the binary value corresponding to that memory location and its encoding in base10.

## Architecture Details
The architecture that we implemented is an 8-bit fixed length instruction set architecture. It contains 16 Opcodes, with many of them supporting 4 addressing modes each.  
The architecture has 1024 bytes of 1-byte-word addressable memory.  
The instruction set has 16 Opcode Functions and 4 Addressing modes.  
The Opcode is divided into 3 parts, namely function, p0, and p1  

**7 6 5 4 3 2 1 0**  
**X X X X Y Y Z Z**

#### Breakdown of Opcode Syntax
* Bits 7-4 holds the function value, i.e. the value that determines the function to be used, for eg, MOV, JMP etc.

* Bits 3-2 Holds the parameter p0, which determines the addressing mode of first arguement(if exists). In case the instruction does'nt take any arguements, like `RET`, or `POP`, we can put any garbage value in these 2 bits, as they are ignored completely. In our case, we initialise these 2 bits with 0.

* Bits 1-0 Holds the parameter p1, which determines the addressing mode of second arguement(if exists). In case the instruction does'nt take tow arguements, like `JMP`, or `CALL`, we can put any garbage value in these 2 bits, as they are ignored completely. In our case, we initialise these 2 bits with 0.  
This field serves another special purpose. Since with a bus length of 8 bit, we can address only 256 bytes of memory, in case of jump instructions or call instructions, which mainly deals in memory, and location of PC, these two bits can be used to pack two more bytes of data. It is because we know that these instructions only take one parameter. So, these two bits will be skipped by opcode parser. But, By using these 2 bits as the 2 MSBs of next field (which contains an address), we can extend the range of addressable memory from 256 bytes to 1024 bytes.

#### Addressing Modes
The architecture supports 4 addressing modes, namely
* Register addressing mode
    * This addressing mode specifies that the arguement is going to be a register.
* Immidiate addressing mode
    * This addressing mode specifies that the arguement is a constant number / Immidiate value.
* Dereference addressing mode
    * This is somewhat similar to the concept of pointers in C. This addressing mode means that the value held by the parameter is a memory address, and the data to be used by this mode is the data that is pointed by the memory location.
* Memory addressing mode
    * This addressing modes specifies that the arguement is a memory location, or a variable that holds a memory address. The data used by this mode is the address itself.

## Binary encoding of Opcodes and Addressing Modes

#### Opcodes:
Opcodes have a 4-bit memory encoding to their mnemonics. This leads to having a total of 16 Mnemonics for functions. The mapping to the mnemonics and binary encoding is as follows:
1.  `MOV    : 0b0000`
2.  `ADD    : 0b0001`
3.  `SUB    : 0b0010`
4.  `CMP    : 0b0011`
5.  `RSH    : 0b0100`
6.  `CMPL   : 0b0101`
7.  `PUSH   : 0b0110`
8.  `POP    : 0b0111`
9.  `MCP    : 0b1000`
10. `CALL   : 0b1001`
11. `RET    : 0b1010`
12. `JG     : 0b1011`
13. `JGE    : 0b1100`
14. `JL     : 0b1101`
15. `JLE    : 0b1110`
16. `JMP    : 0b1111`

#### Addressing Modes
The addressing mode is mapped by a bit-field of width 2. The mapping is as followds

1. Register     :   00
2. Immidiate    :   01
3. Dereference  :   10 
4. Memory       :   11

#### Registers
There are 6 registers in our architecture, and a special register Stack Pointer, which holds the current position of the stack, totalling to 7 registers, which can be fitted into a bit-field of width 3.

1. SP
    * Stack Pointer, it is used to keep the cuurent position of the stack memory This is initialised at last positon of the memory, i.e. `memory[1023]`.
    * Its binary encoding is `0b00`

2. registerA
    * Accumulator register is a register used by functions like `CMP` to store results.
    * Its binary encoding is `0b001`

3. registerB
    * Register B is a general purpose register.
    * Its binary encoding is `0b010'

4. RegisterC
    * Register C is a general purpose register.
    * Its binary encoding is `0b011'

5. RegisterD
    * Register D is a general purpose register.
    * Its binary encoding is `0b011'

6. RegisterMA
    * Register MA is a special type of regiser which is mainly designated to use for memory operations like `MCP` etc.  
    * This register can be thought of as a hybrid of a memory location and a register.
    * Its binary encoding is '0b101'

7. RegisterMB
    * Register MB is a special type of regiser which is mainly designated to use for memory operations like `MCP` etc.  
    * This register can be thought of as a hybrid of a memory location and a register.
    * Its binary encoding is '0b110'


## Explanations of the instructions

#### Opcode

1. `MOV` instruction takes two arguements, and copies the data given by second parameter(source) to the first parameter(destination)

2. `ADD` instruction takes two arguements, and takes the data given by second parameter, and adds it to the first parameter, with result storing in the first parameter.

3. `SUB` instruction takes two arguements, and takes the data given by second parameter, and subtract it from the first parameter, with result storing in the first parameter..
4.  `CMP` instruction takes two parameters, and performs subtraction of second parameter from first parameter, and stores the value in the accumulator. This is mainly done so, because, if value in accumulator is negative, then first parameter is smaller than second parameter. Else if value is positive, then it means that the second parameter is smaller than first parameter. If the value is zero, then it means both are equal. 

5.  `RSH` instruction takes two parameters, and performs logical bitshift of first parameter towards right direction, by the value of second parameter.

6.  `CMPL` instruction takes one parameter, and computes its complements and stores it in iteself.

7.  `PUSH` instruction takes one parameter, and pushes it onto the stack, and then decreases the location of stack by 1.

8.  `POP` instruction increases the location of stack by 1.

9.  `MCP` instruction, or MemoryCopy instruction takes two parameres, and stores the memory location of second parameter as the value of first parameter.

10. `CALL` instruciont takes one parameter, the address to function we are calling. This instruction pushes the current PC onto the stack, changes PC to the address of the given memroy location and then decreases the location of stack by 1.

11. `RET` instructions sets the PC to the value located on the top of the stack, and then increases the location of stack by 1.

12. `JG`  instruction takes a memory as a parameter, and changes the PC if the value stored in accumulator is greater than 0.

13. `JGE` instruction takes a memory as a parameter, and changes the PC if the value stored in accumulator is greater than or equal to 0.

14. `JL`  instruction takes a memory as a parameter, and changes the PC if the value stored in accumulator is less than 0.

15. `JLE` instruction takes a memory as a parameter, and changes the PC if the value stored in accumulator is less than or equal to 0.

16. `JMP` instruction takes a memory as a parameter, and unconditonally changes the PC to the memroy location of the prameter.

#### Literals   
Our assembly language only supports integers as literals, and we can use an integer literal by using a `$` sign before the integer. For eg. in  
`ADD C $5`  
`$5` is a literal, and is value 5.

#### Labels
Our asssembly language understands labels and they can be used as a reference for jumps or calls to functions. For eg.   
`MOV B $1`  
`LOOP:`  
`ADD B $1`  
`CMP B $5`  
`JL LOOP`  
`LOOP1:` 
`SUB B $1` 
`CMP B $3`
`JL OUT`  
`OUT:`  
`RET`  
is a valid set of instructions.
#### Directives
Our assembly understands .data directive, followed by a label, which allocates a memory and assigns the data following the label to that location. This can also be extended by chaining multiple literals by commas, as   
`.data someLabel 3,2,5 `  
If the pc during this instruction is at 100 (say), then this instruction will allocate locations 100, 101 and 102 assigns them values 3, 2, and 5 respectively.

## Authors
Students of National Instutute of Technology, Hamipur, Himachal Pradesh, India
* **Moulik, Roll No. 185506**
* **Swayam Kaul, Roll No. 185512**
* **Rishabh Deknawat, Roll No. 185519**  