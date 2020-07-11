# OPCODES that the assembler supports

## Names and addressing types
1. MOV
    * Register
    * Immidiate
    * Dereference
    * Memory
2. ADD
    * Register
    * Immidiate
    * Dereference
    * Memory
3. SUB
    * Register
    * Immidiate
    * Dereference
    * Memory
4. CMP
    * Register
    * Immidiate
    * Dereference
    * Memory
5. RSH
    * Register
    * Immidiate
    * Dereference
    * Memory
6. CMPL
    * Register
    * Immidiate
    * Dereference
    * Memory
7. PUSH
    * Register
    * Immidiate
    * Dereference
    * Memory
8. POP
9. CALL
    * Memory
10. RET
11. JNE
    * Memory
12. JG
    * Memory
13. JGE
    * Memory
14. JL
    * Memory
15. JLE
    * Memory
16. JMP
    * Memory


## Mapping for functions
1.  MOV     : 0000
2.  ADD     : 0001
3.  SUB     : 0010
4.  CMP     : 0011
5.  RSH     : 0100
6.  CMPL    : 0101
7.  PUSH    : 0110
8.  POP     : 0111
9.  CALL    : 1000
10. RET     : 1001
11. JNE     : 1010
12. JG      : 1011
13. JGE     : 1100
14. JL      : 1101
15. JLE     : 1110
16. JMP     : 1111

## Mapping for Addressing Types:
1. Register         :   00
2. Immidiate        :   01
3. Dereference      :   10
4. Memory           :   11


## Mapping for Registers:
1. SP   : 000
2. A    : 001
3. B    : 010
4. C    : 011
5. D    : 100
6. MA   : 101
7. MB   : 110

## Opcode Format:
The Opcode will have 3 parts to them.
1. Bits 8-5 will have the function.
2. Bits 4-3 will have the Addressing Type of operand 1 (if exists, else 00)
3. Bits 2-1 will have the Addressing Type of operand 2 (if exists, else 00)

So, Opcode is divided into 3 categories

1. XXXXYYZZ AAAAAAAA BBBBBBBB, where XXXX is function, YY is addressing method of first operand(AAAAAAAA), and ZZ is addressing method of second operand(BBBBBBBB)

2. XXXXYY00 AAAAAAAA, where XXXX is the function, YY is the addressiing method of first operand(AAAAAAAA).

3. XXXX0000, where XXXX is the function.