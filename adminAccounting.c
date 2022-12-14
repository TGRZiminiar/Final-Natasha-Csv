#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.route.h"
#include "user.route.h"

void SeeAllProfit();
void CalculateWeekAccounting(time_t *lastTime, time_t *lastLastTime, time_t *selectDate);
void DeleteDuplicate(ProductPOS product[], int *size);
void ProfitByProductName();
void ProfitTimeRange();
void SortProduct(ProductPOS product[], int size);


void SelectAccounting(){

    int choice;
    fflush(stdin);
    printf("\n\nHey Admin! What you want to do here");
    printf("\n(1) See All Profit");
    printf("\n(2) Profit Specific Product");
    printf("\n(3) Profit Time Range");
    printf("\n(4) Exist");
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
        ProfitByProductName();
        break;

    case 3:
        ProfitTimeRange();
        break;

    case 4:
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

    int sumProfit = 0;
    int sumCost = 0;


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
                tempProduct[i].productPrice = tempProduct[i].totalCost;
                tempProduct[i].productCost = productData.productCost;
                tempProduct[i].productProfit = productData.productProfit;
                tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                tempProduct[i].productQuantity = productData.productQuantity;
                tempProduct[i].singlePriceProduct = productData.productPrice;
                sumProfit += tempProduct[i].sumProfit;
                sumCost += tempProduct[i].productCost;
            }
        }
    }

    printf("Product Profit Of All Time :\t%d\n", sumProfit);
    printf("Product Cost Of All Time :\t%d\n", sumCost);

}


void ProfitByProductName(){

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
                tempProduct[i].productPrice = tempProduct[i].totalCost;
                tempProduct[i].productCost = productData.productCost;
                tempProduct[i].productProfit = productData.productProfit;
                tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                tempProduct[i].productQuantity = productData.productQuantity;
                tempProduct[i].singlePriceProduct = productData.productPrice;
            }
        }
    }
  

    DeleteDuplicate(tempProduct, &size);

    // for (int i = 0; i < size; i++){

    //     if(strcmp(tempProduct[i].productName, "None") != 0){

    //         printf("Product Name                :\t%s \n", tempProduct[i].productName);
    //         // printf("productCost             :\t %d \n", tempProduct[i].productCost);
    //         // printf("productPrice            :\t %d \n", tempProduct[i].productPrice);
    //         // printf("productProfit           :\t %d \n", tempProduct[i].productProfit);
    //         // printf("singlePriceProduct      :\t %d \n", tempProduct[i].singlePriceProduct);
    //         // printf("productCost             :\t %d \n", tempProduct[i].productCost);
    //         // printf("sumProfit               :\t %d \n", tempProduct[i].sumProfit);
    //         // printf("ToTal Sell              :\t %d \n", tempProduct[i].totalInCart);
    //         // printf("\n\n");
       
    //     }
    // }

   
    SortProduct(tempProduct, size);
    int counter = 1;

    for (int i = 0; i < size; i++){
        if(strcmp(tempProduct[i].productName, "None") != 0){
            printf("Rank %d\n",counter);
            printf("Product Name             :\t %s \n", tempProduct[i].productName);
            printf("Product Cost             :\t %d \n", tempProduct[i].productCost);
            printf("Product Profit           :\t %d \n", tempProduct[i].productProfit);
            printf("ToTal Sell               :\t %d \n", tempProduct[i].totalInCart);
            printf("Sum Profit               :\t %d \n", tempProduct[i].sumProfit);
            printf("\n\n");
            counter++;
        }
    }
    

}




void DeleteDuplicate(ProductPOS product[], int *size){
    
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            if(i == j || product[i].productQuantity == 0 || strcmp(product[i].productName, "None") == 0) continue;

            else if(strcmp(product[i].productName, product[j].productName) == 0){
                
                strcpy(product[j].productName, "None");
                product[i].totalInCart += product[j].totalInCart;
                product[i].sumProfit += product[j].sumProfit;
                product[i].productCost += product[j].productCost;
                product[j].productQuantity = 0;

            }
        }
    }
}


void ProfitTimeRange(){

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
                tempProduct[i].productPrice = tempProduct[i].totalCost;
                tempProduct[i].productCost = productData.productCost;
                tempProduct[i].productProfit = productData.productProfit;
                tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                tempProduct[i].productQuantity = productData.productQuantity;
                tempProduct[i].singlePriceProduct = productData.productPrice;
            }
        }
    }

    


    
}

void CalculateWeekAccounting(time_t *lastTime, time_t *lastLastTime, time_t *selectDate){

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
        CalculateWeekAccounting(lastTime, lastLastTime, selectDate);
        return;
        break;
}}


void SortProduct(ProductPOS product[], int size){

    for (int i = 0; i < size-1; i++){
        for (int j = 0; j < size-1-i; j++){
            if(product[j].productProfit < product[j+1].productProfit){
                ProductPOS temp = product[j];
                product[j] = product[j+1];
                product[j+1] = temp;
            }
        }
        
    }
    

}