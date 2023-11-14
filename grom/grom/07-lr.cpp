// 2018 ReVoL Primer Template
// 07-lr.cpp (���������� ����� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 07 -lr -gr

// ��������� ���������������� �������� ������ ��� A
void eliminate_direct(SYMB Ai, grammar & g1) {
}

// ��������� ����� ������� �� ����
void compile_rule(RULE rule_k, RULE rule_j, RULE & rule_new) {
}

// �������� ������� Ak->Ajx �� ������� Ak->wx, w - ������ ����� Aj
// k - ����� ������� Ak->Ajx
void replace_Aj(int k, grammar & g1) {

    RULE rule_k = g1[k];

    SYMB Aj = rule_k[1];

    RULE rule_new;

    for (int j = 0; j < length; j++) {

    }

}

// ����������� ������� �������� � �����
// ��� ������������ �� ������� �� Ak
// �������� ������� ���� Ak->Ajx �� Ak->wx, w - ������ ����� Aj
void indirect_to_direct(SYMB Ak, grammar & g1) {

    int rule_count = g1.count();

    // ���������� ������� � �������� < k
    for (SYMB Aj = 1; Aj < Ak ; Aj++) {

        // ��� ������� ������� ������������� ��� �������
        for (int k = 0; k < rule_count; k++) {

            RULE rule = g1[k];

            // ���� ����� �������, ��� ����� ����������� ���������� Ak, � ������ ����������
            // � �������� j, ������� ������ �� ����������� ��������, ��� k
            if ((rule[0] == -Ak) && (rule[1] == -Aj)) {

                // ��������� ���� ������� �� ���� ������ ��� Aj
                replace_Aj(k, g1);
            }
        }
    }
}

// ��������� ����� ��������
void eliminate_leftr(grammar & g1) {

    // ������ ���������� �����������
    SYMB last = g1.nont_count();

    for (SYMB A = 1; ; A++) {

        // ��������� ����� ��������
        if (g1.is_symbol_leftr(-A)) {
            eliminate_direct(-A, g1);
        }

        // ������� ������
        if (A == last) {
            break;
        }

        // ��������� ������� ��������
        else {
            indirect_to_direct(A + 1, g1);
        }
    }
}

// ����� ����� � ��������
// ���������� ����� ��������
int algorithm_eliminate_leftr(grammar & g1, FILE * target) {
    // ��������
    eliminate_leftr(g1);
    // ������� ���������� � �������
    g1.print(stdout);
    // ������� ���������� � ����
    g1.print(target);
    // ���������
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
