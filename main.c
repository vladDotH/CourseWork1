#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <fcntl.h>
#include "Text.h"

void io_config() {
#if defined(__linux__)
    setlocale(LC_ALL, "ru_RU.utf8");
#elif defined(_WIN32)
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
#endif
}

enum Mode {
    EXIT,
    PRINT_MINUTES_DELTA,
    DELETE_ALL_CAPITAL_LATIN,
    SORT_CYRILLIC_DESCENT,
    DELETE_NO_SPEC_CHARS_SENTENCES,
    PRINT,
    MANUAL
};

const wchar_t *GREETING = L"Введите текст (Три перевода строки \\n - для окончания ввода)\n";
const wchar_t *HELP =
        L"Выберите действие:\n"
        "1 - Для каждой подстроки в тексте, задающей время вида “часы:минуты”, вывести номер предложения в котором "
        "она  встречается и количество минут до текущего времени(время в которое начала выполняться данная задача).\n"
        "2 - В каждом предложении удалить все заглавные латинские буквы.\n"
        "3 - Отсортировать предложения по уменьшению количеству кириллических букв.\n"
        "4 - Удалить все предложения в которых нет специальных символов.\n"
        "5 - Распечатать текст\n"
        "6 - Справка\n"
        "0 - Выход\n";
const wchar_t *INPUT = L">>";

int main() {
    io_config();
    wprintf(GREETING);
    Text text = readText();
    wprintf(HELP);

    enum Mode mode = -1;
    while (mode != EXIT) {
        wprintf(INPUT);
        wscanf(L"%d", &mode);
        switch (mode) {
            case PRINT_MINUTES_DELTA:
                printMinutesDelta(text, time(NULL));
                break;
            case DELETE_ALL_CAPITAL_LATIN:
                delAllCapitalLatin(text);
                break;
            case SORT_CYRILLIC_DESCENT:
                sortByCyrillicLow(&text);
                break;
            case DELETE_NO_SPEC_CHARS_SENTENCES:
                delNoSpecCharSentences(&text);
                break;
            case PRINT:
                printText(text);
                break;
            case MANUAL:
                wprintf(HELP);
        }
    }

    delText(&text);
}
