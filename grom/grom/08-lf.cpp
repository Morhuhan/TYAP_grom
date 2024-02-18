// 2018 ReVoL Primer Template
// 08-lf.cpp (����� ������������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 08 -lf -gr

// �������� pref ��������� ������� rule ?
int is_prefix_for(RULE rule, RULE pref) {

    int pref_symb_count = pref.count();

    int counter = 0;

    for (int s = 0; s <= pref_symb_count; s++) {

        if (rule[s] == pref[s]) {
            counter++;
        }
    }

    if (counter-1 == pref_symb_count) {
        return 1;
    }

    else
    {
        return 0;
    }
}

// ������������ ������� ��� ������� j
// ���������� ����� �������� ������� j
int max_prefix_for_rule_number(int j, grammar g1) {
    return 0;
}

// ���� ������� ������������ ����� ��� A
// ���������� ����� ��������
int find_prefix_for(SYMB A, grammar g1, RULE & pref) {

    int rule_count = g1.count();

    int prefix_count = 0;

    while (1) {

        prefix_count = 0;

        // ���� ������� � ������� ����� ������������
        for (int r = 1; r < rule_count; r++) {

            RULE rule = g1[r];

            // ���� ����� ����� �������, ���������� ��� � ������� ���������
            if (rule[0] == A) {

                // ���� ������ ����� ������� ����� �������� ��������
                if (is_prefix_for(rule, pref) == 1) {
                    prefix_count++;
                }
            }
        }

        // ���� ������� ������� � ������� ���������
        if (prefix_count > 1) {
            return pref.count();
        }

        // ����� - ��������� ������� � ���������� ������
        else {

            pref.remove();

            // ���� ����� ���������� ����� ������� ����� ����
            if (pref.count() == 0) {
                return 0;
            }
        }
    }
}

// ��������� ������� pref ����������� pref[0]
void eliminate_prefix(grammar & g1, RULE pref) {

    int pref_symb_count = pref.count();

    int rule_count = g1.count();

    SYMB A1 = g1.get_new_nont();;

    for (int r = 1; r <= rule_count; r++) {

        RULE rule = g1[r];

        if (rule[0] == pref[0] && is_prefix_for(g1[r], pref) == 1)  {
            
            RULE temp_rule;

            temp_rule[0] = A1;

            for (int j = pref_symb_count+1; j <= g1[r].count(); j++) {
                temp_rule.append(g1[r][j]);
            }

            g1[r].clean();
            g1[r][0] = A1;

            for (int j = 1; j <= temp_rule.count(); j++) {
                g1[r].append(temp_rule[j]);
            }
        }
    }

    RULE temp_rule;

    temp_rule = pref;

    temp_rule.append(A1);

    g1.rule_add(temp_rule);

}

// �������� ����� ������������
int left_factoring(grammar & g1) {

    int found;

    int rule_count = g1.count();

    int max_size_prefix = 0;
    int temp_size_max_prefix = 0;

    RULE max_prefix_rule;

    while (1) {

        found = 0;

        // ���������� ��� ����� ����������� ������
        for (int r = 1; r < rule_count; r++) {

            RULE rule = g1[r];

            SYMB left_nont = rule[0];

            temp_size_max_prefix = find_prefix_for(left_nont, g1, rule);

            if (temp_size_max_prefix > max_size_prefix) {
                max_size_prefix = temp_size_max_prefix;
                max_prefix_rule = rule;
            }
        }

        // �������� ����� ������� ��� �������� ����������� � ������� �������
        if (max_size_prefix != 0) {

            RULE pref;

            pref[0] = max_prefix_rule[0];

            for (int s = 1; s < max_size_prefix+1; s++) {
                pref.append(max_prefix_rule[s]);
            }

            // ���� ���������� ����� ������� - ��������� ���
            eliminate_prefix(g1, pref);

            found = 1;
        }

        if (found == 1) {
            break;
        }
    }

    return 1;
}

// ����� ����� � ��������
// ����� ������������
int algorithm_left_factoring(grammar & g1, FILE * target) {
    // ��������
    int result = left_factoring(g1);
    // ������� ���������� � �������
    g1.print(stdout);
    // ������� ���������� � ����
    g1.print(target);
    // ���������
    return result;
}
/*/
.08.sxg
<A>
<A>=[a][b][a][b]
<A>=[a][b][c][d]
<A>=[a][b][c][e]
<A>=[a][b][c][f]
/*/
