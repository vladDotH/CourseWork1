#pragma once

#include "Array.h"

typedef Array ArrayLong;

ArrayLong newArrayLong();

void addNum(ArrayLong *this, long num);

long getNum(ArrayLong this, int index);