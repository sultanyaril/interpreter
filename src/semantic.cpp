#include "semantic.h"

int evaluatePoliz(vector<Lexem *> poliz, int row) {
    stack<Lexem *> evalstack;
    evalstack.push(nullptr);
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i] == nullptr) {
            continue;
        }
        if (poliz[i] -> type() == NUMBER or poliz[i] -> type() == VARIABLE) {
            evalstack.push(poliz[i]);
            continue;
        }
        if (poliz[i] -> getType() == GOTO) {
            Lexem *a = evalstack.top();
            evalstack.pop();
            return labels[a -> getName()];
        }
        Lexem *b = evalstack.top();
        evalstack.pop();
        Lexem *a = evalstack.top();
        evalstack.pop();
        evalstack.push(new Number(poliz[i] -> getValue(a, b)));
        continue;
    }
    if (evalstack.top()) {
        int answ = evalstack.top() -> getValue();
        delete evalstack.top();
        evalstack.pop();
        cout << answ << endl;
    }
    evalstack.pop();
    return row + 1;
}
