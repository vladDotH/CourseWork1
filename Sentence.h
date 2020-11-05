#pragma once

#include "Array.h"
#include "ArrayLong.h"

extern const wchar_t *END_CHARS;
extern const wchar_t *CYRILLIC;
extern const wchar_t *CAPITAL_LATIN;
extern const wchar_t *SPECIAL_CHARS;
extern const wchar_t *WORD_DELIMITERS;

extern wchar_t NULL_TERMINATOR;
extern wchar_t TIME_DELIMITER;

typedef Array Sentence;

int isEndChar(wchar_t c);

int isWordDelim(wchar_t);

Sentence newSentence();

void addChar(Sentence *this, wchar_t c);

wchar_t *cString(Sentence this);

Sentence readSentence();

int cmpNoReg(Sentence s1, Sentence s2);

int cyrillicChars(Sentence s);

int cmpCyrillicLow(void *ptr_s1, void *ptr_s2);

void delCapitalLatin(Sentence *s);

int hasSpecial(Sentence s);

ArrayLong getMinutesDelta(Sentence s);