
#ifndef _ADMINROUTE_H
#define _ADMINROUTE_H

#include <time.h>

typedef struct {
  char productName[50];
  int productQuantity;
  int productPrice;
  int productCost;
  int productProfit;
  int minimumQuantity;
} Product;

typedef struct {  
  char ownerName[50];
  char productName[50];
  int productQuantity;
  int productPrice;
  int productCost;
  int productProfit;
  time_t timeStamp;
} ProductPOS;



// ============= ADMIN CHOICE =============

void CommandUser();
void CommandProduct();
// ============= END ADMIN CHOICE =============



// ============= Product CRUD =============

void AddProduct();
void PrintProduct();
void EditProductInDB();
void RemoveProduct();

// ===========END Product CRUD ===========




// ============== ADMIN USER ==============

void PrintUserData();
int NumberOfUser();
void EditUser();
void RemoveUser();

// =========== END ADMIN USER =============


// =========== USER CART =============

void FindProductByProductKey(int *productKey, Product *targetProduct);

// =========== END USER CART ============



// =========== ACCOUNTING SYSTEM =============


// ========= END ACCOUNTING SYSTEM ============




// ============ POINT OF SALE ==============

void SelectPointOfSales();

// ========= END POINT OF SALE ============



#endif 