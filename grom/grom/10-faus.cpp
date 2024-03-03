// 2018 ReVoL Primer Template
// 10-faus.cpp (устранение недостижимых состояний автомата)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a13b -faus
// a10 -faus

// ознакомительные действия с автоматом
void fa_general(NFA & fa) {

    SYMB A = fa.reg_state_id("A");
    SYMB B = fa.reg_state_id("B");
    SYMB C = fa.reg_state_id("C");
    SYMB D = fa.reg_state_id("D");
    SYMB E = fa.reg_state_id("E");
    SYMB F = fa.reg_state_id("F");
    SYMB G = fa.reg_state_id("G");

    TRAN tran;
    tran.a = A;
    tran.b = B;
    tran.c = '0';
    fa.tran_add(tran);
    
    tran.a = A;
    tran.b = C;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = B;
    tran.b = D;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = C;
    tran.b = E;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = D;
    tran.b = C;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = D;
    tran.b = E;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = E;
    tran.b = B;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = E;
    tran.b = D;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = F;
    tran.b = D;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = G;
    tran.b = F;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = G;
    tran.b = E;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = G;
    tran.b = F;
    tran.c = '1';
    fa.tran_add(tran);

    fa.initials.insert(A);
    fa.finals.insert(D);
    fa.finals.insert(E);
}

// устранение недостижимых состояний конечного автомата
void fa_remove_unreachable(NFA & fa1, NFA & fa2) {
    
    //fa_general(fa2);
    
    int tran_count = fa1.delta_count();

    SSET R = fa1.initials;

    for (int s = 1; s <= R.count(); s++) {
        fa2.reg_initial_from(fa1, R[s]);
    }

    while (1) {

        int flag = 0;

        for (int t = 1; t <= tran_count; t++) {

            TRAN tran = fa1[t];

            if (R.contains(tran.a)) {

                if (!R.contains(tran.b)) {
                    R.insert(tran.b);
                    flag = 1;
                }
                else
                {
                    R.insert(tran.b);
                }
            }
        }

        if (flag == 0) { break; }
    }

    int finals_count = fa1.finals.count();

    for (int f = 1; f <= finals_count; f++) {
        SYMB fin = fa1.finals[f];
        if (R.contains(fin)) {
            fa2.reg_final_from(fa1, fin);
        }
    }

    for (int t = 1; t <= tran_count; t++) {
        TRAN tran = fa1[t];
        if (R.contains(tran.a) && R.contains(tran.b)) {
            fa2.tran_add_from(fa1, tran);
        }
    }

}

// точка входа в алгоритм
// устранение недостижимых состояний КА
int algorithm_fa_remove_unreachable(NFA & fa1, FILE * target) {
    // выходной КА
    NFA fa2;
    // алгоритм
    fa_remove_unreachable(fa1, fa2);
    // выводим КА в консоль
    fa2.printi(stdout);
    // выводим КА в файл
    fa2.printi(target);
    // результирующий КА
    fa1 = fa2;
    // результат
    return 1;
}
/*/
.a13b.sxg
{A}
(A,a)={A}
(A,b)={B}
(B,a)={A}
(B,a)={S}
{S}
/*/
