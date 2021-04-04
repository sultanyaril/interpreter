#ifndef CONST_H
#define CONST_H
using namespace std;
#include <map>
#include <string>

enum TYPE {
    OPER, VARIABLE, NUMBER
};

enum OPERATOR {
    IF,
    ELSE, ENDIF,
    WHILE, ENDWHILE,
    GOTO, COLON,
    LBRACKET, RBRACKET,
    ASSIGN,
    OR,
    AND,
    BITOR,
    XOR,
    BITAND,
    SHL, SHR,
    EQ, NEQ, 
    LEQ, LT,
    GEQ, GT,
    PLUS, MINUS,
    MULTIPLY, DIV, MOD
};
extern int NUMBER_OF_OPS;
extern map<string, int> variables;
extern string OPERTEXT[];
extern int PRIORITY[];
#endif
