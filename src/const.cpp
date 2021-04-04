#include "const.h"

map<string, int> variables;
string OPERTEXT[] = {
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
    -2, -2,
    -1, -1,
    0,
    1,
    2,
    3,
    4,
    5,
    8, 8,
    6, 6,
    7, 7,
    9, 9,
    10, 10, 10
};
int NUMBER_OF_OPS = sizeof(PRIORITY) / sizeof(int);
