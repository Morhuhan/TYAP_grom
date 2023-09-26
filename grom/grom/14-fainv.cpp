// 2018 ReVoL Primer Template
// 14-fainv.cpp (инвертирование автомата)
#include "stdafx.h"
#include "grammar.h"
#include "main.h"
// командные строки
// a13e -fainv -dfa -fainv -dfa

// обращает автомат
void fa_invert(NFA & fa) {
}

// точка входа в алгоритм
// инвертирование автомата
int algorithm_fa_invert(NFA & fa, FILE * target) {
    // алгоритм
    fa_invert(fa);
    // выводим КА в консоль
    fa.printn(stdout);
    // выводим КА в файл
    fa.printn(target);
    return 1;
}
