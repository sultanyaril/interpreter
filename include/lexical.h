#ifndef LEXICAL_H
#define LEXICAL_H
#include <vector>
#include <iostream>
#include <lexem.h>
#include <const.h>
vector<Lexem *> parseLexem(string & codeline);
Lexem *get_var(string & codeline, int & i);
Lexem *get_num(string &codeline, int & i);
Lexem *get_oper(string & codeline, int & i);
#endif
