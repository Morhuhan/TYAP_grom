// 2018 ReVoL Primer Template
// 01-gen.cpp (ознакомительные действия)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 001

// упражнение 1
void test1 (grammar & g1, grammar & g2) {
}

// упражнение 2, 3, 4
void test2 (grammar & g1, grammar & g2) {
}

// упражнение 5
void test3 (grammar & g1, grammar & g2) {
}

// алгоритмы общих действий с грамматикой
void grammar_general(grammar & g1, grammar & g2) {
    test1(g1, g2);
    //test2(g1, g2);
    //test3(g1, g2);
}

// точка входа в алгоритм
// общие действия с грамматикой
int algorithm_general(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    grammar_general(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    return 0;
}
/*/
.001.sxg
<S>
<S>=<S>[+]<T>
<S>=<T>
<T>=<T>[*]<P>
<T>=<P>
<P>=[a]
<P>=[(]<S>[)]
/*/
