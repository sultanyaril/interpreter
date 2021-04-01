#ifndef LEXEM_H
#define LEXEM_H
#include <const.h>
#include <vector>
class Lexem {
public:
    virtual ~Lexem(){
    };
    OPERATOR virtual getType() {
    };
    int virtual getPriority() {
    };
    int virtual getValue() {
    };
    int virtual getValue(Lexem *, Lexem *) {
    };
    void virtual setValue(int) {
    };
    void virtual setType(string) {
    };
    string virtual getName() {
    };
    void virtual setName(string) {
    };
    TYPE virtual type() {
    };
    Lexem();
};


class Variable : public Lexem{
    string name;
public:
    Variable(string &);
    Variable();
    int getValue();
    void setValue(int);
    string getName();
    void setName(string);
    TYPE type();
};


class Number : public Lexem {
    int value;
public:
    Number();
    Number(int);
    int getValue();
    void setValue(int);
    TYPE type();
};


class Oper : public Lexem {
    OPERATOR opertype;
public:
    Oper();
    Oper(string &);
    OPERATOR getType();
    void setType(string);
    int getPriority();
    int getValue(Lexem *, Lexem *);
    TYPE type();
};

#endif
