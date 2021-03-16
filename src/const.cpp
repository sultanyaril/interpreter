#include "const.h"

map<string, int> VAR;
string OPERTEXT[] = {
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
