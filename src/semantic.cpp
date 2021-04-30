#include <semantic.h>

int evaluatePoliz(vector<vector<Lexem *>> &polizLines, int row) {
    vector<Lexem *> poliz = polizLines[row];
    stack<Lexem *> evalstack;
    stack<Lexem *> newNumbers;
    evalstack.push(nullptr);
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i] == nullptr) {
            continue;
        }
        if (poliz[i] -> type() == NUMBER or poliz[i] -> type() == VARIABLE) {
            evalstack.push(poliz[i]);
            continue;
        }
        if (poliz[i] -> getType() == RETURN) {
            if (evalstack.top()) {
                global_stack.push(evalstack.top() -> getValue());
                evalstack.pop();
            }
            variables.clear();
            arrays.clear();
            while (!newNumbers.empty()) {
                delete newNumbers.top();
                newNumbers.pop();
            }
            return -1;
        }
        if (poliz[i] -> getType() == FUNCTION) {
            stack<int> stack_of_stupidity;
            while(!global_stack.empty()) {
                stack_of_stupidity.push(global_stack.top());
                global_stack.pop();
            }
            while (!stack_of_stupidity.empty()) {
                evalstack.top() -> setValue(stack_of_stupidity.top());
                evalstack.pop();
                stack_of_stupidity.pop();
            }
            continue;
        }
        if (poliz[i] -> getType() == LBRACKET) {
            if (i + 1 >= poliz.size())
                continue;
            if (poliz[i + 1] -> type() != VARIABLE)
                continue;
            if (functions.find(poliz[i + 1] -> getName()) == functions.end())
                continue;
            Lexem *func_name = poliz[i + 1];
            poliz[i + 1] = nullptr;
            for (int arg = 0; arg < functions[func_name->getName()].number_of_args; arg++) {
                global_stack.push(evalstack.top()->getValue());
                evalstack.pop();
            }
            Space *current_space = new Space;
            current_space -> variables = variables;
            current_space -> arrays = arrays;
            variables.clear();
            arrays.clear();
            int tmp_row = functions[func_name->getName()].row_to_jump;
            while (tmp_row >= 0) {
                //printVector(polizLines[tmp_row]);
                tmp_row = evaluatePoliz(polizLines, tmp_row);
            }
            variables = current_space -> variables;
            arrays = current_space -> arrays;
            delete current_space;
            if (!global_stack.empty()) {
                evalstack.push(new Number(global_stack.top()));
                global_stack.pop();
                newNumbers.push(evalstack.top());
            }
            continue;
        }
        if (poliz[i] -> getType() == LSQRBRACKET) {
            int val = evalstack.top()->getValue();
            evalstack.pop();
            Lexem *ele = new ArrayElement(evalstack.top()->getName());
            evalstack.pop();
            ((ArrayElement*)ele) -> setPosition(val);
            evalstack.push(ele);
            newNumbers.push(ele);
            continue;
        }
        if (poliz[i] -> getType() == PRINT) {
            cout << evalstack.top()->getValue() << endl;
            continue;
        }
        if (poliz[i] -> getType() == ENDIF) {
            continue;
        }
        if (poliz[i] -> getType() == IF || poliz[i] -> getType() == WHILE) {
            int rvalue = evalstack.top()->getValue();
            evalstack.pop();
            if (rvalue == 0) {
                while (!newNumbers.empty()) {
                    delete newNumbers.top();
                    newNumbers.pop();
                }
                return ((Goto *)poliz[i]) -> getRow();
            }
            continue;
        }
        if (poliz[i] -> getType() == ELSE || poliz[i] -> getType() == ENDWHILE) {
            return ((Goto *)poliz[i]) -> getRow();
        }
        if (poliz[i] -> getType() == GOTO) {
            Lexem *a = evalstack.top();
            evalstack.pop();
            return variables[a->getName()];
        }
        Lexem *b = evalstack.top();
        evalstack.pop();
        Lexem *a = evalstack.top();
        evalstack.pop();
        evalstack.push(new Number(poliz[i] -> getValue(a, b)));
        newNumbers.push(evalstack.top());
        continue;
    }
    if (evalstack.top()) {
        int answ = evalstack.top() -> getValue();
        evalstack.pop();
    }
    evalstack.pop();
    while (!newNumbers.empty()) {
        delete newNumbers.top();
        newNumbers.pop();
    }
    return row + 1;
}
