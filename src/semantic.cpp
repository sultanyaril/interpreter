#include "semantic.h"

int evaluatePoliz(vector<Lexem *> poliz, int row) {
    stack<Lexem *> evalstack;
    stack<Lexem *> new_Numbers;
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
            int answ_row = variables[a -> getName()];
            return answ_row;
        }
        Lexem *b = evalstack.top();
        evalstack.pop();
        Lexem *a = evalstack.top();
        evalstack.pop();
        evalstack.push(new Number(poliz[i] -> getValue(a, b)));
        new_Numbers.push(evalstack.top());
        continue;
    }
    if (evalstack.top()) {
        int answ = evalstack.top() -> getValue();
        evalstack.pop();
        cout << answ << endl;
    }
    evalstack.pop();
    while (!new_Numbers.empty()) {
        delete new_Numbers.top();
        new_Numbers.pop();
    }
    return row + 1;
}
