// 2018 ReVoL Primer Template
// 02-gr.cpp (группирование правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 02 -gr

// группирует правила в порядке появления нетерминалов
void group_rules(grammar & g1, grammar & g2) {
}

// точка входа в алгоритм
// группирование правил
int algorithm_group_rules(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    group_rules(g1, g2);
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
.02.sxg
<S>
<A>=<S><A>
<A>=<B>
<B>=[b]
<A>=[a]
<S>=<B>
<S>=<A><B>
/*/
