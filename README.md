# LowCode
A simple procedural programming language

## Format of commands:
+ \<INSTRUCTION\> \<REGISTER TO EDIT\> \<VALUE\>  
\<VALUE\> may be optional in commands  
  
+ OUT -> OUT \<VALUE OR REGISTER\>  
  
+ EXIT -> EXIT \<VALUE\>  
\<VALUE\> either 0 or 1  


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
|REG|Registers a value in memory|[NOREG](#noreg), [BADVAL](#badval)|
|IN|Refers to stdin and is used to take input from user and store a particular value in a register|[NOREG](#noreg), [BADIN](#badin)|
|OUT|Refers to stdout and is used to take value from a register or raw value and print it in stdout|```null```|
|ADD|Takes a register and a value to add to the register|```null```|
|SUB|Same as ADD but subtracts value|```null```|
|MULT|Same as ADD but multiplies value|```null```|
|DIV|Same as ADD but divides value|[DIV0](#div0)|
|EXIT|Used to exit from code, the only command to take a value 0 or 1 but no register|[BADEXIT](#badexit)|
|IFGT|Run the next line only if the value 1 greater than value 2|[NOREG](#noreg)|
|IFLT|Run the next line only if the value 1 less than value 2|[NOREG](#noreg)|
|IFEQ|Run the next line only if the value 1 equal to value 2|[NOREG](#noreg)|
|IFLE|Run next line if the value 1 <= value 2|[NOREG](#noreg)|
|IFGE|Run next line if the value 1 >= value 2|[NOREG](#noreg)|
|JMP|Jumps to a particular line number, can take both registers and raw number|[NOREG](#noreg)|

## Errors:
### BADEXIT
Thrown when program exits with exit code 1  
ie, there is some error in program  

### BADIN
Thrown when illegal input is passed  
ie, [a-z, A-Z or any other ascii character except 0-9]  

### NOREG
Thrown when the requested reguster doensnot exists  

### BADVAL
Thrown when the value in code is not a number  
Example: reg i0 ```hello```  
Here ```hello``` is not a number  

### DIV0
Thrown when program wants to divide a number by 0  

## Comment:
LowCode only supports `;` as single line comments

# Installation:
+ First download the files using git clone "repourl"
+ make a new directory
+ run cmake in the new directory with path to download directory
+ run ./lowcc to run the program
+ you may even add the build path to environment variable PATH to make it a system command and then run it as lowcc

~ By Rouvik Maji 14/12/2021
