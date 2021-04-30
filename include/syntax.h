#ifndef SYNTEX_H
#define SYNTEX_H
#include <vector>
#include <stack>
#include <iostream>
#include <lexem.h>
void initJumps(vector <vector<Lexem*>> &infixes);
void initLabels(vector <Lexem *> & infix, int row);
vector<Lexem *> buildPoliz(vector<Lexem *> infix);
#endif
