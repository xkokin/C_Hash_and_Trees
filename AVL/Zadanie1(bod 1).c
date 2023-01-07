#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

typedef struct BinaryTree {						//struktura pre AVL binarny strom
	int index;									//index - cislo odkazu binary tree
//	unsigned char* index;
	int height;									//height - vyska odkazu
	struct BinaryTree *nextR;					//ukazovatel na nasledujuci prvok vpravo 
	struct BinaryTree *nextL;					//ukazovatel na prvok vlavo
	struct BinaryTree *parent;					//ukazovatel na predchadzajuci odkaz
}btree;

//btree* searchAVL(btree* Head, unsigned char* index) {
btree* searchAVL(btree* Head, int index){


	if (Head == NULL || Head->index == index) return Head;
	

	if (index < Head->index) return searchAVL(Head->nextL, index);
	else return searchAVL(Head->nextR, index);

}

btree* Balance(btree* x);

btree* insertAVL(btree* Head, int index) {

	if (Head == NULL) {
		Head = (btree*)calloc(1, sizeof(btree));
		if (Head) {
			Head->index = index;										//pridelujeme index novemu odkazu
			Head->parent = NULL;										//ked sme nasli miesto pre odkaz, nastavime vsetci parametre 
			Head->nextR = NULL;
			Head->nextL = NULL;
			return Head;
		}
	}

	if (index < Head->index) {
		Head->nextL = insertAVL(Head->nextL, index);
		Head->nextL->parent = Head;
	}
	else {
		Head->nextR = insertAVL(Head->nextR, index);
		Head->nextR->parent = Head;
	}
	return Balance(Head);													//zavolame funkciu balance pre vyvazovanie stromu s
}



int GetHeight(btree* p){		//ak existuje nieaka hodnota height tak vrati to
	if (p) return p->height;
	else return 0;
}

																//tato f-ia bude pouzivat pre balancing naseho binary tree pri vytvarani novych odkazov
int BalanceFactor(btree* p){									//vrati koeficient rovnovahy odkazu

	return GetHeight(p->nextR) - GetHeight(p->nextL);
}


void OverHeight(btree* p){

	int hleft = GetHeight(p->nextL);
	int hright = GetHeight(p->nextR);

	p->height = (hleft > hright ? hleft : hright) + 1;
}

btree* RightSmallRotation(btree* x){		//f-ia pre male otocenie vpravo

	btree* y = x->nextL;

	x->nextL = y->nextR;
	y->nextR = x;
	OverHeight(x);
	OverHeight(y);
	return y;
}
btree* LeftSmallRotation(btree* y){			//f-ia pre male otocenie vlavo
	btree* x = y->nextR;

	y->nextR = x->nextL;
	x->nextL = y;
	OverHeight(y);
	OverHeight(x);
	return x;
}

btree * Balance(btree * x){																//funkcia na vyvazovanie binarneho stromu AVL

	OverHeight(x);																		//spravime najprv funkciu pre nastavenie vysky noveho odkazu

	if (BalanceFactor(x) == 2){															//pouzieme koeficient vyvazovania pre urcenie otocenia ktore potrebujeme 

		if (BalanceFactor(x->nextR) < 0) x->nextR = RightSmallRotation(x->nextR);		//ak vyvazovaci koeficient praveho nasledujuceho odkazu mensi za 0 budeme pouzivat 
		return LeftSmallRotation(x);													//Velke otocenie vlavo, ak nie tak male otocenie vlavo
	}
	if (BalanceFactor(x) == -2)
	{
		if (BalanceFactor(x->nextL) > 0) x->nextL = LeftSmallRotation(x->nextL); 
		return RightSmallRotation(x);
	}
	return x;
}


btree* searchMinAVL(btree* Head) {
	if (Head->nextL) {
		return searchMinAVL(Head->nextL);
	}
	else return Head;
}

btree* deleteMinAVL(btree* Head) {
	if (Head->nextL == NULL) return Head->nextR;

	else {
		Head->nextL = deleteMinAVL(Head->nextL);
		return Balance(Head);
	}
}


btree* deleteAVL(btree* Head, int index) {
	if (Head == NULL) {
		//printf("Node has already been deleted or does not exist \n");
		return NULL;
	}
	if (index < Head->index) Head->nextL = deleteAVL(Head->nextL, index);
	else if (index > Head->index) Head->nextR = deleteAVL(Head->nextR, index);

	else if (index == Head->index){

		btree* y = Head->nextL;
		btree* z = Head->nextR;

		free(Head);

		if (!z) return y;

		else {
			btree* min = searchMinAVL(z);
			min->nextR = deleteMinAVL(z);
			min->nextL = y;
			return Balance(min);
		}
	}
	return Balance(Head);
}



btree* initAVL(int index){
	btree* tmp = (btree*)calloc(1, sizeof(btree));
	if (tmp) {

			tmp->index = index;
			tmp->parent = NULL;
			tmp->nextR = tmp->nextL = NULL;
			

			return tmp;
	}
}
