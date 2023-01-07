#pragma once

typedef struct BinaryTree btree;

btree* searchAVL(btree* Head, int index);

btree* insertAVL(btree* Head, int index);

btree* deleteAVL(btree* Head, int index);

btree* initAVL(int index);