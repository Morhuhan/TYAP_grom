// 2018 ReVoL Primer Template
// 15-minfa.cpp (минимизация ДКА методом Пономарева)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 

// минимизирует ДКА
int minimize_dfa(NFA & fa1, NFA & fa2, FILE * target) {
    return 1;
}

// точка входа в алгоритм
// минимизация ДКА методом Пономарева
int algorithm_min_dfa(NFA & fa1, FILE * target) {
    // результирующий КА
    NFA fa2;
    // алгоритм
    int result = minimize_dfa(fa1, fa2, target);
    // выводим КА в консоль
    fa2.printi(stdout);
    // выводим КА в файл
    fa2.printi(target);
    // выходной КА
    fa1 = fa2;
    // результат
    return result;
}
