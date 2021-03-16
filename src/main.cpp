#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include "lexem.h"
#include "lexical.h"
#include "syntax.h"
#include "semantic.h"
#include "debug.h"
int main() {
	string codeline;
	vector<Lexem *> infix;
	vector<Lexem *> poliz;
	int value;
	while (getline(cin, codeline)) {
		infix = parseLexem(codeline);
		poliz = buildPoliz(infix);
		value = evaluatePoliz(poliz);
		cout << "VALUE: " <<value << endl;
        printVar();
        cout << endl;
	}
	return 0;
}
