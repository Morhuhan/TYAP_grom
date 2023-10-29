// 2018 ReVoL Primer Template
// 04-ur.cpp (���������� ������������ ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 03 -us -ur -gr

// ��������� ����������� ������� rule � ��������� R
void find_rule_syms(RULE rule, SSET & R) {

    int symbol_count = rule.count();

    for (int s = 1; s <= symbol_count; s++) {

        SYMB A = rule[s];

        if (A < 0) {
            R.insert(A);
        }
    }
}

// ��������� ��������� ���������� ��������
void find_reachable_syms(grammar & g1, SSET & R) {

    int rule_count = g1.count();

    while (1) {

        // ����� fix ����� ���������� �������� R.
        int fix = R.count();

        // ������������� ������� G1 �� r = 1 �� r = rule_count.
        for (int r = 1; r <= rule_count; r++) {
            
            // ����� rule � ������� r ���������� G1
            RULE rule = g1[r];

            // ���� ����� ���������� ������� rule ���� � R
            if (R.contains(rule[0])) {

                // �������� ����������� ���� rule � R
                find_rule_syms(rule, R);
            }
        }

        // ���� fix ����� ���������� �������� R, �� ��������� 9.
        if (fix == R.count()) {
            break;
        }
    }
}

// ���������� � g2 �������, ����� ������� ������� ����������� R
void find_reachable_rules(grammar & g2, grammar & g1, SSET R) {

    int rule_count = g1.count();

    for (int r = 1; r <= rule_count; r++) {

        RULE rule = g1[r];

        if (R.contains(rule[0])) {
            g2.rule_add_from(g1, rule);
        }
    }
}

// ������� ������������ �������
void remove_unreachable(grammar & g1, grammar & g2) {

    g2.set_start_from(g1);

    SSET R;

    R.insert(g1.start());

    find_reachable_syms(g1, R);

    find_reachable_rules(g2, g1, R);
}

// ����� ����� � ��������
// ���������� ������������ ��������
int algorithm_remove_unreachable(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ���������� ������������ ��������
    remove_unreachable(g1, g2);
    // ������� ���������� � �������
    g2.print(stdout);
    // ������� ���������� � ����
    g2.print(target);
    // �������� ����������
    g1 = g2;
    // ���������
    return 1;
}
