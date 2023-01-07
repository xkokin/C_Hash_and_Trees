#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Btree23.h"

typedef struct TREE {				//struktura pre 2-3 binarny sstrom
	int size;
	int keys[3];

	struct TREE* parent;
	struct TREE* sons[4];

}bt23;

bt23* search23(bt23* head, int key){

	if (head == NULL) {
		printf("Node with key (%d) hasn't been found.\n", key);
		return NULL;
	}

	for (int i = 0; i < head->size; i++) {
		if (head->keys[i] == key) {
			printf("Node with key (%d) has been found.\n", key);
			return head;
		}
	}
	
	if (key < head->keys[0]) return search23(head->sons[0], key);
	
	else if (((head->size == 2) && (key < head->keys[1])) || head->size == 1) return search23(head->sons[1], key);
	
	else if (head->size == 2) return search23(head->sons[2], key);

}

bool isLeaf(bt23* head) {
	return ((head->sons[0] == NULL) && (head->sons[1] == NULL) && (head->sons[2]) == NULL);
}

void swap(int* x, int* y) {
	int r = (*x);
	x = (*y);
	y = r;
}


void sort1(int* x, int* y);
void sort2(int* x, int* y, int* z);


void regulate(bt23* head) {
	if (head->size == 1) return;
	if (head->size == 2) sort1(head->keys[0], head->keys[1]);
	if (head->size == 3) sort2(head->keys[0], head->keys[1], head->keys[2]);
}

void sort1(int* x, int* y) {
	if ((*x) > (*y)) swap(x, y);
}



void sort2(int* x, int* y, int* z) {
	if (*x > *y) swap(x, y);
	if (*x > *z) swap(x, z);
	if (*y > *z) swap(y, z);
}


void insertToNode(bt23* head, int x) {
	head->keys[head->size] = x;
	head->size++;
	regulate(head);
}


void becomeNode2(int key, bt23* head, bt23* first_, bt23* second_) {  
	head->keys[0] = key;
	head->sons[0] = first_;
	head->sons[1] = second_;
	head->sons[2] = head->sons[3] = head->parent = NULL;
	head->size = 1;
}



bt23* split(bt23* head) {
	if (head->size < 3) return head;

	bt23* x = (bt23*)calloc(1, sizeof(bt23));				// Vytvarame dve nove uzly,
	if (x) {
		x->size = 1;										// ktore maju takeho isteho rodica, ako aj head
		x->keys[0] = head->keys[0];
		x->sons[0] = head->sons[0];
		x->sons[1] = head->sons[1];
		x->sons[2] = NULL;
		x->sons[3] = NULL;
		x->parent = head->parent;
	}
	bt23* y = (bt23*)calloc(1, sizeof(bt23));

	if (y) {
		y->size = 1;
		y->keys[0] = head->keys[2];
		y->sons[0] = head->sons[2];
		y->sons[1] = head->sons[3];
		y->sons[2] = NULL;
		y->sons[3] = NULL;
		y->parent = head->parent;
	}


	if (x->sons[0])  x->sons[0]->parent = x;    // spravne nastavime rodica synov .
	if (x->sons[1]) x->sons[1]->parent = x;   // Po odluceni rodicom synov je stary otec,

	if (y->sons[0])  y->sons[0]->parent = y;    // preto mame spravne nastavit ukazovatele
	if (y->sons[1]) y->sons[1]->parent = y;

	if (head->parent) {

		insertToNode(head->parent, head->keys[1]);

		if (head->parent->sons[0] == head) head->parent->sons[0] = NULL;
		else if (head->parent->sons[1] == head) head->parent->sons[1] = NULL;
		else if (head->parent->sons[2] == head) head->parent->sons[2] = NULL;

		// dalej sme sort
		if (head->parent->sons[0] == NULL) {
			head->parent->sons[3] = head->parent->sons[2];
			head->parent->sons[2] = head->parent->sons[1];
			head->parent->sons[1] = y;
			head->parent->sons[0] = x;
		}
		else if (head->parent->sons[1] == NULL) {
			head->parent->sons[3] = head->parent->sons[2];
			head->parent->sons[2] = y;
			head->parent->sons[1] = x;
		}
		else {
			head->parent->sons[3] = y;
			head->parent->sons[2] = x;
		}

		bt23* tmp = head->parent;
		free(head);
		return tmp;
	}
	else {
		x->parent = head;   // tu bude iba koren 
		y->parent = head;   // tak sme rodicom novzch vrcholov urobime rozdeleni element
		becomeNode2(head->keys[1], head, x, y);
		return head;
	}
}


