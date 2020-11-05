#include <string.h>
#include <stdio.h>

#include "text_processing.h"
#include "Array.h"

const char *END_SENTENCE = "Dragon flew away!";
const char *END_CHARS = ".;?!";
const char *TAB_CHARS = " \t";
const char *INVALID_STR = "555";

int isEndChar(char c) {
    return strchr(END_CHARS, (int) c) != NULL;
}

int isTabChar(char c) {
    return strchr(TAB_CHARS, (int) c) != NULL;
}

Sentence readSentence() {
    Sentence s = newArray(sizeof(char));

    char c;
    while (isTabChar(c = getchar())); // miss tab symbols at start

    addItem(&s, &c);
    do {
        c = getchar();
        addItem(&s, &c);
    } while (!isEndChar(c));

    return s;
}

int isEndSentence(Sentence s) {
    return strcmp(s.ptr, END_SENTENCE) == 0;
}

int isValidSentence(Sentence s) {
    return strstr(s.ptr, INVALID_STR) == NULL;
}

Text readAndFormatText(int *before, int *after) {
    *before = *after = -1;

    Text text = newArray(sizeof(Array));
    Sentence s;
    do {
        s = readSentence();
        if (isValidSentence(s)) {
            addItem(&text, &s);
            *after += 1;
        } else
            freePtr(s);

        *before += 1;
    } while (!isEndSentence(s));

    return text;
}
