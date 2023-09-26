// 2018 ReVoL Primer Template
// main.cpp
#include "stdafx.h"
#include "grammar.h"
#include "main.h"

#define MAXREX 512
// регулярное выражение
char rex[MAXREX];
// указатель выражения
int rexindex = 0;
// входная грамматика
grammar gr;
// входной конечный автомат
NFA fa;
// главная функция
// аргументы:
// 1  - входной файл
// 2+ - ключи вида "-идентификатор_ключа"
void mainf(int argc, char* argv[]) {
    SOURCE_TYPE source_type = SOURCE_GRAMMAR;
    FILE * source_file = 0;
    int i = 0, parse_result = 0;
    char c = 0;
    if (argc < 2) {
        help();
        return;
    }
    // открываем исходный файл для чтения
    if (!source_open(&source_file, argv[1], source_type)) {
        // ошибка открытия входного файла
        return;
    }
    if (source_type == SOURCE_FA) {
        // разбираем файл конечного автомата
        printf("-- parse automation\n");
        parse_result = fa.parse(source_file, stdout);
    } else if (source_type == SOURCE_GRAMMAR) {
        // разбираем файл грамматики
        printf("-- parse grammar\n");
        parse_result = gr.parse(source_file, stdout);
    } else {
        // результат по умолчанию
        parse_result = 1;
        // очищаем буфер
        clear_regex();
        for (i = 0; i <= MAX_INREX; i++) rex[i] = 0;
        // считываем регулярное выражение
        int n = 0;
        while (1) {
            if (n >= MAX_INREX) {
                parse_result = 0;
                printf("-- regex too long\n");
                break;
            }
            c = getc(source_file);
            if (c == EOF || c == 10 || c == 13) {
                break;
            } else if (c == '1' || c == '(' || c == ')' || c == '+' || c == STAR) {
                rex[n++] = c;
            } else if (c > 64 && c < 91) {
                rex[n++] = (c |= 32);
            } else if (c > 96 && c < 123) {
                rex[n++] = c;
            } else {
                continue;
            }
        }
        rex[n++] = 10;
    }
    // закрываем исходный файл
    fclose(source_file);
    if (parse_result <= 0) {
        // неуспешный разбор
        return;
    }
    if (argc < 3) {
        // ключей нет
        action_grammar_general(gr);
    } else try {
        // рассматриваем ключи
        for (int k = 2; k < argc; k++) {
            // получим ключ
            ACTION_KEY key = get_key(argv[k]);
            switch (key) {
            case ACT_GR:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_group_rules(gr) == 0) return;
                break;
            case ACT_US:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_remove_useless(gr) == 0) return;
                break;
            case ACT_UR:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_remove_unreachable(gr) == 0) return;
                break;
            case ACT_RE:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_remove_empty(gr) == 0) return;
                break;
            case ACT_RC:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_remove_units(gr) == 0) return;
                break;
            case ACT_LR:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_eliminate_leftr(gr) == 0) return;
                break;
            case ACT_LF:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_left_factoring(gr) == 0) return;
                break;
            case ACT_CNF:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_chomsky_normal_form(gr) == 0) return;
                break;
            case ACT_FAUS:
                if (source_type != SOURCE_FA) { printf("Automation source expected.\n\n"); return; }
                if (action_fa_remove_unreachable(fa) == 0) return;
                break;
            case ACT_AUFA:
                if (source_type != SOURCE_GRAMMAR) { printf("Grammar source expected.\n\n"); return; }
                if (action_grau_to_fa(gr, fa) == 0) return;
                // выходом алгоритма является конечный автомат
                source_type = SOURCE_FA;
                // входную грамматику очищаем
                gr.clear();
                break;
            case ACT_FAAU:
                if (source_type != SOURCE_FA) { printf("Automation source expected.\n\n"); return; }
                if (action_fa_to_grau(fa, gr) == 0) return;
                // выходом алгоритма является грамматика
                source_type = SOURCE_GRAMMAR;
                // входной КА очищаем
                fa.clear();
                break;
            case ACT_DFA:
                if (source_type != SOURCE_FA) { printf("Automation source expected.\n\n"); return; }
                if (action_dfa(fa) == 0) return;
                break;
            case ACT_FAINV:
                if (source_type != SOURCE_FA) { printf("Automation source expected.\n\n"); return; }
                if (action_fa_invert(fa) == 0) return;
                break;
            case ACT_MINFA:
                if (source_type != SOURCE_FA) { printf("Automation source expected.\n\n"); return; }
                if (action_min_dfa(fa) == 0) return;
                break;
            case ACT_REXFA:
                if (source_type != SOURCE_REGEX) { printf("Regular expression source expected.\n\n"); return; }
                if (action_rex_to_fa(rex, fa) == 0) return;
                // выходом алгоритма является автомат
                source_type = SOURCE_FA;
                break;
            case ACT_FAREX:
                if (source_type != SOURCE_FA) { printf("Automation source expected.\n\n"); return; }
                // очищаем буфер
                clear_regex();
                if (action_fa_to_rex(fa, rex) == 0) return;
                // выходом алгоритма является выражение
                source_type = SOURCE_REGEX;
                break;
            default:;
                printf("Unknown key \"%s\".\n\n", argv[k]);
            }
        }
    } catch (const char * err) {
        except(err);
    } catch (...) {
        except("Software");
    }
}

