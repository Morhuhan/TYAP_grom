// 2018 ReVoL Primer Template
// 06-rс.cpp (устранение цепных правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 05 -re -gr -rc -gr

// ищет не цепные правила g1 и добавляет их в g2
void nonunit_rules(grammar & g1, grammar & g2) {

    int rule_count = g1.count();

    for (int r = 1; r <= rule_count; r++) {

        RULE rule = g1[r];

        if (!rule.is_unit()) {
            g2.rule_add_from(g1, rule);
        }
    }
}

// ищет цепочку нетерминала A
void find_chain_for(grammar & g1, SSET & R) {

    int rule_count = g1.count();

    while (1) {

        int fix = R.count();

        for (int r = 1; r <= rule_count; r++) {

            RULE rule = g1[r];

            if (R.contains(rule[0])) {

                int symbol_count = rule.count();
                
                for (int s = 1; s <= symbol_count; s++) {
                    R.insert(rule[s]);
                }
            }
        }

        if (fix == R.count()) {
            break;
        }
    }
}

// формирует новые не цепные правила
void nonunit_rules_for(grammar & g2, grammar & g1, SSET R) {
    
    int r_count = R.count();

    int rule_count = g2.count();

    for (int s = 1; s <= r_count; s++) {

        SYMB X = R[s];

        for (int r = 1; r <= rule_count; r++) {

            RULE rule = g2[r];

            if (rule[0] == R[s]) {
                rule[0] = R[1];
                g2.rule_add_from(g1, rule);
            }
        }
    }
}

// устраняет цепные правила
void remove_units(grammar& g1, grammar& g2) {

    g2.set_start_from(g1);

    // Удаляем цепные правила из g1
    nonunit_rules(g1, g2);

    SYMB last = g1.nont_count();

    for (SYMB A = 1; A <= last; A++) {

        SSET R = -A;

        // Для каждого оставшегося нетерминала находим множество его цепных правил
        find_chain_for(g1, R);

        // Для каждого оставшегося нетерминала добавляем компенсирующие правила
        nonunit_rules_for(g2, g1, R);
    }
}

// точка входа в алгоритм
// устранение цепных правил
int algorithm_remove_units(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    remove_units(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return 1;
}
