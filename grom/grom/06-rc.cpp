// 2018 ReVoL Primer Template
// 06-rс.cpp (устранение цепных правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 05 -re -gr -rc -gr

// ищет не цепные правила g1 и добавляет их в g2
void nonunit_rules(grammar & g1, grammar & g2) {
}

// ищет цепочку нетерминала A
void find_chain_for(grammar & g1, SSET & R) {
}

// формирует новые не цепные правила
void nonunit_rules_for(grammar & g2, grammar & g1, SSET R) {
}

// устраняет цепные правила
void remove_units(grammar & g1, grammar & g2) {
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
