#include "Array.h"
#include <stdlib.h>
#include <string.h>

const int INIT_SIZE = 16;
const int EXPAND_SIZE = 16;

Array newArray(int typeSize) {
    Array this = {INIT_SIZE, 0, typeSize, calloc(INIT_SIZE, typeSize)};
    return this;
}

void addItem(Array *this, void *item) {
    if (this->size >= this->maxSize) {
        this->maxSize += EXPAND_SIZE;
        this->ptr = realloc(this->ptr, this->maxSize * this->typeSize);
    }

    memcpy(this->ptr + this->size * this->typeSize, item, this->typeSize);
    this->size++;
}

void *getItemPtr(Array this, int index) {
    if (index >= 0 && index < this.size)
        return (this.ptr + index * this.typeSize);
    else
        return NULL;
}

void setItem(Array *this, int index, void *item) {
    void *ptr = getItemPtr(*this, index);
    if (ptr != NULL)
        memcpy(ptr, item, this->typeSize);
}

void delItem(Array *this, int index) {
    void *ptr = getItemPtr(*this, index);
    void *remain = getItemPtr(*this, index + 1);
    if (ptr != NULL) {
        if (remain != NULL)
            memmove(ptr, remain, (this->size - index) * this->typeSize);
        this->size--;
    }
}

void delArray(Array *this) {
    if (this->ptr != NULL)
        free(this->ptr);
    this->ptr = NULL;
    this->size = this->maxSize = this->typeSize = 0;
}

void sort(Array *this, int (*compareItem)(void *, void *)) {
    int swap = 1;
    void *tmp = malloc(this->typeSize);
    while (swap) {
        swap = 0;
        for (int i = 1; i < this->size; ++i) {
            void *item1 = getItemPtr(*this, i - 1);
            void *item2 = getItemPtr(*this, i);
            if (compareItem(item1, item2)) {
                memcpy(tmp, item1, this->typeSize);
                memcpy(item1, item2, this->typeSize);
                memcpy(item2, tmp, this->typeSize);
                swap = 1;
            }
        }
    }
    free(tmp);
}
