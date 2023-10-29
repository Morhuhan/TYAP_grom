// 2018 ReVoL Primer Template
// 03-us.cpp (���������� ���������� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 03 -us

// ���������� 1, ����:
//                rule �������� ������ ��������� (������������ �������)
//                rule �������� �����������, �� ��� ��� ���� � R
// ���������� 0, ����:
//                rule �������� �����������, � �� ��� � R
int are_known_syms(RULE rule, SSET R) {

    // ����� symbol_count � ���������� �������� ���� ������� rule.
    int symbol_count = rule.count();

    // ������������� ������� rule �� s = 1 �� s = symbol_count.
    for (int s = 1; s <= symbol_count; s++) {

        //����� A � ������ s ������� rule.
        SYMB A = rule[s];

        // ������� ��� �������
        if (A > 0 && R.contains(A)) {
            continue;
        }

        // ���� A � ���������� � A �� ������ � R, �� ������� 0, �����.
        if (A < 0 && R.misses(A)) {
            return 0;
        }
    }
    return 1;
}


// ��������� ��������� �������� ������������
void find_usefull_syms(grammar & g1, SSET & R) {

    // ����� rule_count � ���������� ������ G1.
    int rule_count = g1.count();

    // ���������� ��������� 3-8.
    while(1) {

        // ����� fix ����� ���������� �������� R.
        int fix = R.count();
        
        // ������������� ������� G1 �� r = 1 �� r = rule_count.
        for (int r = 1; r <= rule_count; r++) {

            // ����� rule � ������� r ���������� G1
            RULE rule = g1[r];

            // ���� rule �� �������� ������������, ������� ��� � R, �� 7.
            if (are_known_syms(rule, R)) {

                // �������� ����� ���������� rule � R.
                R.insert(rule[0]);
            }
        }

        // ���� fix ����� ���������� �������� R, �� ��������� 9.
        if (fix == R.count()) {
            break;
        }
    }
}

// ���������� � g2 �������, ����������� ������� ����������� R
void find_usefull_rules(grammar & g2, grammar & g1, SSET R) {

    // ����� rule_count � ���������� ������ G1
    int rule_count = g1.count();

    // ������������� ������� G1 �� r = 1 �� r = rule_count.
    for (int r = 1; r <= rule_count; r++) {

        // ����� rule � ������� r ���������� G1
        RULE rule = g1[r];

        // ���� ����� ���������� rule ������ � R, �� 5
        if (R.contains(rule[0])) {

            // ���� rule �� �������� ������������, ������� ��� � R, �� 6.
            if (are_known_syms(rule, R)) {

                // �������� ������� rule � G2.
                g2.rule_add_from(g1, rule);
            }
        }
    }
}

// ������� ���������� �������
void remove_useless(grammar & g1, grammar & g2) {

    SSET R; // ���������� ��������� ����������� �� g1

    // ������������� �������
    for (int r = 1; r < g1.count()+1; r++) {
        RULE rule = g1[r];
        int flag = 1;
        // ������������� ������ ����� �������
        for (int s = 1; s < rule.count()+1; s++) {

            // ���� ������� ���������� - ��� ������� �� ��������
            if (rule[s] < 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            for (int s = 1; s < rule.count()+1; s++) {
                R.insert(rule[s]);
            }
        }
    }

    // ��������� R �������� �������������� �������
    find_usefull_syms(g1, R);

    find_usefull_rules(g2, g1, R);

    g2.set_start_from(g1);
}

// ����� ����� � ��������
// ���������� ���������� ��������
int algorithm_remove_useless(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ���������� ���������� ��������
    remove_useless(g1, g2);
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
.03.sxg
<S>
<S>=[a]
<S>=<A>
<A>=<A><B>
<B>=<C>
<C>=[b]
/*/

