#include "lexem.h"

// FUNCTIONS OF LEXEM
Lexem::Lexem() {
}

//FUNCTIONS OF VARIABLE
Variable::Variable(string & n) {
    setName(n);
}

void Variable::setName(string n) {
    name = n;
}

string Variable::getName() {
    return name;
}

TYPE Variable::type() {
    return VARIABLE;
}

Variable :: Variable() {
}

int Variable :: getValue() {
    return variables[name];
}

void Variable :: setValue(int n) {
    variables[name] = n;
}

//FUNCTIONS OF NUMBER
Number::Number(int v) {
    setValue(v);
}

TYPE Number::type() {
    return NUMBER;
}

Number::Number() {
    value = 0;
}


int Number::getValue() {
    return value;
}

void Number::setValue(int v) {
    value = v;
}

//FUNCTIONS OF OPER
Oper::Oper() {
    opertype = PLUS;
}

Oper::Oper(OPERATOR optype) : opertype(optype) {
}

Oper::Oper(string & op) {
    setType(op);
}

TYPE Oper::type() {
    return OPER;
}

void Oper :: setType(string op) {
    for (int i = 0; i < NUMBER_OF_OPS; i++) {
        if (OPERTEXT[i] == op) {
            opertype = static_cast<OPERATOR>(i);
            break;
        }
    }
}

OPERATOR Oper :: getType() {
    return opertype;
}

int Oper :: getPriority() {
    return PRIORITY[opertype];
}

int Oper :: getValue(Lexem *left, Lexem *right) {
    switch(opertype) {
        case PLUS:
            return right->getValue() + left->getValue();
        case MINUS:
            return left->getValue() - right->getValue();
        case MULTIPLY:
            return right->getValue() * left->getValue();
        case ASSIGN:
            left -> setValue(right -> getValue());
            return right->getValue();
        case OR:
            return left->getValue() or right->getValue();
        case AND:
            return left->getValue() and right->getValue();
        case BITOR:
            return left->getValue() | right->getValue();
        case BITAND:
            return left->getValue() & right->getValue();
        case EQ:
            return left->getValue() == right->getValue();
        case NEQ:
            return left->getValue() != right->getValue();
        case LEQ:
            return left->getValue() <= right->getValue();
        case LT:
            return left->getValue() < right->getValue();
        case GEQ:
            return left->getValue() >= right->getValue();
        case GT:
            return left->getValue() > right->getValue();
        case SHL:
            return left->getValue() << right->getValue();
        case SHR:
            return left->getValue() >> right->getValue();
        case DIV:
            return left->getValue() / right->getValue();
        case MOD:
            return left->getValue() % right->getValue();
    }
    return -1;
}

// FUNCTIONS OF GOTO

Goto :: Goto(OPERATOR optype) : Oper(optype) {
    row = -1;
};

void Goto :: setRow(int row) {
    Goto :: row = row;
}

void Goto :: setRow(const string &labelname) {
    row = variables[labelname];
}

int Goto :: getRow() {
    return row;
}
