#include "lexical.h"

Lexem *get_oper(string & codeline, int & i) {
    for (int op = 0; op < NUMBER_OF_OPS; op++) {
        string subcodeline= codeline.substr(i, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            i += OPERTEXT[op].size();
            return new Oper(subcodeline);
        }
    }
    return NULL;
}

Lexem *get_num(string &codeline, int & i) {
    if ((codeline[i] <= '9') and (codeline[i] >= '0')) {
        int numb = 0;
        while ((i < codeline.size())
                    and (codeline[i] <= '9') 
                    and (codeline[i] >= '0')) {
            numb = numb * 10 + codeline[i] - '0';
            i++;
        }
        return new Number(numb);
    }
    return NULL;
}

Lexem *get_var(string & codeline, int & i) {
    if (((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
            ((codeline[i] >= 'A') and (codeline[i] <= 'Z'))) {
        string name = "";
        while ( (i < codeline.size()) and (
                ((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
                ((codeline[i] >= 'A') and (codeline[i] <= 'Z')) or
                ((codeline[i] >= '1') and (codeline[i] <= '9')) or
                (codeline[i] == '_')
                )
                ) {
            name += codeline[i];
            i++;
        }
        if (VAR.find(name) == VAR.end()) {
            VAR[name] = 0;
        }
        return new Variable(name);
    }
    return NULL;
}

vector<Lexem *> parseLexem(string & codeline) {
    vector<Lexem *> answ;
    for (int i = 0; i < codeline.size();) {
        if ((codeline[i] == ' ') or
                (codeline[i] == '\t') or
                (codeline[i] == '\n')) {
            i++;
            continue;
        }
        Lexem *lexem;
        lexem = get_oper(codeline, i);
        if (lexem != NULL) {
            answ.push_back(lexem);
            continue;
        }
        lexem = get_num(codeline, i);
        if (lexem != NULL) {
            answ.push_back(lexem);
            continue;
        }
        lexem = get_var(codeline, i);
        if (lexem != NULL) {
            answ.push_back(lexem);
            continue;
        }
    }
    return answ;
}
