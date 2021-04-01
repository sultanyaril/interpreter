#include "syntax.h"
void initLabels(vector <Lexem *> & infix, int row) {
    for (int i = 1; i < infix.size(); i++) {
        if (infix[i - 1]->type() == VARIABLE &&
            infix[i]->type() == OPER) {
            Variable *lexemvar = (Variable *)infix[i - 1];
            Oper *lexemop = (Oper *)infix[i];
            if (lexemop -> getType() == COLON) {
                labels[lexemvar->getName()] = row;
                delete infix[i-1];
                delete infix[i];
                infix[i - 1] = nullptr;
                infix[i] = nullptr;
                i++;
            }
        }
    }
}

vector<Lexem *> buildPoliz(vector<Lexem *> infix) {
    vector<Lexem *> poliz;
    stack<Lexem *> ops;  // operators
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == nullptr)
            continue;
        if (infix[i]->type() == NUMBER or infix[i]->type() == VARIABLE) {
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
