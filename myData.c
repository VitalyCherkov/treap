#include "myData.h"

int Max(int a, int b){
  if(a > b)
    return a;
  return b;
}
int Min(int a, int b){
  if(a < b)
    return a;
  return b;
}

myData createMyData(int val){
  myData newData = {val, val, val, val};
  return newData;
}
myDownData createMyDownData(int multipler, int addendum){
  myDownData newDownData = {multipler, addendum};
  return newDownData;
}

int getSum(void *v){ return !v ? 0 :((myData*)v)->sum; }
int getMax(void *v){ return !v ? -2000000000 : ((myData*)v)->mx; }
int getMin(void *v){ return !v ? 2000000000 : ((myData*)v)->mn; }
int getVal(void *v){ return ((myData*)v)->val; }

void myCombine(void *root, void *left, void *right){
  if(!root)
    return;
  ((myData*)root)->sum = getVal(root) + getSum(left) + getSum(right);
  ((myData*)root)->mn = Min(getVal(root), Min(getMin(left), getMin(right)));
  ((myData*)root)->mx = Max(getVal(root), Max(getMax(left), getMax(right)));
}

void myPushDown(void *nextDownData, void *downData){
  if(!downData)
    return;
  if(!nextDownData)
    nextDownData = downData;

  ((myDownData*)nextDownData)->multipler *= ((myDownData*)downData)->multipler;
  ((myDownData*)nextDownData)->addendum *= ((myDownData*)downData)->multipler;
  ((myDownData*)nextDownData)->addendum += ((myDownData*)downData)->addendum;
}

void myRecalcData(void *update, void *downData, size_t numElOfT){
  if(!update || !downData)
    return;

  myDownData* dd = (myDownData*)update;

  ((myData*)update)-> val *= dd->multipler;
  ((myData*)update)-> val += dd->addendum;

  ((myData*)update)-> sum *= dd->multipler;
  ((myData*)update)-> sum += dd->addendum * numElOfT;

  ((myData*)update)-> mn *= dd->multipler;
  ((myData*)update)-> mn += dd->addendum;

  ((myData*)update)-> mx *= dd->multipler;
  ((myData*)update)-> mx += dd->addendum;
}