bt23* insert23(bt23* head, int x) {
	if (isLeaf(head)) {
		insertToNode(head, x);
	}

	else if (x <= head->keys[0]) head->sons[0] = insert23(head->sons[0], x);

	else if ((head->size == 1) || ((head->size == 2) && (x <= head->keys[1]))) head->sons[1] = insert23(head->sons[1], x);

	else head->sons[2] = insert23(head->sons[2], x);

	return split(head);
}



bt23* searchMin23(bt23* head) { // vyhladavanie prvku z minimalnim klucom v strome z kornem p.

	if (!head) return head;

	if (!(head->sons[0])) return head;
	else { 
		return searchMin23(head->sons[0]); 
	}
}

void deleteFromNode(bt23* head, int x) { // vymazeme kluc z vrchola(ne zo stromu)
	if ((head->size >= 1) && (head->keys[0] == x)) {
		head->keys[0] = head->keys[1];
		head->keys[1] = head->keys[2];
		head->size--;
	}
	else if ((head->size == 2) && (head->keys[1] == x)) {
		head->keys[1] = head->keys[2];
		head->size--;
	}
}

/*void deleteFromNode(bt23* head, unsigned char* key) { // Удаляем ключ k из вершины (не из дерева)
	if (head->size >= 1 && (strcmp(head->keys[0], key) == 0)) {
		strcpy(head->keys[0], head->keys[1]);
		strcpy(head->keys[1], head->keys[2]);
		head->size--;
	}
	else if (head->size == 2 && (strcmp(head->keys[1], key) == 0)) {
		strcpy(head->keys[1], head->keys[2]);
		head->size--;
	}
}*/

bt23* join(bt23* leaf){

	bt23* parent = leaf->parent;

	if (parent->sons[0] == leaf) {
		insertToNode(parent->sons[1], parent->keys[0]);
		parent->sons[1]->sons[2] = parent->sons[1]->sons[1];
		parent->sons[1]->sons[1] = parent->sons[1]->sons[0];

		if (leaf->sons[0] != NULL) parent->sons[1]->sons[0] = leaf->sons[0];
		else if (leaf->sons[1] != NULL) parent->sons[1]->sons[0] = leaf->sons[1];

		if (parent->sons[1]->sons[0] != NULL) parent->sons[1]->sons[0]->parent = parent->sons[1];

		deleteFromNode(parent, parent->keys[0]);
		free (parent->sons[0]);
		parent->sons[0] = NULL;
	}
	else if (parent->sons[1] == leaf) {
		insertToNode(parent->sons[0], parent->keys[0]);

		if (leaf->sons[0] != NULL) parent->sons[0]->sons[2] = leaf->sons[0];
		else if (leaf->sons[1] != NULL) parent->sons[0]->sons[2] = leaf->sons[1];

		if (parent->sons[0]->sons[2] != NULL) parent->sons[0]->sons[2]->parent = parent->sons[0];

		deleteFromNode(parent, parent->keys[0]);
		free (parent->sons[1]);
		parent->sons[1] = NULL;
	}

	if (parent->parent == NULL) {
		bt23* tmp = NULL;
		if (parent->sons[0] != NULL) tmp = parent->sons[0];
		else tmp = parent->sons[1];
		tmp->parent = NULL;
		free (parent);
		return tmp;
	}
	return parent;
}

bt23* redistribute(bt23* leaf);

bt23* repair(bt23* leaf) {
	if ((leaf->size == 0) && (leaf->parent == NULL)) { // pripad 0, vymazeme jediny kluc 
		free(leaf);
		return NULL;
	}
	if (leaf->size != 0) { // pripad 1, ked vrchol, v ktorom sme vymazali kluc, mal 2 kluce
		if (leaf->parent) return repair(leaf->parent);
		else return leaf;
	}

	bt23* parent = leaf->parent;
	if (parent->sons[0]->size == 2 || parent->sons[1]->size == 2 || parent->size == 2) leaf = redistribute(leaf); // pripad 2, ked staci prerozdelit kluce v strome
	else if (parent->size == 2 && parent->sons[2]->size == 2) leaf = redistribute(leaf); 
	else leaf = join(leaf); // pripad 3, ked mame urobit join a skocit hore na aspon jeden vrchol

	return repair(leaf);
}

