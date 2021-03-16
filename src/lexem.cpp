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

bool Variable :: isNumber() {
    return false;
}

bool Variable :: isVariable() {
    return true;
}

Variable :: Variable() {
}

int Variable :: getValue() {
    return VAR[name];
}

void Variable :: setValue(int n) {
    VAR[name] = n;
}

//FUNCTIONS OF NUMBER
Number::Number(int v) {
    setValue(v);
}

bool Number::isVariable() {
    return false;
}

bool Number::isNumber() {
    return true;
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

Oper::Oper(string & op) {
    setType(op);
}

bool Oper::isVariable() {
    return false;
}

bool Oper::isNumber() {
    return false;
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


