#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "admin.route.h"
#include "user.route.h"

void SpecificDayIn7Days();
void SpecificWeekInMonth();
void printSingleProduct(UserPOS Product);
void CalculateDay(time_t *lastTime, time_t *lastLastTime, time_t *selectDate);
void CalculateWeek(time_t *lastTime, time_t *lastLastTime);

void SelectPointOfSales(){

    int choice;
    fflush(stdin);
    printf("\n\nHey Admin! What you want to do here");
    printf("\n(1) See Some Specific Days In 7 Days");
    printf("\n(2) See Some Week In Month");
    printf("\n(5) Exist");
    printf("\n\nYour choice\t:\t");
    if(scanf("%d",&choice) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        SelectPointOfSales();
        return;
    }

    switch (choice){
    case 1:
        SpecificDayIn7Days();
        break;

    case 2:
        SpecificWeekInMonth();
        break;

    case 3:
        // PrintUserCart(currentUser);
        break;

    case 4:
        // printf("CHECK BILL\n");
        // CheckBill(currentUser);
        break;
    
    case 5:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        SelectPointOfSales();
        break;
    }

}

void SpecificWeekInMonth(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    int size = 0;

    UserPOS tempProduct[1000];


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].cartOwner, sp);
        // printf("%s\n",tempProduct[size].cartOwner);;

        sp = strtok(NULL, ",");
        strcpy(tempProduct[size].productName, sp);

        sp = strtok(NULL, ",");
        tempProduct[size].singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempProduct[size].totalInCart = atoi(sp);

        
        sp = strtok(NULL, ",");
        tempProduct[size].totalCost = atoi(sp);
        
        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        tempProduct[size].timeStamp = (time_t) tempTime;

        size++;

    }
   
    time_t lastTime = time(NULL);
    time_t lastLastTime = time(NULL);
    
    CalculateWeek(&lastTime, &lastLastTime);
    int counter = 0;

    for (int i = 0; i < size; i++){
        if(tempProduct[i].timeStamp < lastTime && lastTime > lastLastTime){

            printSingleProduct(tempProduct[i]);
            counter++;
            
        }

    }

    printf("There Are :\t %d Transection In %.10s To",counter, ctime(&lastTime));
    printf("%.10s\n", ctime(&lastLastTime));

}

void CalculateWeek(time_t *lastTime, time_t *lastLastTime){
    int miltime = 24*60*60;
    time_t now = time(NULL);
    time_t week1 = now - (miltime); 
    time_t week2 = now - (miltime*7); 
    time_t week3 = now - (miltime*14); 
    time_t week4 = now - (miltime*21); 
    time_t week5 = now - (miltime*28); 
    time_t week6 = now - (miltime*35); 
    // printf("%d\n",size);


    printf("------------- What Week Point Of Sales Do You Want -------------\n");
    printf("(1) %.10s To ",ctime(&week1));
    printf("%.10s\n",ctime(&week2));

    printf("(2) %.10s To ",ctime(&week2));
    printf("%.10s\n",ctime(&week3));

    printf("(3) %.10s To ",ctime(&week3));
    printf("%.10s\n",ctime(&week4));

    printf("(4) %.10s To ",ctime(&week4));
    printf("%.10s\n",ctime(&week5));

    printf("(4) %.10s To ",ctime(&week5));
    printf("%.10s\n",ctime(&week6));

    int choice;
    scanf("%d",&choice);
    switch (choice){
    case 1:
        *lastTime = week1;    
        *lastLastTime = week2;   
        break;
    
    case 2:
        *lastTime = week2;    
        *lastLastTime = week3;   
        break;

    case 3:
        *lastTime = week3;    
        *lastLastTime = week4;   
        break;

    case 4:
        *lastTime = week4;    
        *lastLastTime = week5;   
        break;

    case 5:
        *lastTime = week5;    
        *lastLastTime = week6;   
        break;
    
    default:
        system("clear");
        printf("Please Enter A Correct Choice\n");
        CalculateWeek(lastTime, lastLastTime);
        return;
        break;
    }

}


