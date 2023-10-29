// 2018 ReVoL Primer Template
// 05-re.cpp (устранение пустых правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 05 -re -gr

// возвращает 1, если правило вырождающееся
int is_nullable_rule(RULE rule, SSET R) {

    int symbol_count = rule.count();

    if (!symbol_count) {
        return 1;
    }

    for (int s = 1; s <= symbol_count; s++) {
        
        SYMB X = rule[s];

        if (!R.contains(X)) {
            return 0;
        }
    }
    
    return 1;
}

// формирует множество вырождающихся нетерминалов R
void nullable_syms(grammar & g1, SSET & R) {

    int rule_count = g1.count();

    while (1) {

        int fix = R.count();

        for (int r = 1; r <= rule_count; r++) {

            RULE rule = g1[r];

            if (is_nullable_rule(rule, R)) {
                R.insert(rule[0]);
            }
        }

        if (fix == R.count()) {
            break;
        }
    }
}

// непустые правила копирует в g2
void useful_rules(grammar & g2, grammar g1) {

    int rule_count = g1.count();

    for (int r = 1; r <= rule_count; r++) {

        RULE rule = g1[r];

        if (rule.count() > 0) {
            g2.rule_add_from(g1, rule);
        }
    }
}

// удаляет символ N списка P из правила rule
// если полученное правило не пусто, добавляет его в g2
// рекурсивно вызывает себя для полученного остатка правила
// последовательно для символов N-1, N-2...
void remove_nullable_from(grammar & g2, RULE rule, SSET P, int N) {
    
    rule.remove(N);

    if (rule.count() > 0) {

        g2.rule_add(rule);

        remove_nullable_from(g2, rule, P, N-1);
    }
}

// формирует список вырождающихся символов правила
void rule_nullable_syms(RULE rule, SSET R, SSET & P) {

    int symbol_count = rule.count();

    for (int s = 1; s <= symbol_count; s++) {

        SYMB X = rule[s];

        if (R.contains(X)) {
            P.insert(s);
        }
    }
}

// формирует правила, компенсирующие удаленные пустые правила
void complement_rules(grammar& g2, SSET R) {

    int rule_count = g2.count();

    for (int r = 1; r <= rule_count; r++) {

        SSET P;

        RULE rule = g2[r];

        rule_nullable_syms(rule, R, P);

        int p_count = P.count();

        remove_nullable_from(g2, rule, P, p_count);
    }


}

// устраняет пустые правила
void remove_empty(grammar & g1, grammar & g2) {
    
    g2.set_start_from(g1);

    SSET R;

    nullable_syms(g1, R);

    useful_rules(g2, g1);

    if (R.count() == 0) {
        return;
    }

    complement_rules(g2, R);

    if (g2.count() != 1 && R.contains(g2.start())) {

        RULE rule;

        SYMB S1 = g2.get_star_nont(g1.start());
       
        rule[0] = S1;

        g2.rule_add(rule);

        rule.append(g2.start());

        g2.rule_add(rule);

        g2.set_start(S1);
    }

}

// точка входа в алгоритм
// устранение пустых правил
int algorithm_remove_empty(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    remove_empty(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return 1;
}
/*/
.05.sxg
<S>
<S>=<A><B>
<A>=[a]
<A>=<B><B>
<B>=[b]
<B>=.
/*/
