# LowCode
A simple procedural programming language

## Format of commands:
+ [INSTRUCTION] [REGISTER TO EDIT] [VALUE]  
<VALUE> may be optional in commands  
  
+ OUT -> OUT [VALUE OR REGISTER]  
  
+ EXIT -> EXIT [VALUE]  
<VALUE> either 0 or 1  


## Registers:  
There are total 8 registers in memory namely  
i0 ... i7 for integers  
d0 ... d7 for doubles  
f0 ... f7 for floats  
  
Note: request for any other register will lead to
termination of program with error `NOREG`

## Values:  
Values can be floating point or integers
but must follow the rules of certain commands

## Instructions:
|Name|Definition|Errors thrown|
|----|----------|-------------|
|REG|Registers a value in memory|NOREG, BADVAL|
|IN|Refers to stdin and is used to take input from user and store a particular value in a register|NOREG, BADIN|
|OUT|Refers to stdout and is used to take value from a register or raw value and print it in stdout|```null```|
|ADD|Takes a register and a value to add to the register|```null```|
|SUB|Same as ADD but subtracts value|```null```|
|MULT|Same as ADD but multiplies value|```null```|
|DIV|Same as ADD but divides value|DIV0 -> If value = 0 terminates program and writes `DIV0` error in stdout|
|EXIT|Used to exit from code, the only command to take a value 0 or 1 but no register|BADEXIT -> Anything else leads to `BADEXIT` with line number printed|

## Comment:
LowCode only supports `;` as single line comments

~ By Rouvik Maji 14/12/2021