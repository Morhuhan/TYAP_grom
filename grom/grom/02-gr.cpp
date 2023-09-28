// 2018 ReVoL Primer Template
// 02-gr.cpp (группирование правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 02 -gr

// группирует правила в порядке появления нетерминалов
void group_rules(grammar & g1, grammar & g2) {
    SSET P;
    SSET Q;

    SYMB S = g1.start();

    Q.insert(S);

    int rule_count = g1.count();

    // Пока Q не пусто выполнять
    while (Q.count() > 0) {

        // Пусть A - первый элемент мн-ва Q
        SYMB A = Q[1];

        // Добавим A в P
        P.insert(A);

        // Исключим из Q первый элемент
        Q.remove(1);

        // Просматриваем правила g1 от r=1 до r=rule_count
        for (int r = 1; r <= rule_count; r++) {

            // rule - правило r из граматики g1
            RULE rule = g1[r];

            // Если левый нетерминал rule совпадает с A
            if (rule[0] == A) {

                // Добавим rule в g2
                g2.rule_add(rule);

                // Пусть symbol_count — количество символов правила rule.
                int symbol_count = rule.count();

                // Просматриваем символы rule от s = 1 до s = symbol_count.
                for (int s = 1; s <= symbol_count; s++) {

                    // Пусть B — символ s правила rule.
                    SYMB B = rule[s];

                    // Если B — нетерминал, то 
                    if (B < 0) {

                        // Если B отсутствует в P
                        if (P.misses(B)) {

                            // включим его в Q.
                            Q.insert(B);

                        }
                    }
                }
            }
        }
    }

    // Установить целевой символ G2 равным целевому символу G1
    g2.set_start_from(g1);
}

// точка входа в алгоритм
// группирование правил
int algorithm_group_rules(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    group_rules(g1, g2);
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
.02.sxg
<S>
<A>=<S><A>
<A>=<B>
<B>=[b]
<A>=[a]
<S>=<B>
<S>=<A><B>
/*/
