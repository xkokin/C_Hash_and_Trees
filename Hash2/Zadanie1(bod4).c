#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HashTable2.h"


typedef struct SET2
{
    int key;
    //unsigned char* key;
    int data;
    struct SET2* next;
} set2;



int checkPrime2(int n) {

    if (n == 1 || n == 0) return 0;

    for (int i = 2; i < n / 2; i++) {

        if (n % i == 0) return 0;

    }
    return 1;
}
int getPrime2(int n) {

    if (n % 2 == 0) n++;

    while (!checkPrime2(n)) { n += 2; }

    return (n);
}
set2* initHash2(set2* pole, int *capacity, int size) {

    (*capacity) = getPrime2(*capacity);
    set2 *newPole = (set2*)realloc(pole, (*capacity) * sizeof(set2));

    for (int i = size; i < (*capacity); i++) {
        newPole[i].key = -1;
        newPole[i].data = 0;
        newPole[i].next = NULL;
        //printf("%d: key (%d) data (%d)\n", i, newPole[i].key, newPole[i].data);
    }
    //printf("Table initialized\n");
    return newPole;
}
int hashFunction2(int key, int capacity){

    return fmod(key, capacity);
}


set2* findNULL(set2* array) {                                       //hlada prazdny ukazovatel alebo prazdnu bunku pre zapisovanie
    if (array->next == NULL || array->next->key == -1)return array;
    else return findNULL(array->next);
}
set2* insertHash2(set2* array, int key, int data, int* size, int* capacity) {

    int index = hashFunction2(key, (*capacity));

    if ((*size) / (*capacity) > 0.7) {
        (*capacity) *= 2;
        set2* newArray = initHash2(array, capacity, *size);
        newArray = insertHash2(newArray, key, data, size, capacity);
        return newArray;
    }

    if (array[index].data == 0 || array[index].key == -1) {
        array[index].key = key;
        array[index].data = data;
        (*size)++;
        //printf("index: %d data: %d\t", index, array[index].data);
        //printf("New element added with key (%d)\n", key);
        return array;
    }
    else if (array[index].key == key) {
        array[index].data = data;
        //printf("Key's %d data has changed to %d", key, array[index].data);
        return array;
    }
    else {
        //printf("\n Collision detected \n");
        set2* path = NULL;
        if (array[index].next == NULL || array[index].next->key == -1) {
            if (array[index].next == NULL) {
                set2* new = (set2*)malloc(sizeof(set2));
                new->data = data;
                new->key = key;
                new->next = NULL;
                array[index].next = new;
                (*size)++;
                //printf("\n Key (%d) inserted to index (%d) with data (%d), collision solved \n", key, index, new->data);
                return array;
            }
            else if (array[index].next->key == -1) {
                array[index].next->data = data;
                array[index].next->key = key;
                //printf("\n Key (%d) inserted to index (%d) with data (%d), collision solved \n", array[index].next->key, index, array[index].next->data);
                return array;
            }
        }
        path = findNULL(array->next);
        if (path->next != NULL && path->next->key == -1) {
            path->next->data = data;
            path->next->key = key;
            //printf("\n Key (%d) inserted to index (%d) with data (%d), collision solved \n", key, index, array[index].data);
            return array;
        }
        else if (path->next == NULL) {
            set2* new = (set2*)malloc(sizeof(set2));
            new->data = data;
            new->key = key;
            new->next = NULL;
            path->next = new;
            (*size)++;
            //printf("\n Key (%d) inserted to index (%d) with data (%d), collision solved \n", key, index, array[index].data);
            return array;
        }
    }
}


set2* searchChainDel(set2* head, int key) {
    if (head->next != NULL && head->next->key == key) return head;
    else if (head->next == NULL) {
        //printf("Element doesn't exist\n");
        return NULL;
    }
    else return searchChainDel(head->next, key);
}

void deleteHash2(set2* array, int key, int capacity, int* size){

    int index = hashFunction2(key, capacity);

    if (array[index].key == -1) {
        if (array[index].next == NULL) {
            //printf("\n This key (%d) does not exist; index: %d \n", key, index);
            return;
        }
        else {
            if (array[index].next->key == key) {
                array[index].next->key = -1;
                array[index].next->data = 0;
                //printf("\n Key (%d) deleted \n", key);
                return;
            }
            else {
                set2* del = searchChainDel(array[index].next, key);
                if (del == NULL) return;
                del->key = -1;
                del->data = 0;
                (*size)--;
                //printf("\n Key (%d) deleted \n", key);
                return;
            }
        }
    }

    else if (array[index].key == key) {
        array[index].key = -1;
        array[index].data = 0;
        //printf("\n Key (%d) deleted \n", key);
        return;
    }

    else if(array[index].key != key) {
        if (array[index].next->key != key) { 
            set2* del = searchChainDel(array[index].next, key);
            if (del == NULL) return;
            del->key = -1;
            del->data = 0;
            (*size)--;
            //printf("\n Key (%d) deleted \n", key);
            return;
        }
        else if (array[index].next->key == key) {
            array[index].next->key = -1;
            array[index].next->data = 0;
            //printf("\n Key (%d) deleted \n", key);
            return;
        }

    }
    /*else {
        array[index].key = 0;
        array[index].data = 0;
        (*size)--;
        printf("\n Key (%d) deleted \n", key);
        return;
    }*/
}


void displayHash2(set2* array, int capacity) {

    for (int i = 0; i < capacity; i++) {
        if (array[i].data == 0) {
            printf("\n array[%d]: / ", i);
            if (array[i].next != NULL) {
                if (array[i].next->data == 0)printf("\t array[%d]: / ", i);
                else if(array[i].next->data != 0) printf("\n Key: %d array[%d]: %d \t", array[i].next->key, i, array[i].next->data);
            }
        }
        else {
            printf("\n Key: %d array[%d]: %d \t", array[i].key, i, array[i].data);
            if (array[i].next != NULL) {
                if (array[i].next->data == 0)printf("\t array[%d]: / ", i);
                else if (array[i].next->data != 0) printf("\t Key: %d array[%d]: %d \t", array[i].next->key, i, array[i].next->data);
            }
        }
    }
}
set2* searchChain(set2* head, int key) {
    if (head->key == key) {
        return head;
    }
    else return searchChain(head->next, key);
}
int searchHash2(set2* array, int key, int capacity){
    int index = hashFunction2(key, capacity);

    if (array[index].key == key) {
        return index;
    }
    else if (array[index].key != key) {

        if (searchChain(array[index].next, key) == NULL) {
            //printf("Element does not exist\n");
            return -1;
        }
        else if (searchChain(array[index].next, key) != NULL) {
            //printf("Element has been found, index: %d\n", index);
            return index;
        }
    }
    //else printf("Key %d does not exist\n", key);
    //return -1;


}

