#include "ArrayLong.h"

ArrayLong newArrayLong() {
    return newArray(sizeof(long));
}

void addNum(ArrayLong *this, long num) {
    addItem(this, &num);
}

long getNum(ArrayLong this, int index) {
    return *(long *) getItemPtr(this, index);
}
