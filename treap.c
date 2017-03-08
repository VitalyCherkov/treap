#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "treap.h"
//#include "decTree.h"

void clearT(treap **node){
  if(*node == NULL)
    return;
  clearT(&(*node)->left);
  clearT(&(*node)->right);
  freeNodeT(node);
}
void freeNodeT(treap **node){
  if(*node){
    free((*node)->data);
    free((*node)->downData);
  }
  else
    return;
  free(*node);
  *node = NULL;
};
treap* createNodeT(void *data, size_t sizeOfData, void *downData, size_t sizeOfDownData){
  treap *node = NULL;

  node = malloc(sizeof(treap));
  if(node == NULL){
    return NULL;
  }

  node->data = malloc(sizeOfData);
  if(node->data == NULL){
    freeNodeT(&node);
    return NULL;
  }

  memcpy(node->data, data, sizeOfData);
  if(node->data == NULL){
    freeNodeT(&node);
    return NULL;
  }

  if(downData){
    node->downData = malloc(sizeOfDownData);
    if(node->downData == NULL){
      freeNodeT(&node);
      return NULL;
    }

    memcpy(node->downData, downData, sizeOfDownData);
    if(node->downData == NULL){
      freeNodeT(&node);
      return NULL;
    }
  }
  else{
    node->downData = NULL;
  }

  node->size = 1;
  node->level = rand();
  node->left = NULL;
  node->right = NULL;
  return node;
}

void pushT(treap **node, decTree *head){
  if(!*node)
    return;
  head->recalcData((*node)->data, (*node)->downData, (*node)->size);

  if((*node)->left)
    head->pushDown((*node)->left->downData, (*node)->downData);
  if((*node)->right)
    head->pushDown((*node)->right->downData, (*node)->downData);

  free((*node)->downData);
  (*node)->downData = NULL;
}
void updateT(treap **node, decTree *head){
  if(*node == NULL)
    return;

  pushT(node, head);
  pushT(&(*node)->left, head);
  pushT(&(*node)->right, head);
  (*node)->size = getSizeT((*node)->left) + getSizeT((*node)->right) + 1;

  head->combineData((*node)->data, getDataT((*node)->left), getDataT((*node)->right));
}

void* getDataT(treap *node){
  return !node ? NULL : node->data;
}
size_t getSizeT(treap *node){
  return node == NULL ? 0 : node->size;
}


// В левом дереве останется ровно key вершин
void splitT(treap *root, treap **left, treap **right, size_t key, decTree *head){
  if(root == NULL){
    *left = *right = NULL;
    return;
  }
  pushT(left, head);
  pushT(right, head);

  // Если корень должен принадлежать левому поддереву
  if(key > getSizeT((*root).left)){
    treap *newTr = NULL;
    splitT(root->right, &newTr, right, key - getSizeT(root->left) - 1, head);
    (*left) = root;
    (*left)->right = newTr;
  }
  else{
    treap *newTr = NULL;
    splitT(root->left, left, &newTr, key, head);
    (*right) = root;
    (*right)->left = newTr;
  }

  updateT(left, head);
  updateT(right, head);
}

void mergeT(treap **root, treap *left, treap *right, decTree *head){
  pushT(root, head);
  if(left == NULL || right == NULL){
    (*root) = left == NULL ? right : left;
    return;
  }
  if(left->level > right->level){
    mergeT(&left->right, left->right, right, head);
    (*root) = left;
  }
  else{
    mergeT(&right->left, left, right->left, head);
    (*root) = right;
  }
  updateT(root, head);
}

int addT(treap **root, void *data, size_t sizeOfData, void *downData,
  size_t sizeOfDownData, size_t pos, decTree *head
){
  treap *newData = createNodeT(data, sizeOfData, downData, sizeOfDownData);

  if(newData == NULL)
    return EXIT_FAILURE;

  treap *left = NULL;
  treap *right = NULL;

  splitT(*root, &left, &right, pos, head);
  mergeT(&left, left, newData, head);
  mergeT(root, left, right, head);

  return EXIT_SUCCESS;
}

int eraseT(treap **root, size_t firstPos, size_t lastPos, decTree *head){
  if(*root == NULL)
    return EXIT_FAILURE;
  treap *left = NULL;
  treap *middle = NULL;
  treap *right = NULL;

  splitT(*root, &left, &right, lastPos + 1, head);
  splitT(left, &left, &middle, firstPos, head);
  clearT(&middle);
  mergeT(root, left, right, head);

  return EXIT_SUCCESS;
}

void* getT(treap *root, size_t pos){
  if(root == NULL || pos > getSizeT(root))
    return NULL;
  if(pos == getSizeT(root->left))
    return root->data;
  if(pos < getSizeT(root->left))
    return getT(root->left, pos);
  return getT(root->right, pos - getSizeT(root->left) - 1);
}

void* getSubT(treap *root, size_t left, size_t right, decTree *head){
  if(!root)
    return NULL;

  treap *ansT = NULL;
  treap *lT = NULL;
  treap *rT = NULL;

  splitT(root, &lT, &rT, right + 1, head);
  splitT(lT, &lT, &ansT, left, head);

  if(!ansT)
    return NULL;

  return ansT;
}
