#ifndef TREAP_H
#define TREAP_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// -----------------------------------------------------------------
// decTree
// -----------------------------------------------------------------

typedef struct decTree{
  struct decTree *that;
  struct treap *tree;

  size_t sizeOfData;

  void (*combineData)(void *root, void *left, void *right);
  void (*pushDown)(void *root, void *downData);
  void (*recalcData)(void *update, void *downData, size_t numElOfT);
} decTree;

void createDecTree(decTree *tree,
  void (*combineData)(void *root, void *left, void *right),
  void (*pushDown)(void *nextDownData, void *downData),
  void (*recalcData)(void *update, void *downData, size_t numElOfT),
  size_t sizeOfData
);
void addElementD(decTree *tree, void *data, size_t pos);
void* getSegmentD(decTree *tree, size_t l, size_t r);
void eraseSegmentD(decTree *tree, size_t l, size_t r);
void modifySegmentD(decTree *tree, size_t l, size_t r, void* downData);
void freeDecTree(decTree *tree);

// -----------------------------------------------------------------
// treap
// -----------------------------------------------------------------

typedef struct treap {
	void *data;
	void *downData;

	size_t size;
	int level;
	struct treap *left;
	struct treap *right;
} treap;

void clearT(treap **node);
void freeNodeT(treap **node);
treap* createNodeT(void *data, size_t sizeOfData, void *downData,
  size_t sizeOfDownData);

void pushT(treap **node, decTree *head);
void updateT(treap **node, decTree *head);

void* getDataT(treap *node);
size_t getSizeT(treap *node);

void mergeT(treap **root, treap *left, treap *right, decTree *head);
void splitT(treap *root, treap **left, treap **right, size_t key, decTree *head);

int addT(
  treap **root, void *data, void *downData,
  size_t sizeOfDownData, size_t pos, decTree *head
);
int eraseT(treap **root, size_t firstPos, size_t lastPos, decTree *head);
void* getT(treap *root, size_t pos);
void* getSubT(treap *root, size_t left, size_t right, decTree *head);

#endif
