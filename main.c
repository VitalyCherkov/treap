#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "treap.h"
#include "myData.h"

#define true 1
#define false 0

void addElement(decTree *myTree){
  if(!myTree)
    return;
  int val;
  size_t pos;
  if(scanf("%d %zu\n", &val, &pos) != 2)
    return;
  myData newData = createMyData(val);
  addElementD(myTree, &newData, sizeof(newData), pos);
}
void removeSegment(decTree *myTree){
  if(!myTree)
    return;
  size_t lPos, rPos;
  if(scanf("%zu %zu", &lPos, &rPos) != 2)
    return;
  eraseSegmentD(myTree, lPos, rPos);
}
void modifySegment(decTree *myTree){
  if(!myTree)
    return;
  int multipler, addendum;
  size_t lPos, rPos;
  if(fscanf(stdin, "%zu %zu\n%d %d", &lPos, &rPos, &multipler, &addendum) != 4)
    return;
  myDownData md = createMyDownData(multipler, addendum);
  modifySegmentD(myTree, lPos, rPos, &md);
}
void printSegment(decTree *myTree){
  if(!myTree)
    return;
  size_t lPos, rPos;
  if(scanf("%zu %zu", &lPos, &rPos) != 2)
    return;

  myData *md = (myData*)getSegmentD(myTree, lPos, rPos);
  if(!md)
    return;

  printf(
    "val: %d\nsum: %d\nmax: %d\n min: %d\n----\n",
    md->val, md->sum, md->mx, md->mn
  );
}

void menu(decTree *myTree){
  printf("[1] - add element\n");
  printf("[2] - remove segment\n");
  printf("[3] - modify segment\n");
  printf("[4] - get in segment\n");
  printf("[0] - stop & EXIT\n");

  int item;
  while(true){
    if(scanf("%d", &item) != 1)
      continue;
    if(!item)
      break;
    switch (item) {
      case 1:
        addElement(myTree);
        break;
      case 2:
        removeSegment(myTree);
        break;
      case 3:
        modifySegment(myTree);
        break;
      case 4:
        printSegment(myTree);
        break;
      default:
        break;
    }
  }
}

int main(){
  decTree myTree;
  createDecTree(&myTree, myCombine, myPushDown, myRecalcData);
  menu(&myTree);
  freeDecTree(&myTree);
  return 0;
}
