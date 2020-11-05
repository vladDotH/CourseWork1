#pragma once

#include <time.h>
#include "Array.h"
#include "Sentence.h"

extern const wchar_t *const TEXT_END;

typedef Array Text;

Sentence *getSentencePtr(Text this, int i);

int sentenceExist(Text this, Sentence s);

void delText(Text *this);

Text readText();

void printText(Text t);

void delAllCapitalLatin(Text t);

void delNoSpecCharSentences(Text *t);

void sortByCyrillicLow(Text *t);

void printMinutesDelta(Text t, time_t current);