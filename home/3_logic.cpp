#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#define NUMBER_OF_OPS 21
using namespace std;
map<string, int> VAR;
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

string OPERTEXT[] = {
    "(", ")",
    "=",
    "or",
    "and",
    "|",
    "^",
    "&",
    "==", "!=",
    "<=", "<",
    ">=", ">",
    "<<", ">>",
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
    6, 6,
    7, 7,
    8, 8,
    9, 9,
    10, 10, 10
};


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
    bool virtual isNumber() {
    };
    bool virtual isVariable() {
    };
    string virtual getName() {
    };
    void virtual setName(string) {
    };
    Lexem();
};

Lexem::Lexem() {
}

class Variable : public Lexem{
    string name;
public:
    Variable(string &);
    bool isNumber();
    bool isVariable();
    Variable();
    int getValue();
    void setValue(int);
    string getName();
    void setName(string);
};

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

class Number : public Lexem {
    int value;
public:
    Number();
    Number(int);
    int getValue();
    void setValue(int);
    bool isNumber();
    bool isVariable();
};

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
class Oper : public Lexem {
    OPERATOR opertype;
public:
    Oper();
    Oper(string &);
    OPERATOR getType();
    void setType(string);
    int getPriority();
    int getValue(Lexem *, Lexem *);
    bool isNumber();
    bool isVariable();
};

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

void printvector(vector<Lexem *> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->isNumber()) {
            cout << v[i]->getValue() << ' ';
            continue;
        }
        if (v[i]->isVariable()) {
            cout << v[i]->getName()<< ' ';
            continue;
        }
        cout << v[i] -> getType() << ' ';
    }
    cout << endl;
}

Lexem *get_oper(string & codeline, int & i) {
    for (int op = 0; op < NUMBER_OF_OPS; op++) {
        string subcodeline= codeline.substr(i, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            i += OPERTEXT[op].size() - 1;  // for correct incrementation
            return new Oper(subcodeline);
        }
    }
    return NULL;
}

Lexem *get_num(string &codeline, int & i) {
    if ((codeline[i] <= '9') and (codeline[i] >= '0')) {
        int numb = 0;
        while ((i < codeline.size())
                    and (codeline[i] <= '9') 
                    and (codeline[i] >= '0')) {
            numb = numb * 10 + codeline[i] - '0';
            i++;
        }
        i--;  // for correect incrementation
        return new Number(numb);
    }
    return NULL;
}

Lexem *get_var(string & codeline, int & i) {
    if (((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
            ((codeline[i] >= 'A') and (codeline[i] <= 'Z'))) {
        string name = "";
        while ( (i < codeline.size()) and (
                ((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
                ((codeline[i] >= 'A') and (codeline[i] <= 'Z')) or
                ((codeline[i] >= '1') and (codeline[i] <= '9')) or
                (codeline[i] == '_')
                )
                ) {
            name += codeline[i];
            i++;
        }
        i--;  // for correct incrementation
        return new Variable(name);
        if (VAR.find(name) == VAR.end()) {
            VAR[name] = 0;
        }
    }
    return NULL;
}





vector<Lexem *> parseLexem(string & codeline) {
    vector<Lexem *> answ;
    for (int i = 0; i < codeline.size(); i++) {
        if ((codeline[i] == ' ') or
                (codeline[i] == '\t') or
                (codeline[i] == '\n'))
            continue;
        Lexem *lexem;
        lexem = get_oper(codeline, i);
        if (lexem != NULL) {
            answ.push_back(lexem);
            continue;
        }
        lexem = get_num(codeline, i);
        if (lexem != NULL) {
            answ.push_back(lexem);
            continue;
        }
        lexem = get_var(codeline, i);
        if (lexem != NULL) {
            answ.push_back(lexem);
            continue;
        }
    }
    return answ;
}


vector<Lexem *> buildPoliz(vector<Lexem *> infix) {
    vector<Lexem *> poliz;
    stack<Lexem *> ops;  // operators
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i]->isNumber() or infix[i]->isVariable()) {
            poliz.push_back(infix[i]);
            continue;
        }
        if (infix[i] -> getType() == LBRACKET) {
            ops.push(infix[i]);
            continue;
        }
        if (infix[i]->getType() == RBRACKET) {
            delete infix[i];
            while (ops.top() -> getType() != LBRACKET) {
                poliz.push_back(ops.top());
                ops.pop();
            }
            delete ops.top();
            ops.pop();
            continue;
        }

        while ((ops.size() > 0) and
            (ops.top() -> getPriority() > infix[i] -> getPriority())) {
                poliz.push_back(ops.top());
                ops.pop();
            }
        ops.push(infix[i]);
    }
    while(ops.empty() == false) {
        poliz.push_back(ops.top());
        ops.pop();
    }
    return poliz;
}

int evaluatePoliz(vector<Lexem *> poliz) {
    stack<Lexem *> evalstack;
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i] -> isNumber() or poliz[i] -> isVariable()) {
            evalstack.push(poliz[i]);
            continue;
        }
        Lexem *b = evalstack.top();
        evalstack.pop();
        Lexem *a = evalstack.top();
        evalstack.pop();
        evalstack.push(new Number(poliz[i] -> getValue(a, b)));
        delete poliz[i];
        delete a;
        delete b;
        continue;
    }
    int answ = evalstack.top() -> getValue();
    delete evalstack.top();
    return answ;
}

void printVar() {
    cout << "VARIABLES TABLE:" << endl;
    for (map<string, int>::iterator it = VAR.begin(); it != VAR.end(); it++) {
        cout << it -> first << ' ' << it -> second << ' ' << endl;
    }
    cout << "END OF VARIABLES TABLE" << endl;
}

int main() {
	string codeline;
	vector<Lexem *> infix;
	vector<Lexem *> poliz;
	int value;
	while (getline(cin, codeline)) {
		infix = parseLexem(codeline);
		poliz = buildPoliz(infix);
		value = evaluatePoliz(poliz);
		cout << "VALUE: " <<value << endl;
        printVar();
        cout << endl;
	}
	return 0;
}

