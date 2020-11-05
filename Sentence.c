#include "Sentence.h"
#include <string.h>
#include <wchar.h>
#include <bits/wctype-wchar.h>
#include "Text.h"
#include "ArrayLong.h"

const wchar_t *END_CHARS = L".;?!";
const wchar_t *CYRILLIC = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯабвгдеёжзийклмнопрстуфхцчшщьыъэюя";
const wchar_t *CAPITAL_LATIN = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const wchar_t *SPECIAL_CHARS = L"\a\b\f\n\r\t\v";
const wchar_t *WORD_DELIMITERS = L",";

wchar_t NULL_TERMINATOR = L'\0';
wchar_t TIME_DELIMITER = L':';

int isEndChar(wchar_t c) {
    return wcschr(END_CHARS, c) != NULL;
}

int isWordDelim(wchar_t c) {
    return wcschr(WORD_DELIMITERS, c) != NULL || iswspace(c);
}

Sentence newSentence() {
    Sentence s = newArray(sizeof(wchar_t));
    addItem(&s, &NULL_TERMINATOR);
    return s;
}

void addChar(Sentence *this, wchar_t c) {
    setItem(this, this->size - 1, &c);
    addItem(this, &NULL_TERMINATOR);
}

wchar_t *cString(Sentence this) {
    return (wchar_t *) this.ptr;
}

Sentence readSentence() {
    Sentence str = newSentence();
    wchar_t c;
    int i = 0, endSize = (int) wcslen(TEXT_END);
    do {
        addChar(&str, c = getwchar());
        if (c == TEXT_END[i])
            i++;
        else
            i = 0;
    } while (!isEndChar(c) && i != endSize);

    if (i == endSize)
        delArray(&str);

    return str;
}

int cmpNoReg(Sentence s1, Sentence s2) {
    return wcscasecmp(s1.ptr, s2.ptr) == 0;
}

int cyrillicChars(Sentence s) {
    int chars = 0;
    wchar_t *ptr = (wchar_t *) s.ptr;
    while ((ptr = wcspbrk(ptr, CYRILLIC)) != NULL) {
        ptr++;
        chars++;
    }
    return chars;
}

int cmpCyrillicLow(void *s1, void *s2) {
    return cyrillicChars(*(Sentence *) s1) < cyrillicChars(*(Sentence *) s2);
}

void delCapitalLatin(Sentence *s) {
    int i;
    while ((i = wcscspn((wchar_t *) s->ptr, CAPITAL_LATIN)) != s->size - 1) {
        delItem(s, i);
    }
}

int hasSpecial(Sentence s) {
    return wcscspn(s.ptr, SPECIAL_CHARS) != s.size - 1;
}

ArrayLong getMinutesDelta(Sentence s) {
    ArrayLong minutes = newArrayLong();
    wchar_t *ptr = s.ptr;
    while ((ptr = wcschr(ptr, TIME_DELIMITER)) != NULL) {
        wchar_t *l = ptr - 1;
        wchar_t *r = ptr + 1;
        while (l >= (wchar_t *) s.ptr && iswdigit(*l))
            l--;
        while (iswdigit(*r))
            r++;

        ptr++;
        if ((l == s.ptr || isWordDelim(*l)) &&
            (isEndChar(*r) || isWordDelim(*r))) {
            if (isWordDelim(*l))
                l++;
            long m = wcstol(ptr, NULL, 10) + wcstol(l, NULL, 10) * 60;
            addNum(&minutes, m);
        }
    }

    return minutes;
}