void SpecificDayIn7Days(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    int size = 0;

    UserPOS tempProduct[1000];


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].cartOwner, sp);
        // printf("%s\n",tempProduct[size].cartOwner);;

        sp = strtok(NULL, ",");
        strcpy(tempProduct[size].productName, sp);

        sp = strtok(NULL, ",");
        tempProduct[size].singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempProduct[size].totalInCart = atoi(sp);

        
        sp = strtok(NULL, ",");
        tempProduct[size].totalCost = atoi(sp);
        
        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        tempProduct[size].timeStamp = (time_t) tempTime;

        size++;

    }

    time_t selectDate;
    time_t lastTime = time(NULL);
    time_t lastLastTime = time(NULL);

    CalculateDay(&lastLastTime, &lastTime, &selectDate);    
    
    int counter = 0;
    // printf("Last Time :\t%s\n",ctime(&lastTime));
    // printf("Last last Time :\t%s\n",ctime(&lastLastTime));
    char last[50];
    strcpy(last, ctime(&selectDate));
    last[11] = '\0';
    // char lastLast[50];
    // strcpy(lastLast, ctime(&lastLastTime));
    // lastLast[11] = '\0';
    // printf("%.10s\n",lastLast);

    for (int i = 0; i < size; i++){
        char tempTime[50];
        strcpy(tempTime, ctime(&tempProduct[i].timeStamp));
        tempTime[11] = '\0';

        // if(tempProduct[i].timeStamp > lastTime && tempProduct[i].timeStamp < lastLastTime){
            
        //     printSingleProduct(tempProduct[i]);
        //     counter++;

        // }
        
        if(strcmp(tempTime, last) == 0){
            printSingleProduct(tempProduct[i]);
            counter++;
        }

        // printf("Time :\t%s\n",ctime(&tempProduct[i].timeStamp));
        
    }
    
    printf("There Are :\t %d Transection In %.10s\n",counter, ctime(&selectDate));

}

void CalculateDay(time_t *lastTime, time_t *lastLastTime, time_t *selectDate){
    int choice;
    int day = 24*60*60;
    time_t now = time(NULL);
    time_t day1 = now - (day); 
    time_t day2 = now - (day*2); 
    time_t day3 = now - (day*3); 
    time_t day4 = now - (day*4); 
    time_t day5 = now - (day*5); 
    time_t day6 = now - (day*6); 
    time_t day7 = now - (day*7); 
    // printf("%d\n",size);


    printf("------------- What Date Point Of Sales Do You Want -------------\n");
    printf("(1) Last (24Hr) around %.10s\n",ctime(&day1));
    printf("(2) Last (48Hr) around %.10s\n",ctime(&day2));
    printf("(3) Last (72Hr) around %.10s\n",ctime(&day3));
    printf("(4) Last (96Hr) around %.10s\n",ctime(&day4));
    printf("(5) Last (120Hr) around %.10s\n",ctime(&day5));
    printf("(6) Last (144Hr) around %.10s\n",ctime(&day6));
    printf("(7) Last (168Hr) around %.10s\n",ctime(&day7));
    scanf("%d",&choice);
    switch (choice){
    case 1:
        *lastTime = *lastTime - (24*60*60);    
        *lastLastTime = *lastLastTime - (24*60*60*2);   
        *selectDate = day1; 
        break;
    case 2:
        *lastTime = *lastTime - (24*60*60*2);    
        *lastLastTime = *lastLastTime - (24*60*60*3);    
        *selectDate = day2; 
        break;
    case 3:
        *lastTime = *lastTime - (24*60*60*3);    
        *lastLastTime = *lastLastTime - (24*60*60*4);    
        *selectDate = day3; 
        break;
    case 4:
        *lastTime = *lastTime - (24*60*60*4);    
        *lastLastTime = *lastLastTime - (24*60*60*5);    
        *selectDate = day4; 
        break;
    case 5:
        *lastTime = *lastTime - (24*60*60*5);    
        *lastLastTime = *lastLastTime - (24*60*60*6);    
        *selectDate = day5; 
        break;
    case 6:
        *lastTime = *lastTime - (24*60*60*6);    
        *lastLastTime = *lastLastTime - (24*60*60*7);    
        *selectDate = day6; 
        break;
    case 7:
        *lastTime = *lastTime - (24*60*60*7);    
        *lastLastTime = *lastLastTime - (24*60*60*8);    
        *selectDate = day7; 
        break;
    
    default:
        system("clear");
        printf("Please Enter A Correct Choice\n");
        CalculateDay(lastTime, lastLastTime, selectDate);
        return;
        break;
    }
    
}


void printSingleProduct(UserPOS Product){

    printf("\tCart Owner                  :\t%s\n", Product.cartOwner);
    printf("\tProduct Name                :\t%s\n", Product.productName);
    printf("\tSingle Price Product        :\t%d\n", Product.singlePriceProduct);
    printf("\tTotal In Cart               :\t%d\n", Product.totalInCart);
    printf("\tTotal Cost                  :\t%d\n", Product.totalCost);
    printf("\tTime Stamps                 :\t%s\n", ctime(&Product.timeStamp));

}