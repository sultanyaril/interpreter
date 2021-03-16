#include "semantic.h"

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
