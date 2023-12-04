// 2018 ReVoL Primer Template
// 07-lr.cpp (���������� ����� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 07 -lr -gr

// ��������� ���������������� �������� ������ ��� A
void eliminate_direct(SYMB Ai, grammar & g1) {

    SYMB A1 = g1.get_star_nont(Ai);

    int rule_count = g1.count();

    for (int r = 1; r <= rule_count; r++) {

        RULE rule = g1[r];
        
        if (rule[0] == Ai && rule.is_leftr()) {

            RULE new_rule;

            new_rule[0] = A1;

            for (int s = 2; s <= rule.count(); s++) {
                new_rule.append(rule[s]);
            }

            g1[r] = new_rule;

            new_rule.append(A1);

            g1.rule_add(new_rule);

        }

        else if (rule[0] == Ai && !rule.is_leftr()) {

            RULE new_rule = rule;

            new_rule.append(A1);

            g1.rule_add(new_rule);
        }
    }
}

// ��������� ����� ������� �� ���� (�������� ������� �� ����?)
void compile_rule(RULE rule_k, RULE rule_j, RULE & rule_new) {
    
    // ����� �� <B>=<A>[a] � <A>=<B>[b] �������� <B>=<B>[b][a]

    int rule_k_symb_count = rule_k.count();

    int rule_j_symb_count = rule_j.count();

    // <B>=
    rule_new[0] = rule_k[0];

    // <B>=<B>[b]
    for (int s = 1; s < rule_j_symb_count + 1; s++) {
        rule_new.append(rule_j[s]);
    }

    // <B>=<B>[b][a]
    for (int s = 2; s < rule_k_symb_count + 1; s++) {
        rule_new.append(rule_k[s]);
    }
}

// �������� ������� Ak->Ajx �� ������� Ak->wx, w - ������ ����� Aj
// k - ����� ������� Ak->Ajx
void replace_Aj(int k, grammar & g1) {

    // ��� ������������ ����, ��� �� ��� �������� �������, � ������ ����� ���������, � �� ��������
    int flag = 0;

    RULE rule_k = g1[k];

    SYMB Aj = rule_k[1];

    int rule_count = g1.count();

    // ���� ������� ���������, ��� ������� ����� ���������� ��������� � Aj
    for (int j = 1; j < rule_count; j++) {

        RULE rule_new;

        RULE rule_j = g1[j];

        if (rule_j[0] == Aj) {
            compile_rule(rule_k, rule_j, rule_new);

            if (flag == 0) {
                // ��������� ����� ������� � �������� �� ������� � �������� ���������
                g1[k] = rule_new;
                flag = 1;
            }
            else {
                // ��������� ����� ������� � ��������� ��� � �������� ���������
                g1.rule_add(rule_new);
            }
        }
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
        for (int k = 1; k < rule_count; k++) {

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

    for (SYMB A = 1; A <= last; A++) {

        // ��������� ����� ��������
        if (g1.is_symbol_leftr(-A)) {
            eliminate_direct(-A, g1);
            last = g1.nont_count();
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
