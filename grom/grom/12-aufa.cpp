// 2018 ReVoL Primer Template
// 12-aufa.cpp (преобразование грамматики в автомат)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a11 -faau -aufa

// находит пару A->a или A->aB, возвращает номер правила
int has_pair_rule(RULE rule, int length, grammar gr) {
    return 0;
}

// преобразует грамматику в автомат
int grau_to_fa(grammar & gr, NFA & fa) {
    return 1;
}

// точка входа в алгоритм
// преобразование грамматики в автомат
int algorithm_grau_to_fa(grammar & gr, NFA & fa, FILE * target) {
    // алгоритм
    int result = grau_to_fa(gr, fa);
    // выводим КА в консоль
    fa.printi(stdout);
    // выводим КА в файл
    fa.printi(target);
    // результат
    return result;
}
