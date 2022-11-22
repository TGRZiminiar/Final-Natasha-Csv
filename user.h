#include <time.h>

#ifndef POINTOPERATIONS_H_
#define POINTOPERATIONS_H_

typedef struct {
  char userName[50];
  char email[50];
  char password[50];
  char phone[50];
  char role[10];
} User;


int Register();
// int Login();
void PrintUserData();
int NumberOfUser();
void EditUser();
void RemoveUser();
// void UpdateUserInDb();
// void DeleteUserInDb();
// User makeUser(char *userName, char *email, char *password, char *phone, char *role);

#endif /* POINTOPERATIONS_H_ */