int main(int argc, char* argv[]) {
    __try {
        mainf(argc, argv);
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        unsigned int code = GetExceptionCode();
        if (code == EXCEPTION_ACCESS_VIOLATION) {
            except("Access violation");
        } else if (code == EXCEPTION_STACK_OVERFLOW) {
            except("Stack overflow");
        } else {
            except("Hardware");
        }
    }
}
// путь к файлу грамматики
char main_path[MAX_FILE_SPEC] = {0};
// спецификация файла грамматики
char ente_path[MAX_FILE_SPEC] = {0};
// определяет тип файла
SOURCE_TYPE get_source_type(FILE * source) {
    char c = 0;
    while (1) {
        c = getc(source);
        if (c == EOF) {
            fprintf(stdout, "\nUnexpected end of file.\n\n");
            return SOURCE_INVALID;
        } else if (c == 10) {
            fprintf(stdout, "\nInvalid file format.\n\n");
            return SOURCE_INVALID;
        } else if (c == 9 || c == 13 || c == 32) {
        } else {
            break;
        }
    }
    if (c == '<') {
        return SOURCE_GRAMMAR;
    } else if (c == '{') {
        return SOURCE_FA;
    } else {
        if (c == '(' || c == '1') {
            return SOURCE_REGEX;
        } else if (c > 64 && c < 91) {
            return SOURCE_REGEX;
        } else if (c > 96 && c < 123) {
            return SOURCE_REGEX;
        } else {
            return SOURCE_INVALID;
        }
    }
}
// открывает входной файл для чтения
int source_open(FILE ** source_file, const char * path, SOURCE_TYPE & source_type) {
    // копируем спецификацию файла
    strcpy(main_path, path);
    // положение точки с конца файла
    char * p = strrchr(main_path, '.');
    if (p) {
        // отрезаем расширение
        main_path[p - main_path] = 0;
    }
    // копируем путь
    strcpy(ente_path, main_path);
    // добавляем расширение
    strcat(ente_path, ".sxg");
    // открываем файл для чтения
    *source_file = fopen(ente_path, "rt");
    if (!*source_file) {
        if (errno == ENOENT) {
            printf("Source file or path not found \"%s\".\n\n", ente_path);
            return 0;
        } else {
            printf("Error open source file \"%s\".\n\n", ente_path);
            return 0;
        }
    }
    source_type = get_source_type(*source_file);
    if (source_type == SOURCE_INVALID) {
        printf("SYNAX format invalid in source file \"%s\".\n\n", ente_path);
        return 0;
    }
    freopen(ente_path, "rt", *source_file);
    return 1;
}
// открывает файл для записи результата
// добавляет к имени файла действие
int target_open(FILE ** target_file, const char * tail) {
    // добавляем хвостовую часть к пути
    strcat(main_path, tail);
    // копируем путь
    strcpy(ente_path, main_path);
    // добавляем расширение
    strcat(ente_path, ".sxg");
    // проверяем наличие файла
    FILE * f = fopen(ente_path, "rt");
    if (f) {
        fclose(f);
        DeleteFile((LPCSTR)ente_path);
    }
    // открываем файл для записи
    *target_file = fopen(ente_path, "wt");
    if (!*target_file) {
        if (errno == ENOENT) {
            printf("Target path not found \"%s\".\n\n", ente_path);
            return 0;
        } else {
            printf("Error open target file \"%s\".\n\n", ente_path);
            return 0;
        }
    }
    return 1;
}
// определяет действие по ключу
// ключ задается в командной строке и имеет вид "-identifier"
ACTION_KEY get_key(char * buf) {
    if (_stricmp("-gr",    buf) == 0) return ACT_GR;    // группирование правил грамматики
    if (_stricmp("-us",    buf) == 0) return ACT_US;    // устранение бесплодных символов
    if (_stricmp("-ur",    buf) == 0) return ACT_UR;    // устранение недостижимых символов
    if (_stricmp("-re",    buf) == 0) return ACT_RE;    // устранение пустых правил
    if (_stricmp("-rc",    buf) == 0) return ACT_RC;    // устранение цепных правил
    if (_stricmp("-lr",    buf) == 0) return ACT_LR;    // устранение левой рекурсии
    if (_stricmp("-lf",    buf) == 0) return ACT_LF;    // левая факторизация
    if (_stricmp("-cnf",   buf) == 0) return ACT_CNF;   // приведение к нормальной форме Хомского
    if (_stricmp("-faus",  buf) == 0) return ACT_FAUS;  // удаление недостижимых состояний автомата
    if (_stricmp("-aufa",  buf) == 0) return ACT_AUFA;  // преобразование автомата в грамматику
    if (_stricmp("-faau",  buf) == 0) return ACT_FAAU;  // преобразование грамматики в автомат
    if (_stricmp("-dfa",   buf) == 0) return ACT_DFA;   // детерминизация автомата
    if (_stricmp("-fainv", buf) == 0) return ACT_FAINV; // инвертирование автомата
    if (_stricmp("-minfa", buf) == 0) return ACT_MINFA; // минимизация ДКА
    if (_stricmp("-rexfa", buf) == 0) return ACT_REXFA; // преобразование выражения в автомат
    if (_stricmp("-farex", buf) == 0) return ACT_FAREX; // преобразование автомата в выражение
    return ACT_NONE;
}
// очищает буфер выражения
void clear_regex() {
    int count = sizeof(rex) / sizeof(char);
    for (int i = 0; i < count; i++) rex[i] = 0;
}
// сбрасывает указатель выражения
void reset_rex_pointer(void) {
    rexindex = 0;
}
// записывает знак в выражение
void char_to_rex(char c) {
    if (rexindex >= MAXREX) {
        throw "regex overflow";
    }
    rex[rexindex++] = c;
}
// 01 ознакомительные действия с грамматикой
int action_grammar_general(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-gen")) return 0;
    printf("-- grammar general\n");
    algorithm_general(gr, target_file);
    fclose(target_file);
    return 0;
}
// 02 группирование правил
int action_group_rules(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-gr")) return 0;
    printf("-- group rules\n");
    int result = algorithm_group_rules(gr, target_file);
    fclose(target_file);
    return result;
}
// 03 устранение бесплодных символов
int action_remove_useless(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-us")) return 0;
    printf("-- remove useless\n");
    int result = algorithm_remove_useless(gr, target_file);
    fclose(target_file);
    return result;
}
// 04 устранение недостижимых символов
int action_remove_unreachable(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-ur")) return 0;
    printf("-- remove unreachable\n");
    int result = algorithm_remove_unreachable(gr, target_file);
    fclose(target_file);
    return result;
}
// 05 устранение пустых правил
int action_remove_empty(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-re")) return 0;
    printf("-- remove empty\n");
    int result = algorithm_remove_empty(gr, target_file);
    fclose(target_file);
    return result;
}
// 06 устранение цепных правил
int action_remove_units(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-rc")) return 0;
    printf("-- remove units\n");
    int result = algorithm_remove_units(gr, target_file);
    fclose(target_file);
    return result;
}

