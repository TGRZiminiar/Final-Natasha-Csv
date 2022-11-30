/* 
1. ฟังก์ชัน Login user จะใช้ pointer ส่งค่ามาเพื่อที่จะเอาไปเช้คว่าเป้น admin ไหม = Login
2. ฟังก์ชั่น Register pointer เหมือน login = Register
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"
#define FILENAME_SIZE 1024
#define MAX_LINE 2048


void Login(int *loginOrNot, User *currentUser){

    User user;
    FILE *fp;

    char userName[50];
    char password[50];

    printf("\n------------- Please Fill UserName And Password ---------------\n\n");
    printf("\tUserName  :\t");
    fgets(userName, 50, stdin);
    userName[strlen(userName)-1] = 0;

    printf("\tPassword  :\t");
    fgets(password, 50, stdin);
    password[strlen(password)-1] = 0;


    fp = fopen("database/User.csv","r");
    char line[1000];
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        sp = strtok(line, ",");

        strcpy(user.userName, sp);
        
        sp = strtok(NULL, ",");
        strcpy(user.password, sp);
        //Email
        sp = strtok(NULL, ",");
        strcpy(user.email, sp);
        //Phone
        sp = strtok(NULL, ",");
        strcpy(user.phone, sp);
        //Role
        sp = strtok(NULL, ",");
        strcpy(user.role, sp);
        // printf("ThIS IS USER ROLE => %s\n",user.role);
        user.role[strlen(user.role)-1] = 0;

        if(strcmp(user.userName, userName) == 0 && strcmp(user.password, password) == 0){
            printf("Login Success \n");
            strcpy(currentUser->userName, user.userName);
            strcpy(currentUser->email, user.email);
            strcpy(currentUser->phone, user.phone);
            strcpy(currentUser->role, user.role);

            if(strcmp(user.role, "admin") == 0){
                // printf("Role Admin \n");
                *loginOrNot = 1;
                break;
            }
            else if(strcmp(user.role, "user") == 0){
                // printf("Role User \n");
                *loginOrNot = 2;
                break;
            }
        }
        else continue;

    }
    
    return;
    

}

void Register(int *loginOrNot){
    User user;
    int checkRole;
    FILE *fp;

    fp = fopen("database/User.csv", "a+");
 
    if (fp == NULL){
        printf("Error opening User.csv\n");
        return;
    }

    // system("cls");
    printf("\n============Register Page============");

    printf("\nPlease enter your userName:\t");
    fgets(user.userName,50,stdin);
    user.userName[strlen(user.userName)-1] = 0;
    
    printf("\nPlease enter your password:\t");
    fgets(user.password,50,stdin);
    user.password[strlen(user.password)-1] = 0;
    
    printf("\nPlease enter your email:\t");
    fgets(user.email,50,stdin);
    user.email[strlen(user.email)-1] = 0;

    
    printf("\nPlease enter your phone:\t");
    fgets(user.phone,50,stdin);
    user.phone[strlen(user.phone)-1] = 0;

    
    printf("\nPlease enter your role [1 = admin, 0 = user]:\t");
    scanf("%d",&checkRole);

    
    if(checkRole == 1){
      strcpy(user.role,"admin");
    }
    else{
      strcpy(user.role,"user");
    }


    printf("\n------------- User Detail ---------------\n\n");
    printf("\tUserName  :\t%s\n",user.userName);
    printf("\tPassword  :\t%s\n",user.password);
    printf("\tEmail     :\t%s\n",user.email);
    printf("\tPhone     :\t%s\n",user.phone);
    printf("\tRole      :\t%s\n",user.role);
    printf("\n\n");
    printf("\nDo you want to save the invoice [y/n]:\t");
    char saveBill;
    scanf("%s",&saveBill);

    if(saveBill == 'y'){

       fprintf(fp,
            "%s,%s,%s,%s,%s\n",
            user.userName,
            user.password,
            user.email,
            user.phone,
            user.role
        );
    if(fwrite != 0){
        printf("\nSuccessfully saved");
    }
    else{
        printf("\nError saving");
    } 
    
    if (ferror(fp)){
      printf("Error writing to file.\n");
      return;
    }
    fclose(fp);

    if(checkRole == 1){
        *loginOrNot = 2;
        return;
    }
    
    else {
        *loginOrNot = 1;
        return;
    }
    }
    *loginOrNot = 0;
    return;

}