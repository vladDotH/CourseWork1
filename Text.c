#include "Text.h"
#include <wchar.h>
#include "Sentence.h"
#include "ArrayLong.h"

const wchar_t *const TEXT_END = L"\n\n\n";

Sentence *getSentencePtr(Text this, int i) {
    return (Sentence *) getItemPtr(this, i);
}

int sentenceExist(Text this, Sentence s) {
    for (int i = 0; i < this.size; ++i) {
        if (cmpNoReg(*getSentencePtr(this, i), s))
            return 1;
    }
    return 0;
}

void delText(Text *this) {
    for (int i = 0; i < this->size; ++i) {
        delArray(getSentencePtr(*this, i));
    }
    delArray(this);
}

Text readText() {
    Text text = newArray(sizeof(Sentence));
    Sentence s;
    while ((s = readSentence()).ptr != NULL) {
        if (!sentenceExist(text, s))
            addItem(&text, &s);
        else
            delArray(&s);
    }
    return text;
}

void printText(Text t) {
    for (int i = 0; i < t.size; ++i) {
        wprintf(L"%ls", cString(*getSentencePtr(t, i)));
    }
    wprintf(L"\n");
}

void delAllCapitalLatin(Text t) {
    for (int i = 0; i < t.size; ++i) {
        delCapitalLatin(getSentencePtr(t, i));
    }
}

void delNoSpecCharSentences(Text *t) {
    for (int i = 0; i < t->size; ++i) {
        Sentence *s = getSentencePtr(*t, i);
        if (!hasSpecial(*s)) {
            delArray(s);
            delItem(t, i);
            i--;
        }
    }
}

void sortByCyrillicLow(Text *t) {
    sort(t, cmpCyrillicLow);
}

void printMinutesDelta(Text t, time_t current) {
    struct tm *timeInfo = localtime(&current);
    long currMin = timeInfo->tm_hour * 60 + timeInfo->tm_min;
    for (int i = 0; i < t.size; ++i) {
        ArrayLong mins = getMinutesDelta(*getSentencePtr(t, i));
        for (int j = 0; j < mins.size; ++j) {
            wprintf(L"Предложение №%d. Минут до текущего времени: %d\n", i + 1, currMin - getNum(mins, j));
        }
        delArray(&mins);
    }
}