// 07 устранение левой рекурсии
int action_eliminate_leftr(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-lr")) return 0;
    printf("-- eliminate left recursion\n");
    int result = algorithm_eliminate_leftr(gr, target_file);
    fclose(target_file);
    return result;
}
// 08 левая факторизация
int action_left_factoring(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-lf")) return 0;
    printf("-- left factoring\n");
    int result = algorithm_left_factoring(gr, target_file);
    fclose(target_file);
    return result;
}
// 09 приведение к нормальной форме Хомского
int action_chomsky_normal_form(grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-cnf")) return 0;
    printf("-- Chomsky normal form\n");
    int result = algorithm_chomsky_normal_form(gr, target_file);
    fclose(target_file);
    return result;
}
// 10 устранение недостижимых состояний автомата
int action_fa_remove_unreachable(NFA & fa) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-faus")) return 0;
    printf("-- fa remove unreachable\n");
    int result = algorithm_fa_remove_unreachable(fa, target_file);
    fclose(target_file);
    return result;
}
// 11 преобразование автомата в грамматику
int action_fa_to_grau(NFA & fa, grammar & gr) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-faau")) return 0;
    printf("-- fa to grammar\n");
    int result = algorithm_fa_to_grau(fa, gr, target_file);
    fclose(target_file);
    return result;
}
// 12 преобразование грамматики в автомат
int action_grau_to_fa(grammar & gr, NFA & fa) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-aufa")) return 0;
    printf("-- grammar to fa\n");
    int result = algorithm_grau_to_fa(gr, fa, target_file);
    fclose(target_file);
    return result;
}
// 13 преобразование НКА в ДКА
int action_dfa(NFA & fa) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-dfa")) return 0;
    printf("-- nfa to dfa\n");
    int result = algorithm_dfa(fa, target_file);
    fclose(target_file);
    return result;
}
// 14 инвертирование автомата
int action_fa_invert(NFA & fa) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-fainv")) return 0;
    printf("-- fa invert\n");
    int result = algorithm_fa_invert(fa, target_file);
    fclose(target_file);
    return result;
}

