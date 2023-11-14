// 2018 ReVoL Primer Template
// 07-lr.cpp (устранение левой рекурсии)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 07 -lr -gr

// устран€ет непосредственную рекурсию правил дл€ A
void eliminate_direct(SYMB Ai, grammar & g1) {
}

// формирует новое правило из двух
void compile_rule(RULE rule_k, RULE rule_j, RULE & rule_new) {
}

// замен€ет правило Ak->Ajx на правила Ak->wx, w - правые части Aj
// k - номер правила Ak->Ajx
void replace_Aj(int k, grammar & g1) {

    RULE rule_k = g1[k];

    SYMB Aj = rule_k[1];

    RULE rule_new;

    for (int j = 0; j < length; j++) {

    }

}

// преобразует не€вную рекурсию в €вную
// дл€ нетерминалов от первого до Ak
// замен€ет правила вида Ak->Ajx на Ak->wx, w - правые части Aj
void indirect_to_direct(SYMB Ak, grammar & g1) {

    int rule_count = g1.count();

    // ѕеребераем символы с индексом < k
    for (SYMB Aj = 1; Aj < Ak ; Aj++) {

        // ƒл€ каждого символа просматриваем все правила
        for (int k = 0; k < rule_count; k++) {

            RULE rule = g1[k];

            // »щем такие правила, где слева исследуемый нетерминал Ak, а справа нетерминал
            // с индексом j, который меньше по абсолютному значению, чем k
            if ((rule[0] == -Ak) && (rule[1] == -Aj)) {

                // «аемен€ем тело правила на тела правил дл€ Aj
                replace_Aj(k, g1);
            }
        }
    }
}

// устран€ет левую рекурсию
void eliminate_leftr(grammar & g1) {

    // »ндекс последнего нетерминала
    SYMB last = g1.nont_count();

    for (SYMB A = 1; ; A++) {

        // ”стран€ем €вную рекурсию
        if (g1.is_symbol_leftr(-A)) {
            eliminate_direct(-A, g1);
        }

        // ”слови€ выхода
        if (A == last) {
            break;
        }

        // ”стран€ем не€вную рекурсию
        else {
            indirect_to_direct(A + 1, g1);
        }
    }
}

// точка входа в алгоритм
// устранение левой рекурсии
int algorithm_eliminate_leftr(grammar & g1, FILE * target) {
    // алгоритм
    eliminate_leftr(g1);
    // выводим грамматику в консоль
    g1.print(stdout);
    // выводим грамматику в файл
    g1.print(target);
    // результат
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
