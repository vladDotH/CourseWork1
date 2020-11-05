#pragma once

#include "Array.h"

extern const char *END_SENTENCE;
extern const char *END_CHARS;
extern const char *TAB_CHARS;
extern const char *INVALID_STR;

typedef Array Text;
typedef Array Sentence;

int isTabChar(char c);

int isEndChar(char c);

Sentence readSentence();

int isEndSentence(Sentence s);

int isValidSentence(Sentence s);

Text readAndFormatText(int *before, int *after);