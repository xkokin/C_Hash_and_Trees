#pragma once

typedef struct SET1 set1;

set1* initHash1(set1* array, int* capacity, int size);

set1* insertHash1(set1* array, int key, int data, int* size, int* capacity);

void deleteHash1(set1* array, int key, int capacity, int* size);

int searchHash1(set1* array, int key, int capacity);