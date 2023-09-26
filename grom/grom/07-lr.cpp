// 2018 ReVoL Primer Template
// 07-lr.cpp (устранение левой рекурсии)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 07 -lr -gr

// устраняет непосредственную рекурсию правил для A
void eliminate_direct(SYMB Ai, grammar & g1) {
}

// формирует новое правило из двух
void compile_rule(RULE rule_k, RULE rule_j, RULE & rule_new) {
}

// заменяет правило Ak->Ajx на правила Ak->wx, w - правые части Aj
// k - номер правила Ak->Ajx
void replace_Aj(int k, grammar & g1) {
}

// преобразует неявную рекурсию в явную
// для нетерминалов от первого до Ak
// заменяет правила вида Ak->Ajx на Ak->wx, w - правые части Aj
void indirect_to_direct(SYMB Ak, grammar & g1) {
}

// устраняет левую рекурсию
void eliminate_leftr(grammar & g1) {
}

// точка входа в алгоритм
// устранение левой рекурсии
int algorithm_eliminate_leftr(grammar & g1, FILE * target) {
    // алгоритм
    eliminate_leftr(g1);
    // выводим грамматику в консоль
    g1.print(stdout);
    // выводим грамматику в файл
    g1.print(target);
    // результат
    return 1;
}
/*/
.07.sxg
<A>
<A>=<B>[b]
<A>=[a]
<B>=<A>[a]
<B>=<B>[b]
<B>=[b]
/*/
