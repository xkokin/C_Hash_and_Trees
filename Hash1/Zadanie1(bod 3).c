#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HashTable1.h"


typedef struct SET1
{
    int key;
    //unsigned char* key;
    int data;
} set1;


int hashFunction1(int key, int capacity) { 
    return fmod(key, capacity); 
}
/*int hashFunction1(unsigned char* key, int capacity) {
    int stringKey = 0;
    for (int i = 0; i < strlen(key); i++) {
        stringKey += key[i];
    }
    return (stringKey % capacity);
}*/
int checkPrime1(int n){

    if (n == 1 || n == 0) return 0; 

    for (int i = 2; i < n / 2; i++){

        if (n % i == 0) return 0;

    }
    return 1;
}
int getPrime1(int n){

    if (n % 2 == 0) n++;

    while (!checkPrime1(n)){ n += 2; }

    return n;
}


void displayHash1(set1* array, int capacity) {

    for (int i = 0; i < capacity; i++) {
        if (array[i].data == 0)  printf("array[%d]: / \n", i);
        else  printf("Key: %d array[%d]: %d \n", array[i].key, i, array[i].data);
    }
}


set1* insertHash1(set1* array, int key, int data, int *size, int *capacity){
    if (array == NULL) {
        //printf("Table is not initialized\n");
        return;
    }
    int index = hashFunction1(key, (*capacity));


    if (array[index].data == 0 || array[index].key == -1) {
        array[index].key = key;                                         //ak bunka je pradna tak zapisujeme sem 
        array[index].data = data;
        (*size)++;
        //printf("index: %d data: %d\t", index, array[index].data);
        //printf("New element added with key (%d)\n", key);
        return array;

    }
    else if (array[index].key == key) {
                                                                                    //ak kluce su rovnake tak zmenime hodnotu data
        array[index].data = data;
        //printf("Key's %d data has changed to %d", key, array[index].data);
        return array;
    }
    

    
    else {

        if((*size)/ (*capacity) > 0.7){                          //ak naplnenost tabulky vyssia za 70% tak rozsirime dvojnasobne
            (*capacity) *= 2;
            set1* newArray = initHash1(array, capacity, *size);
            //printf("Table has extended, new capacity is %d\n", (*capacity));

            int index1 = hashFunction1(key, (*capacity));
            
            if (newArray[index1].data == 0 || newArray[index].key == -1) {      
                newArray[index1].key = key;
                newArray[index1].data = data;
                (*size)++;
                //printf("size: (%d) index: %d data: %d\t", *size , index1, newArray[index1].data);
                //printf("New element added with key (%d)\n", key);
                return newArray;
            }
            else {
                //printf("\n Collision detected \n");
                for (int i = 0; i < (*capacity); i++) {
                    index = i + hashFunction1(key, (*capacity));
                    if (newArray[index].data == 0 || newArray[index].key == -1) {
                        newArray[index].key = key;
                        newArray[index].data = data;
                        (*size)++;

                        //printf("\n Key (%d) inserted to index (%d) with data (%d), collision solved \n", newArray[index].key, index, newArray[index].data);
                        return newArray;
                        break;
                    }
                }
            }

        }
       // printf("\n Collision detected \n");
        for (int i = 0; i < (*capacity); i++) {

            index = i + hashFunction1(key, (*capacity));
            if (array[index].data == 0 || array[index].key == -1) {
                array[index].key = key;
                array[index].data = data;
                (*size)++;

                //printf("\n Key (%d) inserted to index (%d) with data (%d), collision solved \n", array[index].key, index, array[index].data);
                return array;
                break;
            }
        }
    }
}

void deleteHash1(set1* array, int key, int capacity, int * size){

    int index = hashFunction1(key, capacity);

    if (array[index].data == 0) {
        //printf("\n This key (%d) does not exist; index: %d \n", key, index);
        return;
    }
    if (key != array[index].key) {
        for (int i = 0; i < capacity; i++) {
            index = i + hashFunction1(key, capacity);
            if (key == array[index].key) {
                array[index].key = 0;
                array[index].data = 0;
                (*size)--;
                //printf("\n Key (%d) deleted \n", key);
                return;
            }
        }
    }
    else if (key == array[index].key) {
        array[index].key = 0;
        array[index].data = 0;
        (*size)--;
        //printf("\n Key (%d) deleted \n", key);
        return;
    }
}

int searchHash1(set1* array, int key, int capacity){
    int index = hashFunction1(key, capacity);

    if (array[index].key == key) {
        return index;
    }
    else if (array[index].key != key) {
        for (int i = 0; i < capacity; i++) {
            index = i + hashFunction1(key, capacity);
            if (array[index].key == key) {

                return index;
                break;
            }
        }
    }
   // else printf("Key %d does not exist\n", key);
    return -1;


}

set1* initHash1(set1* array, int* capacity, int size) {     //init budeme pouzivat ked potrebujeme rozsirit tabulku, spravime
                                                            //toto cez funkciu realloc
    (*capacity) = getPrime1(*capacity);
    set1 *newArray = (set1*)realloc(array, (*capacity)* sizeof(set1));      

    for (int i = size; i < (*capacity); i++) {
          newArray[i].key = -1;
          newArray[i].data = 0;
          //printf("%d: key (%d) data (%d)\n",i , newArray[i].key, newArray[i].data);
    }
    //printf("Table initialized\n");
    return newArray;
}

