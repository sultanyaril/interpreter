#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <lexem.h>
#include <lexical.h>
#include <syntax.h>
#include <semantic.h>
#include <utility.h>

int main() {
	string codeline;
	vector<vector<Lexem *>> infixLines, postfixLines;
	vector<Lexem *> poliz;
	int value;
	while (getline(cin, codeline))
		infixLines.push_back(parseLexem(codeline));
    for (int row = 0; row < infixLines.size(); ++row)
        initLabels(infixLines[row], row);
    initJumps(infixLines);
    for (int row = 0; row < infixLines.size(); row++) {
        postfixLines.push_back(buildPoliz(infixLines[row]));
    }
    int row = searchMain(postfixLines);
    while(0 <= row and row < (int)postfixLines.size()){
        row = evaluatePoliz(postfixLines, row);
    }
    clearDoubleVector(infixLines);
    for (map<string, int*>::iterator it=arrays.begin(); it != arrays.end(); it++) {
        delete[] it->second;
    }
	return 0;
}
