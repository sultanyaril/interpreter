#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
enum OPERATOR {
    LBRACKET, RBRACKET, PLUS, MINUS, MULTIPLY
};
int PRIORITY[] = {-1, -1, 0, 0, 1};

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
    Lexem();
};

Lexem::Lexem() {
}

class Number : public Lexem {
    int value;
public:
    Number();
    int getValue();
    void setValue(int);
    bool isNumber();
};

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
};

Oper::Oper() {
    opertype = PLUS;
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
    }
    return -1;
}
void printvector(vector<Lexem *> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->isNumber()) {
            cout << v[i]->getValue() << ' ';
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
                or (codeline[i] == '(') or (codeline[i] == ')')) {
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
    }
    return answ;
}


vector<Lexem *> buildPoliz(vector<Lexem *> infix) {
    vector<Lexem *> poliz;
    stack<Lexem *> ops;  // operators
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i]->isNumber()) {
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
                    (infix[i] -> getType() == MULTIPLY)) {
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
        if (poliz[i] -> isNumber()) {
            evalstack.push(poliz[i]);
            continue;
        }
        if (poliz[i] -> isNumber() == false) {
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
    }
    int answ = evalstack.top() -> getValue();
    delete evalstack.top();
    return answ;
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
		cout << value << endl;
        // for (int i = 0; i < poliz.size(); i++)
            // delete poliz[i];
	}
	return 0;
}

