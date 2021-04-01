#ifndef SYNTEX_H
#define SYNTEX_H
#include <vector>
#include <stack>
#include "lexem.h"
void initLabels(vector <Lexem *> & infix, int row);
vector<Lexem *> buildPoliz(vector<Lexem *> infix);
#endif
