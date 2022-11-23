#include <time.h>

#ifndef _PRODUCTROUTE_H
#define _PRODUCTROUTE_H

typedef struct {
  char productName[50];
  int productQuantity;
  int productPrice;
  int minimumQuantity;
} Product;

typedef struct {  
  char productName[50];
  int productQuantity;
  int productPrice;
  int productCost;
  int productProfit;
  time_t timeStamp;
} Sales;


void AddProduct();
void PrintProduct();
void EditProductInDB();
void RemoveProduct();
void test();

#endif 