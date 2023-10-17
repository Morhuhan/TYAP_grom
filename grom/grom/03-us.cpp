// 2018 ReVoL Primer Template
// 03-us.cpp (���������� ���������� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 03 -us

// ���������� 1, ���� ������� ��������
int are_known_syms(RULE rule, SSET R) {

    // ����� symbol_count � ���������� �������� ���� ������� rule.
    int symbol_count = rule.count();

    // ������������� ������� rule �� s = 1 �� s = symbol_count.
    for (int s = 1; s <= symbol_count; s++) {

        //����� A � ������ s ������� rule.
        SYMB A = rule[s];

        // ���� A � ���������� � A �� ������ � R, �� ������� 1, �����.
        if (A < 0 && R.misses(A)) {
            return 1;
        }
    }

    // ���� ��� ������� �����������, ������� 0.
    return 0;
}


// ��������� ��������� �������� ������������
void find_usefull_syms(grammar & g1, SSET & R) {

    int flag = 1;

    // ����� rule_count � ���������� ������ G1.
    int rule_count = g1.count();

    // ���������� ��������� 3-8.
    while(flag) {
        
        // ����� fix ����� ���������� �������� R.
        int fix = R.count();

        // ������������� ������� G1 �� r = 1 �� r = rule_count.
        for (int r = 1; r <= rule_count; r++) {

            // ����� rule � ������� r ���������� G1
            RULE rule = g1[r];

            // ���� rule �� �������� ������������, ������� ��� � R, �� 7.
            if (!are_known_syms(rule, R)) {

                // �������� ����� ���������� rule � R.
                R.insert(rule[0]);

                // ���� fix ����� ���������� �������� R, �� ��������� 9.
                if (fix == R.count()) {
                    flag = 0;
                    break;
                }
            }
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
            if (!are_known_syms(rule, R)) {

                // �������� ������� rule � G2.
                g2.rule_add(rule);
            }
        }
    }
}

// ������� ���������� �������
void remove_useless(grammar & g1, grammar & g2) {

    SSET R;

    // ��������� R �������� �������������� �������
    find_usefull_syms(g1, R);

    // 
    find_usefull_rules(g2, g1, R);

    // �������� �������������� �������� �� g1 � g2
    for (int i = 0; i <= MAX_TERM + MAX_NONT; i++) {
        strncpy(g2.ident[i], g1.ident[i], MAX_ID);
    }

    g2.set_start_from(g1);

    int flag = 1;
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

// � ���������  ���������� = �����������

// �� ��������� R ��� ��������� �� ���������?

// ����������� (����������) ?
// <S> = <A>
// <A> = <A><B>