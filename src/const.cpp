#include "const.h"

map<string, int> variables;
map<string, int*> arrays;
string OPERTEXT[] = {
    "[", "]",
    "array",
    "print",
    "if",
    "else", "endif",
    "while", "endwhile",
    "goto", ":",
    "(", ")",
    "=",
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
    "*", "/", "%"
};
int PRIORITY[] = {
    -8, -8,
    -7,
    -6,
    -5,
    -4, -4,
    -3, -3,
    -2, -2,
    -1, -1,
    0,
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
    11, 11, 11
};
int NUMBER_OF_OPS = sizeof(PRIORITY) / sizeof(int);
