#ifndef CONST_H
#define CONST_H
using namespace std;
#include <map>
#include <string>

enum TYPE {
    OPER, VARIABLE, NUMBER
};

enum OPERATOR {
    GOTO, COLON,
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
extern map<string, int> variables;
extern string OPERTEXT[];
extern int PRIORITY[];
#endif
