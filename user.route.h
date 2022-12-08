#ifndef _USERROUTE_H
#define _USERROUTE_H

#include <time.h>

typedef struct {
  char userName[50];
  char email[50];
  char password[50];
  char phone[50];
  char role[10];
} User;

typedef struct {
  char cartOwner[50];
  char productName[50];
  int totalInCart;
  int singlePriceProduct;
  int totalCost;
  time_t timeStamp;
} UserCart;


void FirstTouch(int *loginOrNot, User *currentUser);

// ============= ADMIN CHOICE =============

void AdminSelection(User *currentUser);

// ============= END ADMIN CHOICE =============


// ============ Authentication ============

void Register(int *loginOrNot);
void Login(int *loginOrNot, User *currentUser);

// ========== END Authentication ==========



// ============== USER CART ===============

void PrintProductForUser();
void AddProductToCart(User *currentUser);
void PrintUserCart();
// ============ END USER CART =============



void UserSelection(User *currentUser);




#endif 