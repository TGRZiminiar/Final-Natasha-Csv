/* 
หน้านี้มีฟังก์ชันของ USER อย่างเดียว
1. ฟังก์ชันตั้งแต่เริ่มโปรแกรม = FirstTouch
2. ฟังก์ชันให้ user เลือกหลังจาก login = UserSelection

 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048


void FirstTouch(int *loginOrNot, User *currentUser){
    int choice;
    // system("cls");
    printf("\t============WELCOME TO SLEEP SHOP============");
    printf("\n\nPlease select your prefered operation");
    printf("\n(1) Login");
    printf("\n(2) Register");
    printf("\n(3) Exist");
    printf("\n\nYour choice\t:\t");
    scanf("%d",&choice);
    fgetc(stdin);

    switch (choice){
        case 1:
        Login(loginOrNot, currentUser);
        // printf("LOGIN %d\n",Login(loginOrNot));
        // printf("LOGIN OR NOT FROM CASE LOGIN %d\n",*loginOrNot);
        break;
        
        case 2:
        Register(loginOrNot);
        // printf("LOGIN OR NOT FROM CASE REGISTER %d\n",*loginOrNot);
        break;

        case 3:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

        default:
        printf("Your input is invalid, please try again");
        break;
    }
    // printf("LOGIN OR NOT %d\n",*loginOrNot);
    return;
}

void UserSelection(User *currentUser){
    
    int choice;
    
    // while (choice != 1 || choice != 2){
    printf("\n\nWhat you want to do here");
    printf("\n(1) See Other Product");
    printf("\n(2) Add Product To Cart");
    printf("\n(3) Check Your Cart");
    printf("\n(4) Check bill");
    printf("\n(5) Exist");
    printf("\n\nYour choice\t:\t");
    fflush(stdin);
    scanf("%d",&choice);

    switch (choice){
    case 1:
        PrintProductForUserSelection(currentUser);
        break;

    case 2:
        printf("ADD PRODUCT RUNNING\n");
        AddProductToCart(currentUser);
        break;

    case 3:
        PrintUserCart(currentUser);
        break;

    case 4:
        // printf("CHECK BILL\n");
        CheckBill(currentUser);
        break;
    
    case 5:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        UserSelection(currentUser);
        break;
    }
    // }

}


