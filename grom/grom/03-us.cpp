// 2018 ReVoL Primer Template
// 03-us.cpp (устранение бесплодных символов)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 03 -us

// возвращает 1, если правило полезное
int are_known_syms(RULE rule, SSET R) {

    // Пусть symbol_count — количество символов тела правила rule.
    int symbol_count = rule.count();

    // Просматриваем символы rule от s = 1 до s = symbol_count.
    for (int s = 1; s <= symbol_count; s++) {

        //Пусть A — символ s правила rule.
        SYMB A = rule[s];

        // Если A — нетерминал и A не входит в R, то вернуть 1, конец.
        if (A < 0 && R.misses(A)) {
            return 1;
        }
    }

    // Если все символы просмотрены, вернуть 0.
    return 0;
}


// формирует множество полезных нетерминалов
void find_usefull_syms(grammar & g1, SSET & R) {

    int flag = 1;

    // Пусть rule_count — количество правил G1.
    int rule_count = g1.count();

    // Бесконечно выполнять 3-8.
    while(flag) {
        
        // Пусть fix равно количество символов R.
        int fix = R.count();

        // Просматриваем правила G1 от r = 1 до r = rule_count.
        for (int r = 1; r <= rule_count; r++) {

            // Пусть rule — правило r грамматики G1
            RULE rule = g1[r];

            // Если rule не содержит нетерминалов, которых нет в R, то 7.
            if (!are_known_syms(rule, R)) {

                // Включить левый нетерминал rule в R.
                R.insert(rule[0]);

                // Если fix равно количеству символов R, то выполнить 9.
                if (fix == R.count()) {
                    flag = 0;
                    break;
                }
            }
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
            if (!are_known_syms(rule, R)) {

                // Добавить правило rule в G2.
                g2.rule_add(rule);
            }
        }
    }
}

// удаляет бесплодные символы
void remove_useless(grammar & g1, grammar & g2) {

    SSET R;

    // Множество R полезных нетерминальных смволов
    find_usefull_syms(g1, R);

    // 
    find_usefull_rules(g2, g1, R);

    // Копируем идентификаторы символов из g1 в g2
    for (int i = 0; i <= MAX_TERM + MAX_NONT; i++) {
        strncpy(g2.ident[i], g1.ident[i], MAX_ID);
    }

    g2.set_start_from(g1);

    int flag = 1;
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

// В контексте  бесплодные = бесполезные

// Во множестве R все терминалы по умолчанию?

// Бесполезные (Бесплодные) ?
// <S> = <A>
// <A> = <A><B>