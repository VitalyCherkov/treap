#include "treap.h"

void createDecTree(decTree *tree,
  void (*combineData)(void *root, void *left, void *right),
  void (*pushDown)(void *nextDownData, void *downData),
  void (*recalcData)(void *update, void *downData, size_t numElOfT)
){
  if(!tree || !combineData || !pushDown || !recalcData)
    return;

  tree->this = tree;
  tree->combineData = combineData;
  tree->pushDown = pushDown;
  tree->recalcData = recalcData;
  tree->tree = NULL;
}

void addElementD(decTree *tree, void *data, size_t sizeOfData, size_t pos){
  if(!tree || !data)
    return;
  addT(&tree->tree, data, sizeOfData, NULL, 0, pos, tree->this);
}

// Все изменения на отрезке [l, r];

void* getSegmentD(decTree *tree, size_t l, size_t r){
  if(!tree)
    return NULL;

  treap *ansT = getSubT(tree->tree, l, r, tree->this);
  if(!ansT)
    return NULL;

  return ansT->data;
}

void eraseSegmentD(decTree *tree, size_t l, size_t r){
  if(!tree)
    return;

  eraseT(&tree->tree, l, r, tree->this);
}

void modifySegmentD(decTree *tree, size_t l, size_t r, void* downData){
  if(!downData)
    return;

  treap *T = getSubT(tree->tree, l, r, tree->this);
  if(!T)
    return;

  tree->pushDown(T->downData, downData);
  pushT(&T, tree->this);
}

void freeDecTree(decTree *tree){
  if(tree == NULL)
    return;

  clearT(&tree->tree);
}
