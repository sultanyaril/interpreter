#include "debug.h"
void printVar() {
    cout << "VARIABLES TABLE:" << endl;
    for (map<string, int>::iterator it = VAR.begin(); it != VAR.end(); it++) {
        cout << it -> first << ' ' << it -> second << ' ' << endl;
    }
    cout << "END OF VARIABLES TABLE" << endl;
}


void printvector(vector<Lexem *> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->isNumber()) {
            cout << v[i]->getValue() << ' ';
            continue;
        }
        if (v[i]->isVariable()) {
            cout << v[i]->getName()<< ' ';
            continue;
        }
        cout << v[i] -> getType() << ' ';
    }
    cout << endl;
}

