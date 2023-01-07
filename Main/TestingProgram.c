#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "AVL.h"
#include "Btree23.h"
#include "HashTable1.h"
#include "HashTable2.h"





int main() {
	srand(time(NULL));
	/*unsigned char* vocab[50];

	for (int i = 0; i < 50; i++) {
		int r = 1 + (rand() % 10);
		vocab[i] = (unsigned char*)malloc(r * sizeof(unsigned char));
		unsigned char ch[10];
		if (vocab[i]) {
			for (int n = 0; n < r; n++) {
				int letter = 97 + (rand() % 26);
				ch[n] = letter;
				
			}
			
		}
		strcpy(vocab[i], ch);
		printf("%s\n", vocab[i]);
	}*/

	for (int p = 0; p < 3; p++) {
		int t = pow(10, p) * 100000;
		//--------------------AVL-----------------------//
		unsigned int startAVL = clock();
		btree* headAVL = NULL;
		headAVL = initAVL(27);
		if (headAVL == NULL) {
			printf("Something went wrong\n");
			return -1;
		}
		//printf("%d\n", headAVL->index);

		unsigned int startIns0 = clock();
		for (int i = 0; i < pow(10, p)*100000; i++) {
			headAVL = insertAVL(headAVL, i);
			//printf("New AVL node added with key (%d).\n", i);
		}
		unsigned int endIns0 = clock();
		unsigned int Ins0 = endIns0 - startIns0;
		printf("Inserting has been successful, time: %d\n", Ins0);

		unsigned int startSearch0 = clock();
		for (int i = 0; i < pow(10, p)* 100000; i++) {

			//int n = fmod(2 + i * (i * 5), 50);
			btree* found = NULL;
			found = searchAVL(headAVL, i);
			//if(found != NULL) printf("Node with key (%d) has been found.\n", n);
			//else if (found == NULL)printf("Node with key (%d) hasn't been found.\n", n);
		}
		unsigned int endSearch0 = clock();
		unsigned int Search0 = endSearch0 - startSearch0;
		printf("Searching has been successful, time: %d\n", Search0);

		unsigned int startDel0 = clock();
		for (int i = 0; i < pow(10, p) * 100000; i++) {
			deleteAVL(headAVL, i);
			//printf("Node with key (%d) has been deleted.\n", i);
		}
		unsigned int endDel0 = clock();
		unsigned int Del0 = endDel0 - startDel0;
		printf("Deleting has been successful, time: %d\n", Del0);

		unsigned int endAVL = clock();
		unsigned int timeAVL = endAVL - startAVL;
		printf("\nTest for AVL binary tree was successfully done; \nTime: %d\n\n\n", timeAVL);

		//------------------23Btree---------------------//

	/*
		unsigned int start23 = clock();
		bt23* head23 = NULL;
		head23 = init23(head23, 27);


		for (int i = 0; i < 50; i++) {
			head23 = insert23(head23, i);
			printf("New 2-3 node added with key (%d)\n", i);
		}
		for (int i = 0; i < 5; i++) {
			int n = fmod(2 + i * (i * 5), 50);
			search23(head23, n);
		}
		for (int i = 0; i < 50 ; i++) {

			head23 = delete23(head23, i);
		}
		unsigned int end23 = clock();
		unsigned int time23 = end23 - start23;
		printf("\nTest for 2-3 binary tree was successfully done; \nTime: %d\n\n\n", time23);

		*/
		//-------------------Hash1----------------------//


		unsigned int startHash1 = clock();
		int capacity1 = 100;
		int size1 = 0;

		set1* arrayHash1 = NULL;
		arrayHash1 = initHash1(arrayHash1, &capacity1, size1);

		unsigned int startIns1 = clock();
		for (int i = 0; i < pow(10, p) * 100000; i++) {
			arrayHash1 = insertHash1(arrayHash1, i, i + 50, &size1, &capacity1);
			//printf("New element added with key (%d)\n", i);
		}
		unsigned int endIns1 = clock();
		unsigned int Ins1 = endIns1 - startIns1;
		printf("Inserting has been successful, time: %d\n", Ins1);

		unsigned int startSearch1 = clock();
		for (int i = 0; i < pow(10, p) * 100000; i++) {

			//int n = fmod(2 + i * (i * 5), 50);
			int index1 = 0;
			index1 = searchHash1(arrayHash1, i, capacity1);
			//if (index1 != -1) printf("Element with key (%d) has been found.\n", n);
			//else if (index1 == -1)printf("Element with key (%d) hasn't been found.\n", n);
		}
		unsigned int endSearch1 = clock();
		unsigned int Search1 = endSearch1 - startSearch1;
		printf("Searching has been successful, time: %d\n", Search1);

		unsigned int startDel1 = clock();
		for (int i = 0; i < pow(10, p) * 100000; i++) {
			deleteHash1(arrayHash1, i, capacity1, &size1);

		}
		unsigned int endDel1 = clock();
		unsigned int Del1 = endDel1 - startDel1;
		printf("Deleting has been successful, time: %d\n", Del1);

		unsigned int endHash1 = clock();
		unsigned int timeHash1 = endHash1 - startHash1;
		printf("\nTest for Hash table 1 was successfully done; \nTime: %d\n\n\n", timeHash1);

	

		//-------------------Hash2----------------------//


		unsigned int startHash2 = clock();
		set1* arrayHash2 = NULL;
		int capacity2 = 10000;
		int size2 = 0;
		arrayHash2 = initHash2(arrayHash2, &capacity2, size2);

		unsigned int startIns2 = clock();
		for (int i = 0; i < pow(10, p) * 1000000; i++) {
			arrayHash2 = insertHash2(arrayHash2, i, i + 50, &size2, &capacity2);

		}
		unsigned int endIns2 = clock();
		unsigned int Ins2 = endIns2 - startIns2;
		printf("Inserting has been successful, time: %d\n", Ins2);

		unsigned int startSearch2 = clock();
		for (int i = 0; i < pow(10, p) * 100000; i++) {

			//int n = fmod(2 + i * (i * 5), 50);
			int index2 = 0;
			index2 = searchHash2(arrayHash2, i, capacity2);
			//if (index2 != -1) printf("Element with key (%d) has been found.\n", n);
			//else if (index2 == -1)printf("Element with key (%d) hasn't been found.\n", n);
		}
		unsigned int endSearch2 = clock();
		unsigned int Search2 = endSearch2 - startSearch2;
		printf("Searching has been successful, time: %d\n", Search2);
		//displayHash2(arrayHash2, capacity2);

		unsigned int startDel2 = clock();
		for (int i = 0; i < pow(10, p) * 100000; i++) {

			deleteHash2(arrayHash2, i, capacity2, &size2);

		}
		unsigned int endDel2 = clock();
		unsigned int Del2 = endDel2 - startDel2;
		printf("Deleting has been successful, time: %d\n", Del2);


		unsigned int endHash2 = clock();
		unsigned int timeHash2 = endHash2 - startHash2;
		printf("\nTest for Hash table 2 was successfully done; \nTime: %d\n\n\n", timeHash2);


		printf("\n-------------------------------------\nTest for %d elements has been successful\n-------------------------------------\n", t);
	}


	return 0;
}
