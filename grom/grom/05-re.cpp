// 2018 ReVoL Primer Template
// 05-re.cpp (устранение пустых правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 05 -re -gr

// возвращает 1, если правило вырождающееся
int is_nullable_rule(RULE rule, SSET E) {
    return 1;
}

// формирует множество вырождающихся нетерминалов E
void nullable_syms(grammar & g1, SSET & E) {
}

// непустые правила копирует в g2
void useful_rules(grammar & g2, grammar g1) {
}

// удаляет символ N списка P из правила rule
// если полученное правило не пусто, добавляет его в g2
// рекурсивно вызывает себя для полученного остатка правила
// последовательно для символов N-1, N-2...
void remove_nullable_from(grammar & g2, RULE rule, SSET P, int N) {
}

// формирует список вырождающихся символов правила
void rule_nullable_syms(RULE rule, SSET E, SSET & P) {
}

// формирует правила, компенсирующие удаленные пустые правила
void complement_rules(grammar & g2, SSET E) {
}

// устраняет пустые правила
void remove_empty(grammar & g1, grammar & g2) {
}

// точка входа в алгоритм
// устранение пустых правил
int algorithm_remove_empty(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    remove_empty(g1, g2);
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
.05.sxg
<S>
<S>=<A><B>
<A>=[a]
<A>=<B><B>
<B>=[b]
<B>=.
/*/