// 15 минимизация ДКА
int action_min_dfa(NFA & fa) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-minfa")) return 0;
    printf("-- min DFA\n");
    int result = algorithm_min_dfa(fa, target_file);
    fclose(target_file);
    return result;
}
// 16 преобразование выражения в автомат
int action_rex_to_fa(char * rex, NFA & fa) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-rexfa")) return 0;
    printf("-- regex\n%s\n\n", rex);
    printf("-- regex to fa\n");
    int result = algorithm_rex_to_fa(rex, fa, target_file);
    fclose(target_file);
    return result;
}
// 17 преобразование автомата в выражение
int action_fa_to_rex(NFA & fa, char * rex) {
    FILE * target_file = 0;
    if (!target_open(&target_file, "-farex")) return 0;
    printf("-- fa to regex\n");
    int result = algorithm_fa_to_rex(fa, rex, target_file);
    fclose(target_file);
    return result;
}
// исключение
void except(const char * err) {
    fprintf(stdout, "\n\n-- Exception encountered");
    fprintf(stdout, "\n-- %s\n\n", err);
}
// справка
void help() {
    printf("\nUsage:\n");
    printf("grom path -key1 -key2 . . .\n");
    printf("Keys:\n");
    printf("-gr    - group rules\n");
    printf("-us    - eliminate useless symbols\n");
    printf("-ur    - eliminate unreachable symbols\n");
    printf("-re    - eliminate empty rules\n");
    printf("-rc    - eliminate unit rules\n");
    printf("-lr    - eliminate left recursion\n");
    printf("-lf    - left factoring\n");
    printf("-cnf   - Chomsky normal form\n");
    printf("-faus  - eliminate unreachable states\n");
    printf("-faau  - automation to grammar\n");
    printf("-aufa  - grammar to automation\n");
    printf("-dfa   - NFA to DFA\n");
    printf("-fainv - NFA inverse\n");
    printf("-minfa - minimal DFA\n");
    printf("-rexfa - regex to e-NFA\n");
    printf("-farex - automation to regex\n");
    printf("\n");
}
