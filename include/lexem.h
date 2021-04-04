#ifndef LEXEM_H
#define LEXEM_H
#include <const.h>
#include <vector>
#include <string>
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
    Oper(OPERATOR optype);
    Oper(string &);
    OPERATOR getType();
    void setType(string);
    int getPriority();
    int getValue(Lexem *, Lexem *);
    TYPE type();
};

class Goto : public Oper {
    int row;
public:
    Goto (OPERATOR optype);
    void setRow(int);
    void setRow(const string &labelname);
    int getRow();
};

#endif
