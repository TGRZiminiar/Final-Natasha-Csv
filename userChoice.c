#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048


void FirstTouch(int *loginOrNot){
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
        Login(loginOrNot);
        // printf("LOGIN %d\n",Login(loginOrNot));
        printf("LOGIN OR NOT FROM CASE LOGIN %d\n",*loginOrNot);
        break;
        
        case 2:
        Register(loginOrNot);
        printf("LOGIN OR NOT FROM CASE REGISTER %d\n",*loginOrNot);
        break;

        case 3:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

        default:
        printf("Your input is invalid, please try again");
        break;
    }
    printf("LOGIN OR NOT %d\n",*loginOrNot);
    return;
}