bt23* redistribute(bt23* leaf) {

	bt23* parent = leaf->parent;
	bt23* first = parent->sons[0];
	bt23* second = parent->sons[1];
	bt23* third = parent->sons[2];

	if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
		if (first == leaf) {
			parent->sons[0]= parent->sons[1];
			parent->sons[1] = parent->sons[2];
			parent->sons[2] = NULL;
			insertToNode(parent->sons[0], parent->keys[0]);
			parent->sons[0]->sons[2] = parent->sons[0]->sons[1];
			parent->sons[0]->sons[1] = parent->sons[0]->sons[0];

			if (leaf->sons[0] != NULL) parent->sons[0]->sons[0] = leaf->sons[0];
			else if (leaf->sons[1] != NULL) parent->sons[0]->sons[0] = leaf->sons[1];

			if (parent->sons[0]->sons[0] != NULL) parent->sons[0]->sons[0]->parent = parent->sons[0];

			deleteFromNode(parent, parent->keys[0]);
			free(first);
		}
		else if (second == leaf) {
			insertToNode(first, parent->keys[0]);
			deleteFromNode(parent, parent->keys[0]);
			if (leaf->sons[0] != NULL) first->sons[2] = leaf->sons[0];
			else if (leaf->sons[1] != NULL) first->sons[2] = leaf->sons[1];

			if (first->sons[2] != NULL) first->sons[2]->parent = first;

			parent->sons[1] = parent->sons[2];
			parent->sons[2] = NULL;

			free (second);
		}
		else if (third == leaf) {
			insertToNode(second, parent->keys[1]);
			parent->sons[2] = NULL;
			deleteFromNode(parent, parent->keys[1]);
			if (leaf->sons[0] != NULL) second->sons[2] = leaf->sons[0];
			else if (leaf->sons[1] != NULL) second->sons[2] = leaf->sons[1];

			if (second->sons[2] != NULL)  second->sons[2]->parent = second;

			free (third);
		}
	}
	else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
		if (third == leaf) {
			if (leaf->sons[0] != NULL) {
				leaf->sons[1] = leaf->sons[0];
				leaf->sons[0] = NULL;
			}

			insertToNode(leaf, parent->keys[1]);


			
			if (second->size == 2) {
				parent->keys[1] = second->keys[1];

				deleteFromNode(second, second->keys[1]);
				leaf->sons[0] = second->sons[2];
				second->sons[2] = NULL;
				if (leaf->sons[0] != NULL) leaf->sons[0]->parent = leaf;
			}
			else if (first->size == 2) {
				parent->keys[1] = second->keys[0];

				leaf->sons[0] = second->sons[1];
				second->sons[1] = second->sons[0];
				if (leaf->sons[0] != NULL) leaf->sons[0]->parent = leaf;

				second->keys[0] = parent->keys[0];
				parent->keys[0] = first->keys[1];
				//strcpy(second->keys[0], parent->keys[0]);
				//strcpy(parent->keys[0], first->keys[1]);
				deleteFromNode(first, first->keys[1]);
				second->sons[0] = first->sons[2];
				if (second->sons[0] != NULL) second->sons[0]->parent = second;
				first->sons[2] = NULL;
			}
		}
		else if (second == leaf) {
			if (third->size == 2) {
				if (leaf->sons[0] == NULL) {
					leaf->sons[0] = leaf->sons[1];
					leaf->sons[1] = NULL;
				}
				insertToNode(second, parent->keys[1]);
				parent->keys[1] = third->keys[0];
				//strcpy(parent->keys[1], third->keys[0]);
				deleteFromNode(third, third->keys[0]);
				second->sons[1] = third->sons[0];
				if (second->sons[1] != NULL) second->sons[1]->parent = second;
				third->sons[0] = third->sons[1];
				third->sons[1] = third->sons[2];
				third->sons[2] = NULL;
			}
			else if (first->size == 2) {
				if (leaf->sons[1] == NULL) {
					leaf->sons[1] = leaf->sons[0];
					leaf->sons[0] = NULL;
				}
				insertToNode(second, parent->keys[0]);
				parent->keys[0] = first->keys[1];
				//strcpy(parent->keys[0], first->keys[1]);
				deleteFromNode(first, first->keys[1]);
				second->sons[0] = first->sons[2];
				if (second->sons[0] != NULL) second->sons[0]->parent = second;
				first->sons[2] = NULL;
			}
		}
		else if (first == leaf) {
			if (leaf->sons[0] == NULL) {
				leaf->sons[0] = leaf->sons[1];
				leaf->sons[1] = NULL;
			}
			insertToNode(first, parent->keys[0]);
			if (second->size == 2) {
				parent->keys[0] = second->keys[0];
				//strcpy(parent->keys[0], second->keys[0]);
				deleteFromNode(second, second->keys[0]);
				first->sons[1] = second->sons[0];
				if (first->sons[1] != NULL) first->sons[1]->parent = first;
				second->sons[0] = second->sons[1];
				second->sons[1] = second->sons[2];
				second->sons[2] = NULL;
			}
			else if (third->size == 2) {
				parent->keys[0] = second->keys[0];
				//strcpy(parent->keys[0], second->keys[0]);
				second->keys[0] = parent->keys[1];
				//strcpy(second->keys[0], parent->keys[1]);
				parent->keys[1] = third->keys[0];
				//strcpy(parent->keys[1], third->keys[0]);
				deleteFromNode(third, third->keys[0]);
				first->sons[1] = second->sons[0];
				if (first->sons[1] != NULL) first->sons[1]->parent = first;
				second->sons[0] = second->sons[1];
				second->sons[1] = third->sons[0];
				if (second->sons[1] != NULL) second->sons[1]->parent = second;
				third->sons[0] = third->sons[1];
				third->sons[1] = third->sons[2];
				third->sons[2] = NULL;
			}
		}
	}
	else if (parent->size == 1) {
		insertToNode(leaf, parent->keys[0]);

		if (first == leaf && second->size == 2) {
			parent->keys[0] = second->keys[0];
			//strcpy(parent->keys[0], second->keys[0]);
			deleteFromNode(second, second->keys[0]);

			if (leaf->sons[0] == NULL) leaf->sons[0] = leaf->sons[1];

			leaf->sons[1] = second->sons[0];
			second->sons[0] = second->sons[1];
			second->sons[1] = second->sons[2];
			second->sons[2] = NULL;
			if (leaf->sons[1] != NULL) leaf->sons[1]->parent = leaf;
		}
		else if (second == leaf && first->size == 2) {
			parent->keys[0] = first->keys[1];
			//strcpy(parent->keys[0], first->keys[1]);
			deleteFromNode(first, first->keys[1]);

			if (leaf->sons[1] == NULL) leaf->sons[1] = leaf->sons[0];

			leaf->sons[0] = first->sons[2];
			first->sons[2] = NULL;
			if (leaf->sons[0] != NULL) leaf->sons[0]->parent = leaf;
		}
	}
	return parent;
}


