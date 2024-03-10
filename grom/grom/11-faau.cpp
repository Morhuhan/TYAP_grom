// 2018 ReVoL Primer Template
// 11-faau.cpp (преобразование автомата в грамматику)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a11 -faau

// определяет наличие перехода из финального состояния
int has_tran_from_final(SYMB A, NFA & fa) {
    int delta_count = fa.delta_count();
    for (int t = 1; t < delta_count; t++) {
        TRAN transit = fa[t];
        if (transit.a == A) { return 1; }
    }
    return 0;
}

// преобразует автомат в грамматику
void fa_to_grau(NFA & fa, grammar & gr) {

    int delta_count = fa.delta_count();

    for (int t = 1; t < delta_count; t++) {
        TRAN transit = fa[t];

        RULE rule;

        if (fa.finals.contains(transit.b)) {
            rule[0] = gr.reg_from(fa, transit.a);
            rule.append(gr.reg_char(transit.c));
            gr.rule_add(rule);

            if (has_tran_from_final(transit.b, fa)) {
                rule.append(gr.reg_from(fa, transit.b));
                
            }
        }

        else {
            rule[0] = gr.reg_from(fa, transit.a);
            rule.append(gr.reg_char(transit.c));
            rule.append(gr.reg_from(fa, transit.b));
        }

        gr.rule_add(rule);
    }

    int initials_count = fa.initials.count();

    gr.set_start(gr.reg_from(fa, fa.initials[1]));
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
