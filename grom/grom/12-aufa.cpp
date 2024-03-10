// 2018 ReVoL Primer Template
// 12-aufa.cpp (преобразование грамматики в автомат)
#include "stdafx.h"
#include "grammar.h"
#include <iostream>
// командные строки
// a11 -faau -aufa

using namespace std;

// находит пару A->a или A->aB, возвращает номер правила
int has_pair_rule(RULE rule, grammar gr) {

    int rules_count = gr.count();

    int rule_length = rule.count();

    for (int i = 1; i <= rules_count; i++) {

        RULE rule_i = gr[i];

        if (rule_i[0] == rule[0] && rule_i[1] == rule[1] && rule_i.count() == 2) {

            if (rule_i.count() > 1) {
                return gr.rule_exist(rule_i);
            }
        }
    }

    return 0;
}

// преобразует грамматику в автомат
int grau_to_fa(grammar & gr, NFA & fa) {

    fa.reg_initial_id(gr.getid(gr.start()));

    int rules_count = gr.count();

    for (int i = 1; i <= rules_count; i++) {

        RULE rule = gr[i];

        TRAN tran;

        if (rule.count() > 2) {
            cout << "Grammer is wrong";
            return 0;
        }

        else if (rule.count() == 1) {

            if (has_pair_rule(rule, gr) != 0) {
                RULE pair_rule = gr[has_pair_rule(rule, gr)];

                tran.a = fa.reg_state_from(gr, rule[0]);
                tran.c = gr.get_char(rule[1]);
                tran.b = fa.reg_final_from(gr, pair_rule[2]);
            }

            else
            {
                tran.a = fa.reg_state_from(gr, rule[0]);
                tran.c = gr.get_char(rule[1]);
                tran.b = fa.reg_final_from(gr, gr.get_new_nont());
            }

        }

        else if (rule.count() == 2) {

            tran.a = fa.reg_state_from(gr, rule[0]);
            tran.c = gr.get_char(rule[1]);
            tran.b = fa.reg_state_from(gr, rule[2]);
        }

        fa.tran_add(tran);
    }

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
