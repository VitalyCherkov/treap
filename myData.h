#ifndef MYDATA_H
#define MYDATA_H

#include <stdio.h>
#include <stdlib.h>

int Max(int a, int b);
int Min(int a, int b);

typedef struct myData{
  int val;
  int sum;
  int mx;
  int mn;
} myData;
typedef struct myDownData{
  int multipler;
  int addendum;
} myDownData;

myData createMyData(int val);
myDownData createMyDownData(int multipler, int addendum);
int getSum(void *v);
int getMax(void *v);
int getMin(void *v);
int getVal(void *v);
void myCombine(void *root, void *left, void *right);
void myPushDown(void *nextDownData, void *downData);
void myRecalcData(void *update, void *downData, size_t numElOfT);

#endif //MYDATA_H
