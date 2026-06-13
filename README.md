# F+

This DSL is made in C and is stack based. If you choose the open source version you must have GCC to compile it and you will be able to see all the code. If you choose the compiled version you can use the Windows executable (x86-64) to run the programs made on this DSL. 
Example of use:
1,15,
1,16,
3, 
8,
1,17,
4,
8,
9
Would mean:
PUSH 15,
PUSH 16,
ADD, //15+16
PRINT, //31
PUSH 17,
SUB, //31-17
PRINT, //14
HLT
