#pragma once

#include <stddef.h>

typedef int (*compare_t)(const void *a, const void *b);

void MergeSort(void *a, size_t n, size_t c, compare_t cmp);
