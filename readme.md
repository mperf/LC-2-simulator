# LC-2 Simulator

Assembly LC-2 cli simulator written in C, Lex and Yacc.

## Compatibility

- Linux
- MacOS

## Installation

1. First, You need to install Flex (lexical analyzer) and Yacc. Use brew if You are in MacOS.
   
```C
sudo apt install flex \
sudo apt install bison
```

2. clone this repo
3. launch the `make` command

## Usage
`./lc2 code.asm [-e]|[-s]`

- -e: executes the entire program and prints all registers
- -s: steps to every instruction in ~=1000 ms
- no options: press enter for next instruction
  
### during execution without options

press `r` to print the registers:

```
  x3001   AND     R2      R2      #0
x3002   LOOP   LDR     R1      R0      #0
x3003   BRZ     END
> r
R0=12297        R1=15   R2=0    R3=0
R4=0    R5=0    R6=0    R7=0
CC=P    PC=12291 (x3003)

> 
```

## Missing parts

TRAP instructions are not yet implemented. LOAD & STORE functions work perfectly, You just can't see them in the memory.