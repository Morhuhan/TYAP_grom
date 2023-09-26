// 2018 ReVoL Primer Template
// 09-cnf.cpp (приведение к нормальной форме Хомского)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 002 -cnf -gr

// правило для вывода терминала
void term_rule(SYMB A, SYMB a, grammar & g1, grammar & g2) {
}

// приводит правило к нормальной форме Хомского
void rule_to_cnf(RULE rule_old, grammar & g1, grammar & g2) {
}

// заменяет терминалы нетерминалами
void terms_to_nonts(RULE & rule, grammar & g1, grammar & g2) {
}

// приводит грамматику к нормальной форме Хомского
int chomsky_normal_form(grammar & g1, grammar & g2) {
    return 1;
}

// точка входа в алгоритм
// приведение к нормальной форме Хомского
int algorithm_chomsky_normal_form(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    int result = chomsky_normal_form(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return result;
}
/*/
.002.sxg
<S>
<S>=<S>[+]<S>
<S>=<S>[*]<S>
<S>=[a]
<S>=[(]<S>[)]
/*/
