#ifndef CONST_H
#define CONST_H
using namespace std;
#include <map>
#include <string>

enum OPERATOR {
    LBRACKET, RBRACKET,
    ASSIGN,
    OR,
    AND,
    BITOR,
    XOR,
    BITAND,
    EQ, NEQ,
    LEQ, LT,
    GEQ, GT,
    SHL, SHR,
    PLUS, MINUS,
    MULTIPLY, DIV, MOD
};
extern int NUMBER_OF_OPS;
extern map<string, int> VAR;
extern string OPERTEXT[];
extern int PRIORITY[];
#endif
