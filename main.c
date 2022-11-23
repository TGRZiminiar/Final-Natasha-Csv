
#include <stdio.h>
#include "product.route.h"
#include <string.h>
#include <stdlib.h>
// #include "headerFile/userAuth.h"
#include "user.route.h"

int main(void){
  
  int loginOrNot = 0;
  // 0 = NotLogin 1 = AdminLogin 2 = UserLogin
  
  char keepGoingOrNot = 'y';
  

  while (loginOrNot == 0){
    FirstTouch(&loginOrNot);
    printf("LOGIN OR NOT FROM WHILE %d\n",loginOrNot);
    if(loginOrNot == 0){
      system("cls");
      printf("========= Your UserName Or Password Is Wronge =========\n");
    }
  }
  
  if(loginOrNot == 1){
    // AdminChoice();
    printf("Admin Login\n");
  }

  else if(loginOrNot == 2){
    printf("User Login\n");
  }

 

  return 0;
}


/* 
int main(void){
  
  int loginOrNot = 0;
  // 0 = NotLogin 1 = UserLogin 2 = AdminLogin
  char keepGoingOrNot = 'y';
  while(keepGoingOrNot == 'y'){
    printf("THIS IS LOGINORNOT %d\n",loginOrNot);
    if(loginOrNot == 0){
      int choice;
      system("cls");
      printf("\t============WELCOME TO SLEEP SHOP============");
      printf("\n\nPlease select your prefered operation");
      printf("\n(1) Login");
      printf("\n(2) Register");
      printf("\n(3) PrintDb User");
      printf("\n(4) Number User");
      printf("\n(5) Edit User");
      printf("\n(6) Remove User");
      printf("\n(7) Add Product");
      printf("\n(8) Print Product");
      printf("\n(9) Edit Product");
      printf("\n(10) Remove Product");
      printf("\n(11) Exist");
      printf("\n\nYour choice\t:\t");
      scanf("%d",&choice);
      fgetc(stdin);

      switch (choice){
        case 1:
          loginOrNot = Login();
          break;
        
        case 2:
          loginOrNot = Register();
          break;

        case 3:
          PrintUserData();
          break;
        
        case 4:
           
            printf("Number Of User %d\n",NumberOfUser());
            break;

        case 5:
            EditUser();
            break;
      
        case 6:
            RemoveUser();
            break;

        case 7:
          AddProduct();
          break;
        
        case 8:
          PrintProduct();
          break;
        
        case 9:
          EditProductInDB();
          break;
       
        case 10:
          RemoveProduct();
          break;

        case 11:
          printf("\n\t\t Bye Bye :)\n\n");
          exit(0);
          break;

        default:
          printf("Your input is invalid, please try again");
          break;
      }
    }

    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&keepGoingOrNot);
  }
  return 0;
}

 */