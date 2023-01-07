#pragma once

typedef struct SET2  set2;

set2* initHash2(set2* pole, int* capacity, int size);

set2* insertHash2(set2* array, int key, int data, int* size, int* capacity);

void deleteHash2(set2* array, int key, int capacity, int* size);

int searchHash2(set2* array, int key, int capacity);

//void displayHash2(set2* array, int capacity);