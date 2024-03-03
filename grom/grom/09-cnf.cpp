// 2018 ReVoL Primer Template
// 09-cnf.cpp (приведение к нормальной форме Хомского)
#include "stdafx.h"
#include "grammar.h"
#include <iostream>
// командные строки
// 002 -cnf -gr

// правило для вывода терминала
void term_rule(SYMB A, SYMB a, grammar & g1, grammar & g2) {

    g2.reg_nont(g1.getid(A));
    g2.reg_term(g1.getid(a));

    RULE rule;

    rule[0] = A;
    rule.append(a);

    g2.rule_add(rule);
}

// приводит правило к нормальной форме Хомского
void rule_to_cnf(RULE rule_old, grammar & g1, grammar & g2) {

    if (rule_old.count() == 2) {
        g2.rule_add(rule_old);
    }

    else {

        RULE rule_new;

        rule_new[0] = rule_old[0];
        rule_new.append(rule_old[1]);
        rule_new.append(rule_old[2]);
        g2.reg_nont(g1.getid(rule_old[1]));
        g2.reg_nont(g1.getid(rule_old[2]));
        g2.rule_add(rule_new);

        // Удаляем первый символ rule_old
        RULE temp_rule;
        temp_rule[0] = rule_old[2];

        for (int j = 2; j <= rule_old.count(); j++) {
            temp_rule.append(rule_old[j]);
        }

        rule_old = temp_rule;

        rule_to_cnf(rule_old, g1, g2);
    }
}

// заменяет терминалы нетерминалами
void terms_to_nonts(RULE & rule, grammar & g1, grammar & g2) {
    
    int symbol_count = rule.count();

    for (int s = 1; s <= symbol_count; s++) {
        SYMB symbol = rule[s];

        if (symbol > 0) {
            SYMB A = g1.get_new_nont();

            rule[s] = A;

            term_rule(A, symbol, g1, g2);
        }
    }
}

// приводит грамматику к нормальной форме Хомского
int chomsky_normal_form(grammar & g1, grammar & g2) {

    g2.set_start_from(g1);

    int rule_count = g1.count();

    for (int r = 1; r <= rule_count; r++) {

        RULE rule = g1[r];

        if (rule.count() == 0) {
            if (rule[0] != g1.start()) {
                throw "Unexpected empty rule";
                return 0;
            }
            else {
                g2.rule_add_from(g1, rule);
            }
        }

        if (rule.count() > 1) {
            terms_to_nonts(rule, g1, g2);
            rule_to_cnf(rule, g1, g2);
        }

        if (rule.count() == 1) {
            g2.reg_term(g1.getid(rule[1]));
            g2.rule_add_from(g2, rule);
        }
    }

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
