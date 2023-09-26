// 2018 ReVoL Primer Template
// 10-faus.cpp (устранение недостижимых состояний автомата)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a13a -faus
// a10 -faus

// ознакомительные действия с автоматом
void fa_general(NFA & fa) {
}

// устранение недостижимых состояний конечного автомата
void fa_remove_unreachable(NFA & fa1, NFA & fa2) {
    fa_general(fa2);
}

// точка входа в алгоритм
// устранение недостижимых состояний КА
int algorithm_fa_remove_unreachable(NFA & fa1, FILE * target) {
    // выходной КА
    NFA fa2;
    // алгоритм
    fa_remove_unreachable(fa1, fa2);
    // выводим КА в консоль
    fa2.printi(stdout);
    // выводим КА в файл
    fa2.printi(target);
    // результирующий КА
    fa1 = fa2;
    // результат
    return 1;
}
/*/
.a13b.sxg
{A}
(A,a)={A}
(A,b)={B}
(B,a)={A}
(B,a)={S}
{S}
/*/
