#include <time.h>

#ifndef _USERROUTE_H
#define _USERROUTE_H

typedef struct {
  char userName[50];
  char email[50];
  char password[50];
  char phone[50];
  char role[10];
} User;

void Register(int *loginOrNot);
void Login(int *loginOrNot);
void FirstTouch(int *loginOrNot);
void PrintUserData();
int NumberOfUser();
void EditUser();
void RemoveUser();

#endif 