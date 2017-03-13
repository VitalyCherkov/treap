#ifndef DEC_TREE_H
#define DEC_TREE_H

#include "treap.h"
#include <stdio.h>

struct decTree{
  struct decTree *this;
  struct treap *tree;

  void (*combineData)(void **root, void *left, void *right);
  void (*pushDown)(void **root, void *downData);
  void (*recalcData)(void **update, void *downData);
};

void createDecTree(struct decTree *tree,
  void (*combineData)(void **root, void *left, void *right),
  void (*pushDown)(void **root, void *downData),
  void (*recalcData)(void **update, void *downData)
);
void freeDecTree(struct decTree *tree);

#endif
