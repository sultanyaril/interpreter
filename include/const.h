#ifndef CONST_H
#define CONST_H
using namespace std;
#include <map>
#include <string>
#include <stack>
enum TYPE {
    OPER, VARIABLE, NUMBER
};

enum OPERATOR {
    RETURN,
    FUNCTION, ENDFUNCTION,
    LSQRBRACKET, RSQRBRACKET,
    ARRAY,
    PRINT,
    IF,
    ELSE, ENDIF,
    WHILE, ENDWHILE,
    GOTO, COLON,
    LBRACKET, RBRACKET,
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
    MULTIPLY, DIV, MOD,
    ASSIGN
};
struct Space {
    map<string, int> variables;
    map<string, int*> arrays;
};

struct Function {
    int row_to_jump;
    int number_of_args;
};
extern int NUMBER_OF_OPS;
extern map<string, int> variables;
extern map<string, int*> arrays;
extern map<string, Function> functions;
extern stack<int> global_stack;
extern string OPERTEXT[];
extern int PRIORITY[];
#endif
