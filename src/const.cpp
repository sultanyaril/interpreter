#include <const.h>
map<string, int> variables;
map<string, int*> arrays;
map<string, Function> functions;
stack<int> global_stack;
string OPERTEXT[] = {
    "return",
    "function", "endfunction",
    "[", "]",
    "array",
    "print",
    "if",
    "else", "endif",
    "while", "endwhile",
    "goto", ":",
    "(", ")",
    "or",
    "and",
    "|",
    "^",
    "&",
    "<<", ">>",
    "==", "!=",
    "<=", "<",
    ">=", ">",
    "+", "-",
    "*", "/", "%",
    "="
};
int PRIORITY[] = {
    -10,
    -9, -9,
    -8, -8,
    -7,
    -6,
    -5,
    -4, -4,
    -3, -3,
    -2, -2,
    -1, -1,
    1,
    2,
    3,
    4,
    5,
    9, 9,
    6, 6,
    7, 7,
    8, 8,
    10, 10,
    11, 11, 11,
    0
};
int NUMBER_OF_OPS = sizeof(PRIORITY) / sizeof(int);