bt23* delete23(bt23* head, int key){
	bt23* node = NULL;
	node = search23(head, key); 

	if (node == NULL) {
		//printf("Node has not been found\n");
		return head;
	}

	bt23* min = NULL;
	if (node->keys[0] == key) min = searchMin23(node->sons[1]); // Ищем эквивалентный ключ
	//if (strcmp(node->keys[0], key) == 0) min = searchMin(node->sons[1]); // Ищем эквивалентный ключ
	else min = searchMin23(node->sons[2]);

	if (min) { // menime klu e
		int* z;
		
		if (key == node->keys[0]) z = node->keys[0];
		
		else z = node->keys[1];

		swap(z, min->keys[0]);
		node = min; //
	}

	deleteFromNode(node, key); 
	printf("Node with key (%d) has been deleted.\n", key);
	return repair(node); 
}

bt23* init23(bt23* head, int key){

	head = (bt23*)malloc(sizeof(bt23));
	/*head->keys[0] = (unsigned char*)calloc(9, sizeof(unsigned char));
	head->keys[1] = (unsigned char*)calloc(9, sizeof(unsigned char));
	head->keys[2] = (unsigned char*)calloc(9, sizeof(unsigned char));*/

	head->keys[0] = key;
	//strcpy(head->keys[0], key);
	head->parent = NULL;
	head->sons[0] = head->sons[1] = head->sons[2] = NULL;
	head->size = 1;
	return head;
}

