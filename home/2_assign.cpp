#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;
enum OPERATOR {
    LBRACKET, RBRACKET, ASSIGN, PLUS, MINUS, MULTIPLY
};
int PRIORITY[] = {-1, -1, 0, 1, 1, 2};
map<string, int> VAR;


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
    int virtual getValue(int, int) {
    };
    void virtual setValue(int) {
    };
    void virtual setType(char) {
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
    bool isNumber();
    bool isVariable();
    Variable();
    int getValue();
    void setValue(int);
    string getName();
    void setName(string);
};

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
    int getValue();
    void setValue(int);
    bool isNumber();
    bool isVariable();
};

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
    OPERATOR getType();
    void setType(char);
    int getPriority();
    int getValue(int , int);
    bool isNumber();
    bool isVariable();
};

Oper::Oper() {
    opertype = PLUS;
}

bool Oper::isVariable() {
    return false;
}

bool Oper::isNumber() {
    return false;
}

void Oper :: setType(char op)  {
    switch(op) {
        case '+':
            opertype = PLUS;
            break;
        case '-':
            opertype = MINUS;
            break;
        case '*':
            opertype = MULTIPLY;
            break;
        case '(':
            opertype = LBRACKET;
            break;
        case ')':
            opertype = RBRACKET;
            break;
        case '=':
            opertype = ASSIGN;
            break;
    }
}

OPERATOR Oper :: getType() {
    return opertype;
}

int Oper :: getPriority() {
    return PRIORITY[opertype];
}

int Oper :: getValue(int a, int b) {
    switch(opertype) {
        case PLUS:
            return a + b;
        case MINUS:
            return b - a;
        case MULTIPLY:
            return a * b;
        case ASSIGN:
            return a;
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

vector<Lexem *> parseLexem(string codeline) {
    vector<Lexem *> answ;
    for (int i = 0; i < codeline.size(); i++) {
        if ((codeline[i] == ' ') or (codeline[i] == '\t') or (codeline[i] == '\n'))
            continue;
        if ((codeline[i] == '+') or (codeline[i] == '-') or (codeline[i] == '*')
                or (codeline[i] == '(') or (codeline[i] == ')') or codeline[i] == '=') {
            answ.push_back(new Oper);
            answ.back() -> setType(codeline[i]);
            continue;
        }
        if ((codeline[i] <= '9') and (codeline[i] >= '0')) {
            int numb = 0;
            while ((i < codeline.size())
                        and (codeline[i] <= '9') 
                        and (codeline[i] >= '0')) {
                numb = numb * 10 + codeline[i] - '0';
                i++;
            }
            answ.push_back(new Number);
            answ.back() -> setValue(numb);
            i--;
            continue;
        }
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
            answ.push_back(new Variable);
            answ.back()->setName(name);
            if (VAR.find(name) == VAR.end()) {
                VAR[name] = 0;
            }
            i--;
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
        }

        if ((infix[i] -> getType() == PLUS) or
                    (infix[i] -> getType() == MINUS) or
                    (infix[i] -> getType() == MULTIPLY) or
                    (infix[i] -> getType() == ASSIGN)) {
            while ((ops.size() > 0) and (ops.top() -> getPriority() >= infix[i] -> getPriority())) {
                poliz.push_back(ops.top());
                ops.pop();
            }
            ops.push(infix[i]);
            continue;
        }
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
        if (poliz[i] -> getType() == ASSIGN) {
            Lexem *tmp = evalstack.top();
            int a = evalstack.top() -> getValue();
            evalstack.pop();
            evalstack.top() -> setValue(a);
            evalstack.push(tmp);
        }
        int a = evalstack.top() -> getValue();
        delete evalstack.top();
        evalstack.pop();
        int b = evalstack.top() -> getValue();
        delete evalstack.top();
        evalstack.pop();
        evalstack.push(new Number);
        evalstack.top() -> setValue(poliz[i] -> getValue(a, b));
        delete poliz[i];
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
	}
	return 0;
}

