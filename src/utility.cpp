#include <utility.h>
void printVar() {
    cout << "VARIABLES TABLE:" << endl;
    for (map<string, int>::iterator it = variables.begin(); it != variables.end(); it++) {
        cout << it -> first << ' ' << it -> second << ' ' << endl;
    }
    cout << "END OF VARIABLES TABLE" << endl;
}


void printVector(vector<Lexem *> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == nullptr)
            continue;
        if (v[i]->type()==NUMBER) {
            cout << v[i]->getValue() << ' ';
            continue;
        }
        if (v[i]->type()==VARIABLE) {
            cout << v[i]->getName()<< ' ';
            continue;
        }
        cout << OPERTEXT[(v[i] -> getType())] << ' ';
    }
    cout << endl;
}

void printDoubleVector(vector<vector<Lexem *>> v) {
    for (int i = 0; i < v.size(); i++) {
        printVector(v[i]);
    }
}

void clearDoubleVector(vector<vector<Lexem *>>  v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++)
            if (v[i][j] != nullptr)
                delete v[i][j];
    }
}

int searchMain(vector<vector<Lexem *>> postfixLines) {
    int start = 0;
    for (int i = 0; i < postfixLines.size(); i++) {
        int row_size = postfixLines[i].size();
        if (row_size - 1 < 0)
            continue;
        if (postfixLines[i][row_size - 1] == nullptr)
            continue;
        if (postfixLines[i][row_size - 1] -> type() == OPER and
                postfixLines[i][row_size - 1] -> getType() == RETURN) {
            start = i + 1;
        }
    }
    return start;
}
