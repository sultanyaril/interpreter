#include "utility.h"
void printVar() {
    cout << "VARIABLES TABLE:" << endl;
    for (map<string, int>::iterator it = variables.begin(); it != variables.end(); it++) {
        cout << it -> first << ' ' << it -> second << ' ' << endl;
    }
    cout << "END OF VARIABLES TABLE" << endl;
}


void printVector(vector<Lexem *> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->type()==NUMBER) {
            cout << v[i]->getValue() << ' ';
            continue;
        }
        if (v[i]->type()==VARIABLE) {
            cout << v[i]->getName()<< ' ';
            continue;
        }
        cout << v[i] -> getType() << ' ';
    }
    cout << endl;
}

void clearDoubleVector(vector<vector<Lexem *>>  v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++)
            if (v[i][j] != nullptr)
                delete v[i][j];
    }
}
