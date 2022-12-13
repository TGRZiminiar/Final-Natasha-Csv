#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.route.h"
#include "user.route.h"

void SeeAllProfit();

void SelectAccounting(){

    int choice;
    fflush(stdin);
    printf("\n\nHey Admin! What you want to do here");
    printf("\n(1) See All Profit");
    printf("\n(3) Exist");
    printf("\n\nYour choice\t:\t");
     if(scanf("%d",&choice) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        SelectPointOfSales();
        return;
    }

    switch (choice){
    case 1:
        // SpecificDayIn7Days();
        SeeAllProfit();
        break;

    case 2:
        // SpecificWeekInMonth();
        break;

    case 3:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        SelectAccounting();
        break;
    }

}

void SeeAllProfit(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    ProductPOS tempProduct[1000];
    int size = 0;

    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].ownerName, sp);
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

    fclose(fp);
    
    FILE *fpProduct;
    fpProduct = fopen("database/Product.csv","r");
    Product productData;

    while (fgets(line, 1000, fpProduct) != NULL){

        // printf("\n%s\n",line);
        sp = strtok(line, ",");
        strcpy(productData.productName, sp);
        
        sp = strtok(NULL, ",");
        productData.productPrice = atoi(sp);

        sp = strtok(NULL, ",");
        productData.productQuantity = atoi(sp);
        
        sp = strtok(NULL, ",");
        productData.productCost = atoi(sp);
      
        sp = strtok(NULL, ",");
        productData.productProfit = atoi(sp);

        sp = strtok(NULL, ",");
        productData.minimumQuantity = atoi(sp);

        for (int i = 0; i < size; i++){
            if(strcmp(tempProduct[i].productName, productData.productName) == 0){
                tempProduct[i].productCost = productData.productCost;
                tempProduct[i].productProfit = productData.productProfit;
                tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                tempProduct[i].productQuantity = productData.productQuantity;
                tempProduct[i].singlePriceProduct = productData.productPrice;
            }
        }
    }

    for (int i = 0; i < size; i++){
        printf("ownerName               :\t %s \n",tempProduct[i].ownerName);
        printf("productCost             :\t %d \n",tempProduct[i].productCost);
        printf("productName             :\t %s \n",tempProduct[i].productName);
        printf("productPrice            :\t %d \n",tempProduct[i].productPrice);
        printf("productProfit           :\t %d \n",tempProduct[i].productProfit);
        printf("productQuantity         :\t %d \n",tempProduct[i].productQuantity);
        printf("singlePriceProduct      :\t %d \n",tempProduct[i].singlePriceProduct);
        printf("productCost             :\t %d \n",tempProduct[i].productCost);
        printf("sumProfit               :\t %d \n",tempProduct[i].sumProfit);
        printf("productQuantity         :\t %d \n",tempProduct[i].productQuantity);
        printf("\n\n");
    }
    




}