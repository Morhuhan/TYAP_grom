// 2018 ReVoL Primer Template
// main.h (описания констант, типов и функций основного модуля)
#pragma once
#include <windows.h>

// константы типа входного файла
enum SOURCE_TYPE { SOURCE_INVALID, SOURCE_GRAMMAR, SOURCE_FA, SOURCE_REGEX };

// максимальная длина спецификации
#define MAX_FILE_SPEC 260

// открывает входной файл для чтения
int source_open(FILE ** source_file, const char * path, SOURCE_TYPE & source_type);

// открывает результирующий файл для записи
int target_open(FILE ** target_file, const char * path);

// ключи возможных действий
enum ACTION_KEY { 
    /* общие действия с грамматикой             */ ACT_NONE = 0,
    /* группирование правил грамматики          */ ACT_GR,
    /* устранение бесплодных символов           */ ACT_US,
    /* устранение недостижимых символов         */ ACT_UR,
    /* устранение пустых правил                 */ ACT_RE,
    /* устранение цепных правил                 */ ACT_RC,
    /* устранение левой рекурсии                */ ACT_LR,
    /* левая факторизация                       */ ACT_LF,
    /* приведение к нормальной форме Хомского   */ ACT_CNF,
    /* удаление недостижимых состояний автомата */ ACT_FAUS,
    /* преобразование автомата в грамматику     */ ACT_FAAU,
    /* преобразование грамматики в автомат      */ ACT_AUFA,
    /* детерминизация автомата                  */ ACT_DFA,
    /* инвертирование автомата                  */ ACT_FAINV,
    /* минимизация ДКА                          */ ACT_MINFA,
    /* преобразование выражения в автомат       */ ACT_REXFA,
    /* преобразование автомата в выражение      */ ACT_FAREX
};

// АЛГОРИТМЫ
// 01. ознакомительные действия
int algorithm_general(grammar & g1, FILE * target);
// 02. группирование правил
int algorithm_group_rules(grammar & g1, FILE * target);
// 03. устранение бесплодных символов
int algorithm_remove_useless(grammar & g1, FILE * target);
// 04. устранение недостижимых символов
int algorithm_remove_unreachable(grammar & g1, FILE * target);
// 05. устранение пустых правил
int algorithm_remove_empty(grammar & g1, FILE * target);
// 06. устранение цепных правил
int algorithm_remove_units(grammar & g1, FILE * target);
// 07. устранение левой рекурсии
int algorithm_eliminate_leftr(grammar & g1, FILE * target);
// 08. левая факторизация
int algorithm_left_factoring(grammar & g1, FILE * target);
// 09. приведение к нормальной форме Хомского
int algorithm_chomsky_normal_form(grammar & g1, FILE * target);
// 10. устранение недостижимых состояний автомата
int algorithm_fa_remove_unreachable(NFA & fa, FILE * target);
// 11. преобразование автомата в грамматику
int algorithm_fa_to_grau(NFA & fa, grammar & gr, FILE * target);
// 12. преобразование грамматики в автомат
int algorithm_grau_to_fa(grammar & gr, NFA & fa, FILE * target);
// 13. преобразование НКА в ДКА
int algorithm_dfa(NFA & fa, FILE * target);
// 14. инвертирование автомата
int algorithm_fa_invert(NFA & fa, FILE * target);
// 15. минимизация ДКА
int algorithm_min_dfa(NFA & fa, FILE * target);
// 16. преобразование выражения в автомат
int algorithm_rex_to_fa(char * rex, NFA & fa, FILE * target);
// 17. преобразование автомата в выражение
int algorithm_fa_to_rex(NFA & fa, char * rex, FILE * target);

// ДЕЙСТВИЯ
// 01. ознакомительные действия с грамматикой
int action_grammar_general(grammar & g1);
// 02. группирование правил
int action_group_rules(grammar & g1);
// 03. устранение бесплодных символов
int action_remove_useless(grammar & g1);
// 04. устранение недостижимых символов
int action_remove_unreachable(grammar & g1);
// 05. устранение пустых правил
int action_remove_empty(grammar & g1);
// 06. устранение цепных правил
int action_remove_units(grammar & g1);
// 07. устранение левой рекурсии
int action_eliminate_leftr(grammar & g1);
// 08. левая факторизация
int action_left_factoring(grammar & g1);
// 09. приведение к нормальной форме Хомского
int action_chomsky_normal_form(grammar & g1);
// 10. удаление недостижимых состояний автомата
int action_fa_remove_unreachable(NFA & fa);
// 11. преобразование автомата в грамматику
int action_fa_to_grau(NFA & fa, grammar & gr);
// 12. преобразование грамматики в автомат
int action_grau_to_fa(grammar & gr, NFA & fa);
// 13. преобразование НКА в ДКА
int action_dfa(NFA & fa);
// 14. инвертирование автомата
int action_fa_invert(NFA & fa);
// 15. минимизация ДКА
int action_min_dfa(NFA & fa);
// 16. преобразование выражения в автомат
int action_rex_to_fa(char * rex, NFA & fa);
// 17. преобразование автомата в выражение
int action_fa_to_rex(NFA & fa, char * rex);

// определяет действие по ключу
ACTION_KEY get_key(char * buf);
// сбрасывает указатель выражения
void reset_rex_pointer(void);
// записывает знак в выражение
void char_to_rex(char c);
// очищает буфер выражения
void clear_regex();
// исключение
void except(const char * err);
// справка
void help();
