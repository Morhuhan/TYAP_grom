// 2018 ReVoL Primer Template
// 03-us.cpp (устранение бесплодных символов)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 03 -us

// возвращает 1, если правило полезное
int are_known_syms(RULE rule, SSET R) {
    return 1;
}

// формирует множество полезных нетерминалов
void find_usefull_syms(grammar & g1, SSET & R) {
}

// записывает в g2 правила, нетерминалы которых принадлежат R
void find_usefull_rules(grammar & g2, grammar & g1, SSET R) {
}

// удаляет бесплодные символы
void remove_useless(grammar & g1, grammar & g2) {
}

// точка входа в алгоритм
// устранение бесплодных символов
int algorithm_remove_useless(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // устранение бесплодных символов
    remove_useless(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return 1;
}
/*/
.03.sxg
<S>
<S>=[a]
<S>=<A>
<A>=<A><B>
<B>=<C>
<C>=[b]
/*/
