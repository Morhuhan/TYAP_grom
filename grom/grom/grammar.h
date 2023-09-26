// 2018 ReVoL Primer Template
// grammar.h
// описание классов библиотеки grammar.lib
#pragma once
// размер множества CSET
#define MAX_CSET 3
// размер множества SSET
#define MAX_SSET 63
// длина идентификатора
#define MAX_ID 7
// количество терминалов
#define MAX_TERM 31
// количество нетерминалов
#define MAX_NONT 31
// количество правил
#define MAX_RULE 31
// длина правой части правила
#define MAX_BODY 8
// длина идентификатора состояния
#define MAX_FA_ID 7
// количество состояний
#define MAX_FA_STATE MAX_SSET
// количество переходов
#define MAX_FA_DELTA 63
// длина входного выражения
#define MAX_INREX 63
// символ операции *
#define STAR '*'
// определение типа символа
typedef short SYMB;
// предварительные объявления классов
class CSET;
class SSET;
class RULE;
class grammar;
class TRAN;
class NFA;
// множество знаков
class CSET {
    // элементы
    char items[1 + MAX_CSET];
public:
    // конструктор по умолчанию
    CSET();
    // очищает объект
    void clear();
    // возвращает количество элементов
    int count();
    // добавляет элемент
    int insert(char item);
    // возвращает элемент
    char operator [] (int index);
    // сравнивает множества
    int operator == (CSET A);
};
// множество
class SSET {
    // элементы
    SYMB items[1 + MAX_SSET];
public:
    // конструктор по умолчанию
    SSET();
    // конструктор приведения
    SSET(SYMB item);
    // очищает объект
    void clear();
    // возвращает количество элементов
    int count();
    // определяет наличие элемента
    int contains(SYMB item);
    // определяет отсутствие элемента
    int misses(SYMB item);
    // добавляет элемент
    int insert(SYMB item);
    // удаляет элемент
    int remove(int index);
    // возвращает элемент
    SYMB operator [] (int index);
    // операция сравнения
    int operator == (SSET A);
};
// класс правила грамматики
class RULE {
    // символы
    SYMB symbols[4 + MAX_BODY];
public:
    // конструктор по умолчанию
    RULE();
    // очищает объект
    void clear();
    // очищает правую часть правила
    void clean();
    // длина правой части
    int count();
    // возвращает/устанавливает символ правила
    SYMB & operator [] (int index);
    // добавляет символ
    void append(SYMB symbol);
    // удаляет символ по номеру
    void remove(int index);
    // удаляет последний символ
    void remove(void);
    // операция равенства
    int operator == (RULE rule);
    // возвращает признак цепного правила
    int is_unit();
    // возвращает признак леворекурсивного правила
    int is_leftr();
};
// класс грамматики
class grammar {
    // правила
    RULE rules[1 + MAX_RULE];
    // идентификаторы символов
    char ident[2 + MAX_TERM + MAX_NONT][1 + MAX_ID];
public:
    // конструктор по умолчанию
    grammar();
    // очищает объект
    void clear();
    // возвращает количество правил
    int count();
    // возвращает количество терминалов
    int term_count();
    // возвращает количество нетерминалов
    int nont_count();
    // возвращает индекс целевого символа
    SYMB start();
    // устанавливает целевой символ
    void set_start(SYMB sym);
    // регистрирует целевой символ по идентификатору
    SYMB set_start_id(const char * id);
    // регистрирует целевой символ другой грамматики
    SYMB set_start_from(grammar gr);
    // возвращает правило по номеру
    RULE & operator [] (int index);
    // добавляет правило
    void rule_add(RULE rule);
    // добавляет правило другой грамматики
    void rule_add_from(grammar gr, RULE rule);
    // возвращает номер правила или 0
    int rule_exist(RULE rule);
    // преобразует правило другой грамматики в правило этой грамматики
    void rule_cast(grammar gr, RULE & rule);
    // регистрирует нетерминал
    SYMB reg_nont(const char * id);
    // регистрирует терминал
    SYMB reg_term(const char * id);
    // регистрирует символ как терминал
    SYMB reg_char(char c);
    // регистрирует символ другой грамматики
    SYMB reg_from(grammar gr, SYMB symbol);
    // регистрирует состояние КА как нетерминал грамматики
    SYMB reg_from(NFA fa, SYMB state);
    // формирует маркированный нетерминал и регистрирует его
    SYMB get_star_nont(SYMB sym);
    // формирует новый нетерминал и регистрирует его
    SYMB get_new_nont();
    // возвращает идентификатор символа
    char * getid(SYMB symbol);
    // возвращает первый символ терминала
    char get_char(SYMB tok);
    // возвращает признак леворекурсивного по правилу символа
    int is_symbol_leftr(SYMB sym);
    // анализирует целостность грамматики
    int analyse();
    // выводит текст правила в указанный поток
    void rule_print(FILE * stream, RULE rule);
    // выводит текст грамматики в указанный поток
    void print(FILE * stream);
    // разбирает файл грамматики
    int parse(FILE * input_stream, FILE * err_stream);
    // возвращает символ по идентификатору терминала
    SYMB find_term(const char * id);
    // возвращает символ по идентификатору нетерминала
    SYMB find_nont(const char * id);
private:
    // считывает из потока строку
    int parse_line(FILE * input_stream, FILE * err_stream);
};
// класс перехода КА
class TRAN {
public:
    SYMB a; // состояние
    char c; // символ перехода
    SYMB b; // состояние перехода
    char f; // атрибуты
    // конструктор по умолчанию
    TRAN();
    // операция равенства
    int operator == (TRAN t);
};
// класс конечного автомата (КА)
class NFA {
    // переходы
    TRAN delta[1 + MAX_FA_DELTA];
    // идентификаторы состояний
    char ident[1 + MAX_FA_STATE][1 + MAX_FA_ID];
public:
    // начальные состояния
    SSET initials;
    // финальные состояния
    SSET finals;
    // символы переходов
    SSET chars;
    // конструктор по умолчанию
    NFA();
    // очищает объект
    void clear();
    // возвращает количество переходов
    int delta_count();
    // возвращает количество состояний
    int state_count();
    // возвращает/устанавливает переход
    TRAN & operator [] (int index);
    // добавляет переход
    SYMB tran_add_immediate(SYMB a, char c, SYMB b);
    // добавляет переход
    SYMB tran_add(TRAN tran);
    // добавляет переход другого КА
    SYMB tran_add_from(NFA fa, TRAN tran);
    // регистрирует состояние
    SYMB reg_state_id(const char * id);
    // регистрирует состояние другого КА
    SYMB reg_state_from(NFA fa, SYMB state);
    // регистрирует символ грамматики как состояние
    SYMB reg_state_from(grammar gr, SYMB sym);
    // регистрирует начальное состояние
    SYMB reg_initial_id(const char * id);
    // регистрирует начальное состояние другого КА
    SYMB reg_initial_from(NFA fa, SYMB state);
    // регистрирует символ грамматики как начальное состояние
    SYMB reg_initial_from(grammar gr, SYMB sym);
    // регистрирует финальное состояние
    SYMB reg_final_id(const char * id);
    // регистрирует финальное состояние другого КА
    SYMB reg_final_from(NFA fa, SYMB state);
    // регистрирует символ грамматики как финальное состояние
    SYMB reg_final_from(grammar gr, SYMB sym);
    // формирует новое состояние и регистрирует его
    SYMB get_new_state();
    // возвращает идентификатор состояния
    char * getid(SYMB state);
    // анализирует КА
    int analyse();
    // выводит текст перехода КА в указанный поток
    void trans_printi(FILE * stream, TRAN tran);
    // выводит текст перехода КА в указанный поток
    void trans_printn(FILE * stream, TRAN tran);
    // выводит текст КА в указанный поток
    void printn(FILE * stream);
    // выводит текст КА в указанный поток
    void printi(FILE * stream);
    // разбирает файл КА
    int parse(FILE * input_stream, FILE * err_stream);
private:
    // возвращает состояние по идентификатору или 0
    SYMB find_state(const char * id);
    // считывает из потока строку
    int parse_line(FILE * input_stream, FILE * err_stream);
};
