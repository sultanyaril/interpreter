#include "syntax.h"
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
