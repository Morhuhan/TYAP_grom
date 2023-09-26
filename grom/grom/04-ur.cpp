// 2018 ReVoL Primer Template
// 04-ur.cpp (устранение недостижимых символов)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 03 -us -ur -gr

// добавляет нетерминалы правила rule в множество R
void find_rule_syms(RULE rule, SSET & R) {
}

// формирует множество достижимых символов
void find_reachable_syms(grammar & g1, SSET & R) {
}

// записывает в g2 правила, левые символы которых принадлежат R
void find_reachable_rules(grammar & g2, grammar & g1, SSET R) {
}

// удаляет недостижимые символы
void remove_unreachable(grammar & g1, grammar & g2) {
}

// точка входа в алгоритм
// устранение недостижимых символов
int algorithm_remove_unreachable(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // устранение недостижимых символов
    remove_unreachable(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return 1;
}
