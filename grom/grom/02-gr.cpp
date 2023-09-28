// 2018 ReVoL Primer Template
// 02-gr.cpp (������������� ������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 02 -gr

// ���������� ������� � ������� ��������� ������������
void group_rules(grammar & g1, grammar & g2) {
    SSET P;
    SSET Q;

    SYMB S = g1.start();

    Q.insert(S);

    int rule_count = g1.count();

    // ���� Q �� ����� ���������
    while (Q.count() > 0) {

        // ����� A - ������ ������� ��-�� Q
        SYMB A = Q[1];

        // ������� A � P
        P.insert(A);

        // �������� �� Q ������ �������
        Q.remove(1);

        // ������������� ������� g1 �� r=1 �� r=rule_count
        for (int r = 1; r <= rule_count; r++) {

            // rule - ������� r �� ��������� g1
            RULE rule = g1[r];

            // ���� ����� ���������� rule ��������� � A
            if (rule[0] == A) {

                // ������� rule � g2
                g2.rule_add(rule);

                // ����� symbol_count � ���������� �������� ������� rule.
                int symbol_count = rule.count();

                // ������������� ������� rule �� s = 1 �� s = symbol_count.
                for (int s = 1; s <= symbol_count; s++) {

                    // ����� B � ������ s ������� rule.
                    SYMB B = rule[s];

                    // ���� B � ����������, �� 
                    if (B < 0) {

                        // ���� B ����������� � P
                        if (P.misses(B)) {

                            // ������� ��� � Q.
                            Q.insert(B);

                        }
                    }
                }
            }
        }
    }

    // ���������� ������� ������ G2 ������ �������� ������� G1
    g2.set_start_from(g1);
}

// ����� ����� � ��������
// ������������� ������
int algorithm_group_rules(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ��������
    group_rules(g1, g2);
    // ������� ���������� � �������
    g2.print(stdout);
    // ������� ���������� � ����
    g2.print(target);
    // �������� ����������
    g1 = g2;
    // ���������
    return 1;
}
/*/
.02.sxg
<S>
<A>=<S><A>
<A>=<B>
<B>=[b]
<A>=[a]
<S>=<B>
<S>=<A><B>
/*/
