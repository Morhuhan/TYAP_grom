// 2018 ReVoL Primer Template
// 13-dfa.cpp (преобразование НКА в ДКА)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a13a -dfa
// a13e -dfa
// a13b -dfa

// исследованные состояния
SSET inspected;

// вычисляет замыкание A состояния НКА state
void closure(SYMB state, SSET & A, NFA & fa1) {
}

// вычисляет замыкание A состояния ДКА A
void closureA(SSET & A, NFA & fa1) {
}

// вычисляет 2^(n-1)
int power2n(int n) {
    return 0;
}

// вычисляет идентификатор состояния ДКА, регистрирует его
// регистрирует финальное состояние, если есть
int reg_state(SSET & A, NFA & fa1, NFA & fa2) {
    return 0;
}

// ищет другие состояния
// A - состояние ДКА - множество состояний НКА
// initial - признак начального состояния
int follow_dfa_state(SSET A, NFA fa1, NFA & fa2, int initial = 0) {
    return 1;
}

// преобразует НКА в ДКА
int nfa_to_dfa(NFA & fa1, NFA & fa2) {
    inspected.clear();
    return follow_dfa_state(fa1.initials, fa1, fa2, 1);
}

// точка входа в алгоритм
// преобразование НКА в ДКА
int algorithm_dfa(NFA & fa1, FILE * target) {
    // выходной КА
    NFA fa2;
    // алгоритм
    int result = nfa_to_dfa(fa1, fa2);
    // выводим КА в консоль
    fa2.printn(stdout);
    // выводим КА в файл
    fa2.printn(target);
    // выходной КА
    fa1 = fa2;
    // результат
    return result;
}
/*/
.a13a.sxg
{A}
(A,a)={A}
(A,a)={B}
(A,b)={A}
(B,b)={C}
{C}
/*/
/*/
.a13e.sxg
{1}
(1, )={2,8}
(2, )={3,5}
(3,a)={4}
(4, )={7}
(7, )={2}
(5,b)={6}
(6, )={7}
(7, )={8}
{8}
/*/
