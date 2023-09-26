// 2018 ReVoL Primer Template
// 08-lf.cpp (левая факторизация)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 08 -lf -gr

// является pref префиксом правила rule ?
int is_prefix_for(RULE rule, RULE pref) {
    return 1;
}

// максимальный префикс для правила j
// возвращает длину префикса правила j
int max_prefix_for_rule_number(int j, grammar g1) {
    return 0;
}

// ищет префикс максимальной длины для A
// возвращает длину префикса
int find_prefix_for(SYMB A, grammar g1, RULE & pref) {
    return 0;
}

// устраняет префикс pref нетерминала pref[0]
void eliminate_prefix(grammar & g1, RULE pref) {
}

// алгоритм левой факторизации
int left_factoring(grammar & g1) {
    return 1;
}

// точка входа в алгоритм
// левая факторизация
int algorithm_left_factoring(grammar & g1, FILE * target) {
    // алгоритм
    int result = left_factoring(g1);
    // выводим грамматику в консоль
    g1.print(stdout);
    // выводим грамматику в файл
    g1.print(target);
    // результат
    return result;
}
/*/
.08.sxg
<A>
<A>=[a][b][a][b]
<A>=[a][b][c][d]
<A>=[a][b][c][e]
<A>=[a][b][c][f]
/*/
