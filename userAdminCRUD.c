#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"
#include <stdbool.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 2048


User makeUser(char *userName, char *email, char *password, char *phone, char *role){
  User user;
  
  strcpy(user.userName,userName);
  strcpy(user.email,email);
  strcpy(user.password,password);
  strcpy(user.phone,phone);
  strcpy(user.role,role);
  return user;

}

void PrintUserData(){

    FILE *fp;
    User users[1000];

    if (fp == NULL){
        printf("Error opening file.\n");
        return;
    }
    fp = fopen("database/User.csv", "r"); 
   
    char line[1000];

    char *sp;
    int i = 0;
    // TODO: print table header 
    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s",line);

        sp = strtok(line, ",");
        strcpy(users[i].userName, sp);

        sp = strtok(NULL, ",");
        strcpy(users[i].password, sp);

        sp = strtok(NULL, ",");
        strcpy(users[i].email, sp);

        sp = strtok(NULL, ",");
        strcpy(users[i].phone, sp);
        
        sp = strtok(NULL, ",");
        strcpy(users[i].role, sp);
        printf("Line %d\n",i);
        printf("%s %s %s %s %s",users[i].userName, users[i].password, users[i].email, users[i].phone, users[i].role);

        i++;
    }   
    // scanf("");

    fclose(fp);

}

int NumberOfUser(){
    FILE *fp;

    if (fp == NULL){
        printf("Error opening file.\n");
        return 0;
    }
    fp = fopen("database/User.csv", "r"); 
   
    char line[1000];

    char *sp;
    int i = 0;
    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s",line);

        i++;
    }   
    
    fclose(fp);

    printf("%d\n",i);

    return i;
}


void EditUser(){
    FILE *fp;
    FILE *fpTemp;
    
    if(fp == NULL){
        printf("Error Opening File.\n");
        return;
    }

    fp = fopen("database/User.csv","r");
    fpTemp = fopen("database/TempUser.csv","w");

    User users[1000];
    User updateUser;
    User tempUser;
    char line[1000];    
    int found = 0;
    char targetUser[100];
    PrintUserData();

    char *sp;
    printf("Enter Name That You Want To Update\t:\t");
    fgets(targetUser, 50, stdin);
    targetUser[strlen(targetUser)-1] = 0;
    bool keepReading = true;

    char buffer[MAX_LINE];

    while (fgets(line, 1000, fp) != NULL){
        if(feof(fp)) {
            keepReading = false;
        }
        // fgets(buffer, MAX_LINE, fp);
        sscanf(line, "%s", &updateUser.userName);

        sp = strtok(line, ",");
        strcpy(updateUser.userName, sp);

        sp = strtok(NULL, ",");
        strcpy(updateUser.password, sp);

        sp = strtok(NULL, ",");
        strcpy(updateUser.email, sp);

        sp = strtok(NULL, ",");
        strcpy(updateUser.phone, sp);
        
        sp = strtok(NULL, ",");
        strcpy(updateUser.role, sp);

        // printf("UserName %s\n",updateUser.userName);
        // printf("Password %s\n",updateUser.password);
        // printf("Email %s\n",updateUser.email);
        // printf("Phone %s\n",updateUser.phone);
        // printf("Role %s\n",updateUser.role);
        
        if(strcmp(targetUser, updateUser.userName) == 0){
            found = 1;

            printf("Current value for username is %s; please enter new value:", updateUser.userName );
            scanf("%s", &updateUser.userName);

            printf("Current value for email is %s; please enter new value:", updateUser.email );
            scanf("%s", &updateUser.email);

            printf("Current value for email is %s; please enter new value:", updateUser.phone );
            scanf("%s", &updateUser.phone);

            fprintf(fpTemp,
                "%s,%s,%s,%s,%s",
                updateUser.userName,
                updateUser.password,
                updateUser.email,
                updateUser.phone,
                updateUser.role
            );
        }

        else {
            fprintf(fpTemp,
                "%s,%s,%s,%s,%s",
                updateUser.userName,
                updateUser.password,
                updateUser.email,
                updateUser.phone,
                updateUser.role
            );
        }
    }
    
    fclose(fp);
    fclose(fpTemp);

    if(found == 1){
        fp = fopen("database/User.csv","w");
        fpTemp = fopen("database/TempUser.csv","r");

        while (fgets(line, 1000, fpTemp) != NULL){
            if(feof(fp)) {
                keepReading = false;
            }

            sscanf(line, "%s", &tempUser.userName);

            sp = strtok(line, ",");
            strcpy(tempUser.userName, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.password, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.email, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.phone, sp);
            
            sp = strtok(NULL, ",");
            strcpy(tempUser.role, sp);
        
            fprintf(fp,
            "%s,%s,%s,%s,%s",
            tempUser.userName,
            tempUser.password,
            tempUser.email,
            tempUser.phone,
            tempUser.role
            );
        }
        fclose(fp);
        fclose(fpTemp);
    }
    else {
        printf("DATA NOT FOUND\n");
    }
}



void RemoveUser(){

    FILE *fp, *fpTemp;

    char fileName[FILENAME_SIZE] = "database/User.csv";
    char tempFileName[FILENAME_SIZE];
    char buffer[MAX_LINE];
    int deleteLine = 0;
    PrintUserData();
    strcpy(tempFileName, "temp____");
    strcat(tempFileName, fileName);

    printf("Delete Line: ");
    scanf("%d",&deleteLine);

    fp = fopen(fileName, "r");
    fpTemp = fopen(tempFileName, "w");

    if(fp == NULL || fpTemp == NULL){
        printf("FILE FORMAT ERROR\n");
        return;
    }

    bool keepReading = true;
    int currentLine = 1;
    do{
        fgets(buffer, MAX_LINE, fp);
        if(feof(fp)) keepReading = false;
        else if(currentLine != deleteLine){
            fputs(buffer, fpTemp);
        }
        currentLine++;

    } while (keepReading);
    
    fclose(fp);
    fclose(fpTemp);

    remove(fileName);
    rename(tempFileName, fileName);
    return;

}   

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