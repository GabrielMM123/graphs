This is a program that generates a graph of a function f(x)\n
The first input that this code takes is the degree of the functions, and after this, their coefficients,\n
from an, an-1, an-2, ..., a0.\n
Example:\n
Input:\n
1\n
1 0 // graph of the function f(x) = x\n
Input:\n
2\n
1 -2 1 // graph of the function f(x) = x² -2x + 1\n
Input:\n
3\n
1 0 -3 0 // graph of the function f(x) = x³ - 3x\n
__________________________________________________________
There are still some room for optimization, and some parts of the code could be improved(since the anti-aliasing algorithm\n
isn't perfect, and for some higher degree functions, the program fails to draw lines)\n
