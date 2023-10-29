// 2018 ReVoL Primer Template
// 03-us.cpp (устранение бесплодных символов)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 03 -us

// возвращает 1, если:
//                rule содержит только терминалы (терминальную цепочку)
//                rule содержит нетерминалы, но они уже есть в R
// возвращает 0, если:
//                rule содержит нетерминалы, и их нет в R
int are_known_syms(RULE rule, SSET R) {

    // Пусть symbol_count — количество символов тела правила rule.
    int symbol_count = rule.count();

    // Просматриваем символы rule от s = 1 до s = symbol_count.
    for (int s = 1; s <= symbol_count; s++) {

        //Пусть A — символ s правила rule.
        SYMB A = rule[s];

        // Добавил это условие
        if (A > 0 && R.contains(A)) {
            continue;
        }

        // Если A — нетерминал и A не входит в R, то вернуть 0, конец.
        if (A < 0 && R.misses(A)) {
            return 0;
        }
    }
    return 1;
}


// формирует множество полезных нетерминалов
void find_usefull_syms(grammar & g1, SSET & R) {

    // Пусть rule_count — количество правил G1.
    int rule_count = g1.count();

    // Бесконечно выполнять 3-8.
    while(1) {

        // Пусть fix равно количество символов R.
        int fix = R.count();
        
        // Просматриваем правила G1 от r = 1 до r = rule_count.
        for (int r = 1; r <= rule_count; r++) {

            // Пусть rule — правило r грамматики G1
            RULE rule = g1[r];

            // Если rule не содержит нетерминалов, которых нет в R, то 7.
            if (are_known_syms(rule, R)) {

                // Включить левый нетерминал rule в R.
                R.insert(rule[0]);
            }
        }

        // Если fix равно количеству символов R, то выполнить 9.
        if (fix == R.count()) {
            break;
        }
    }
}

// записывает в g2 правила, нетерминалы которых принадлежат R
void find_usefull_rules(grammar & g2, grammar & g1, SSET R) {

    // Пусть rule_count — количество правил G1
    int rule_count = g1.count();

    // Просматриваем правила G1 от r = 1 до r = rule_count.
    for (int r = 1; r <= rule_count; r++) {

        // Пусть rule — правило r грамматики G1
        RULE rule = g1[r];

        // Если левый нетерминал rule входит в R, то 5
        if (R.contains(rule[0])) {

            // Если rule не содержит нетерминалов, которых нет в R, то 6.
            if (are_known_syms(rule, R)) {

                // Добавить правило rule в G2.
                g2.rule_add_from(g1, rule);
            }
        }
    }
}

// удаляет бесплодные символы
void remove_useless(grammar & g1, grammar & g2) {

    SSET R; // Изначально заполняем терминалами из g1

    // Просматриваем правила
    for (int r = 1; r < g1.count()+1; r++) {
        RULE rule = g1[r];
        int flag = 1;
        // Просматриваем правую часть правила
        for (int s = 1; s < rule.count()+1; s++) {

            // Если находим нетерминал - это правило не подходит
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

    // Множество R полезных нетерминальных смволов
    find_usefull_syms(g1, R);

    find_usefull_rules(g2, g1, R);

    g2.set_start_from(g1);
}

// точка входа в алгоритм
// устранение бесплодных символов
int algorithm_remove_useless(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // устранение бесплодных символов
    remove_useless(g1, g2);
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
.03.sxg
<S>
<S>=[a]
<S>=<A>
<A>=<A><B>
<B>=<C>
<C>=[b]
/*/

