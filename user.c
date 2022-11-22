#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
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

int Register(){
    User user;
    int checkRole;
    FILE *fp;

    fp = fopen("user.csv", "a+");
 
    if (fp == NULL){
        printf("Error opening user.\n");
        return 1;
    }

    system("cls");
    printf("\n============Reigster Page============");

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

    
    printf("\nPlease enter your role:\t");
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
    
    if (ferror(fp)){
      printf("Error writing to file.\n");
      return 0;
    }
    fclose(fp);

    if(checkRole == 1){
        return 2;
    }
    
    else {
        return 1;
    }
    }
    return 0;

}

void PrintUserData(){

    FILE *fp;
    User users[1000];

    if (fp == NULL){
        printf("Error opening file.\n");
        return;
    }
    fp = fopen("user.csv", "r"); 
   
    char line[1000];

    char *sp;
    int i = 0;
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
    

    fclose(fp);

}

int NumberOfUser(){
    FILE *fp;

    if (fp == NULL){
        printf("Error opening file.\n");
        return 0;
    }
    fp = fopen("user.csv", "r"); 
   
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

    fp = fopen("user.csv","r");
    fpTemp = fopen("tempUser.csv","w");

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
        fp = fopen("user.csv","w");
        fpTemp = fopen("tempuser.csv","r");

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

    char fileName[FILENAME_SIZE] = "user.csv";
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