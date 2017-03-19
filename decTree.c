#include "treap.h"

void createDecTree(decTree *tree,
  void (*combineData)(void *root, void *left, void *right),
  void (*pushDown)(void *nextDownData, void *downData),
  void (*recalcData)(void *update, void *downData, size_t numElOfT),
  size_t sizeOfData
){
  if(!tree || !combineData || !pushDown || !recalcData || !sizeOfData)
    return;

  tree->that = tree;
  tree->combineData = combineData;
  tree->pushDown = pushDown;
  tree->recalcData = recalcData;

  tree->sizeOfData = sizeOfData;
  tree->tree = NULL;
}

void addElementD(decTree *tree, void *data, size_t pos){
  if(!tree || !data)
    return;
  addT(&tree->tree, data, NULL, 0, pos, tree->that);
}

// Все изменения на отрезке [l, r];

void* getSegmentD(decTree *tree, size_t l, size_t r){
  if(!tree)
    return NULL;

  void *ansT = getSubT(tree->tree, l, r, tree->that);
  if(!ansT)
    return NULL;

  return ansT;
}

void eraseSegmentD(decTree *tree, size_t l, size_t r){
  if(!tree)
    return;

  eraseT(&tree->tree, l, r, tree->that);
}

void modifySegmentD(decTree *tree, size_t l, size_t r, void* downData){
  if(!downData)
    return;

  treap *T = getSubT(tree->tree, l, r, tree->that);
  if(!T)
    return;

  tree->pushDown(T->downData, downData);
  pushT(&T, tree->that);
}

void freeDecTree(decTree *tree){
  if(tree == NULL)
    return;

  clearT(&tree->tree);
}
