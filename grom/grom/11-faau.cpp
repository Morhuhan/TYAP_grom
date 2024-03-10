// 2018 ReVoL Primer Template
// 11-faau.cpp (�������������� �������� � ����������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// a11 -faau

// ���������� ������� �������� �� ���������� ���������
int has_tran_from_final(SYMB A, NFA & fa) {
    int delta_count = fa.delta_count();
    for (int t = 1; t < delta_count; t++) {
        TRAN transit = fa[t];
        if (transit.a == A) { return 1; }
    }
    return 0;
}

// ����������� ������� � ����������
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

// ����� ����� � ��������
// �������������� �������� � ����������
int algorithm_fa_to_grau(NFA & fa, grammar & gr, FILE * target) {
    // ��������
    fa_to_grau(fa, gr);
    // ������� ���������� � �������
    gr.print(stdout);
    // ������� ���������� � ����
    gr.print(target);
    // ���������
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
