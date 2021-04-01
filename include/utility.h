#ifndef DEBUG_H
#define DEBUG_H
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include "const.h"
#include "lexem.h"
void printVar();
void printVector(vector<Lexem *> v);
void clearDoubleVector(vector<vector<Lexem *>> v);
#endif
