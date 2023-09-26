// 2018 ReVoL Primer Template
// 11-faau.cpp (преобразование автомата в грамматику)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a11 -faau

// определяет наличие перехода из финального состояния
int has_tran_from_final(SYMB A, NFA & fa) {
    return 0;
}

// преобразует автомат в грамматику
void fa_to_grau(NFA & fa, grammar & gr) {
}

// точка входа в алгоритм
// преобразование автомата в грамматику
int algorithm_fa_to_grau(NFA & fa, grammar & gr, FILE * target) {
    // алгоритм
    fa_to_grau(fa, gr);
    // выводим грамматику в консоль
    gr.print(stdout);
    // выводим грамматику в файл
    gr.print(target);
    // результат
    return 1;
}
/*/
.a11.sxg
{A}
(A,a)={B}
(B,b)={E}
(E,d)={F}
(E,c)={B}
{E,F}
/*/
