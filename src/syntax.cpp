#include "syntax.h"
void initLabels(vector <Lexem *> & infix, int row) {
    for (int i = 1; i < infix.size(); i++) {
        if (infix[i - 1]->type() == VARIABLE &&
            infix[i]->type() == OPER) {
            Variable *lexemvar = (Variable *)infix[i - 1];
            Oper *lexemop = (Oper *)infix[i];
            if (lexemop -> getType() == COLON) {
                variables[lexemvar->getName()] = row;
                delete infix[i-1];
                delete infix[i];
                infix[i - 1] = nullptr;
                infix[i] = nullptr;
                i++;
            }
        }
    }
}

void initJumps(vector<vector<Lexem *>> & infixes) {
    stack <Goto *> stackIfElse, stackWhile;
    for (int row = 0; row < infixes.size(); row++) {
        for (int i = 0; i < infixes[row].size(); i++) {
            if (infixes[row][i] == nullptr)
                continue;
            if (infixes[row][i] -> type() != OPER) {
                continue;
            }
            if (infixes[row][i] -> getType() == IF) {
                stackIfElse.push((Goto *) infixes[row][i]);
                continue;
            }
            if (infixes[row][i] -> getType() == ELSE) {
                stackIfElse.top() -> setRow(row + 1);
                stackIfElse.pop();
                stackIfElse.push((Goto *) infixes[row][i]);
                continue;
            }
            if (infixes[row][i] -> getType() == ENDIF) {
                stackIfElse.top() -> setRow(row + 1);
                stackIfElse.pop();
                continue;
            }
            if (infixes[row][i] -> getType() == WHILE) {
                ((Goto *)infixes[row][i]) -> setRow(row);
                stackWhile.push((Goto *)infixes[row][i]);
                continue;
            }
            if (infixes[row][i] -> getType() == ENDWHILE) {
                ((Goto *)infixes[row][i]) -> setRow(stackWhile.top() -> getRow());
                stackWhile.top() -> setRow(row + 1);
                stackWhile.pop();
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
//        if (infix[i] -> getType() == ENDIF or infix[i] -> getType() == ENDWHILE) {
//            poliz.push_back(infix[i]);
//            continue;
//        }
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
