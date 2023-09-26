// 2018 ReVoL Primer Template
// 17-farex.cpp (преобразование автомата в выражение)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a17 -farex

/* объ€вление используемых функций */
// сбрасывает указатель выражени€
void reset_rex_pointer(void);

// записывает знак в выражение
void char_to_rex(char c);

// прототип функции
int has_tran_from_final(SYMB A, NFA & fa);
/* конец объ€влений используемых функций */

// таблица коэффициентов
CSET COT[MAX_FA_STATE][MAX_FA_STATE];

// выводит плюс
void putplus(char * rex, int & plus) {
}

// выводит коэффициент
void coeff(char * rex, CSET C) {
}

// решение дл€ состо€ни€ A
void solve(SYMB A, NFA fa, char * rex) {
}

// преобразует конечный автомат в регул€рное выражение
// исходный автомат должен быть ћ»Ќ»ћ»јЋ№Ќџћ
int fa_to_rex(NFA & fa, char * rex) {
    return 1;
}

// точка входа в алгоритм
// преобразование автомата в выражение
int algorithm_fa_to_rex(NFA & fa, char * rex, FILE * target) {
    // алгоритм
    int result = fa_to_rex(fa, rex);
    // выводим выражение в консоль
    fprintf(stdout, "%s\n\n", rex);
    // выводим выражение в файл
    fprintf(target, "%s\n", rex);
    // результат
    return result;
}
/*/
.a17
{A}
(A,a)={B}
(B,b)={B}
{B}
/*/
