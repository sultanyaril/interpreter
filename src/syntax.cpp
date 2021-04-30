#include <syntax.h>


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
        if (infix[i - 1]->type() == OPER and infix[i - 1] -> getType() == FUNCTION) {
            functions[infix[i] -> getName()].number_of_args = infix.size() - i - 3;
            functions[infix[i] -> getName()].row_to_jump = row;
            delete infix[i];
            delete infix[i + 1];
            delete infix[infix.size() - 1];
            infix[i + 1] = nullptr;  // delete brackets
            infix[infix.size() - 1] = nullptr;
            infix[i] = nullptr;
            return;
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
        Lexem *function_holder = nullptr;
        int bracket_counter = 0;
        if (infix[i] == nullptr)
            continue;
        if (infix[i]->type() == VARIABLE and functions.find(infix[i] -> getName()) != functions.end()) {
            ops.push(infix[i]);
            continue;
        }
        if (infix[i]->type() == NUMBER or infix[i]->type() == VARIABLE) {
            poliz.push_back(infix[i]);
            continue;
        }
        if (infix[i] -> getType() == LBRACKET or infix[i] -> getType() == LSQRBRACKET) {
            ops.push(infix[i]);
            continue;
        }
        if (infix[i]->getType() == RBRACKET or infix[i]->getType() == RSQRBRACKET) {
            while (ops.top() -> getType() != LBRACKET and ops.top() -> getType() != LSQRBRACKET) {
                poliz.push_back(ops.top());
                ops.pop();
            }
            if (ops.top()->getType() == LBRACKET) {
                if (ops.top()->type() == VARIABLE and functions.find(infix[i]->getName()) != functions.end() ) {
                    poliz.push_back(ops.top());
                    ops.pop();
                    poliz.push_back(ops.top());
                    ops.pop();
                }
            } else {
                poliz.push_back(ops.top());
                ops.pop();
            }
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
