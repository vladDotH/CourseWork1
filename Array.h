#pragma once

extern const int INIT_SIZE;
extern const int EXPAND_SIZE;

typedef struct {
    int maxSize;
    int size;
    int typeSize;
    void *ptr;
} Array;

Array newArray(int typeSize);

void addItem(Array *this, void *item);

void *getItemPtr(Array this, int index);

void setItem(Array *this, int index, void *item);

void delItem(Array *this, int index);

void delArray(Array *this);

/* compare function must return
 * first > second for Ascending
 * first < second for Descending
 */
void sort(Array *this, int (*compareItem)(void *, void *));
