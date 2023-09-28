// 2018 ReVoL Primer Template
// 01-gen.cpp (ознакомительные действия)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 001

// упражнение 1
void test1 (grammar & g1, grammar & g2) {
    SYMB S = g2.reg_nont("S");
    SYMB A = g2.reg_nont("A");
    SYMB B = g2.reg_nont("B");
    SYMB a = g2.reg_term("a");
    SYMB b = g2.reg_term("b");

    RULE rule;
    rule[0] = S;
    rule.append(A);
    rule.append(B);

    g2.rule_add(rule);

    g2.set_start(S);

    rule.clear();

    rule[0] = A;
    rule.append(a);
    g2.rule_add(rule);

    rule.clean();
    rule.append(B);
    rule.append(B);
    g2.rule_add(rule);

    rule.clear();
    rule[0] = B;
    rule.append(b);
    g2.rule_add(rule);

    rule.clean();
    g2.rule_add(rule);
}

// упражнение 2, 3, 4
void test2 (grammar & g1, grammar & g2) {

    SYMB a = g1.find_term("a");

    g2.set_start_from(g1);

    // Перебор правил
    int rule_count = g1.count();
    for (int r = 1; r <= rule_count; r++) {
        RULE rule = g1[r];
        int symbol_count = rule.count();
        // Перебор символов правил
        for (int s = 1; s <= symbol_count; s++) {
            // Узнаем, является ли символ терминальным
            if (rule[s] < 0) {
                printf("nont ");
            }
            else {
                printf("term");
            }
            printf("\n");

            // Заменяем символ на a
            rule[s] = a;
        }
        g2.rule_add_from(g1, rule);
    }
}

// упражнение 5
void test3 (grammar & g1, grammar & g2) {
    SSET R;

    // Включаем целевой символ в множество достяжимых символов R
    R.insert(g1.start());
    int rule_count = g1.count();

    while (1) {
        int fix = R.count();

        for (int r = 1; r <= rule_count; r++) {
            RULE rule = g1[r];

            if (R.contains(rule[0])) {
                int symbol_count = rule.count();
                
                for (int s = 1; s <= symbol_count; s++) {
                    SYMB A = rule[s];
                    if (A < 0) R.insert(A);

                }
            }

        }
        if (fix == R.count()) break;
    }

    int symbol_count = R.count();
    
    for (int s = 1; s <= symbol_count; s++) {
        printf("%s\n", g1.getid(R[s]));
    }
}

// алгоритмы общих действий с грамматикой
void grammar_general(grammar & g1, grammar & g2) {
    //test1(g1, g2);
    //test2(g1, g2);
    //test3(g1, g2);
}

// точка входа в алгоритм
// общие действия с грамматикой
int algorithm_general(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    grammar_general(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    return 0;
}
/*/
.001.sxg
<S>
<S>=<S>[+]<T>
<S>=<T>
<T>=<T>[*]<P>
<T>=<P>
<P>=[a]
<P>=[(]<S>[)]
/*/
