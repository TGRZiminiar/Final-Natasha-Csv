/* 
ไฟล์ที่เกี่ยวกับให้พวกตะกร้าสินค้าของ user ทุกอย่างที่ user ต้องเกี่ยวข้องกับสินค้าจะรวมไว้ที่นี้
1. Print Product ทั้งหมดที่มีให้ user ดู = PrintProductForUser
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"
#include "admin.route.h"

void PrintProductForUser(){
    Product product;
    FILE *fp;

    fp = fopen("database/Product.csv","r");
    printf("\n ****Product Information****\n");
    int i = 1;
    char line[1000];
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s\n",line);
        printf("----------- Product Key : %d -------------\n\n",i);

        sp = strtok(line, ",");
        strcpy(product.productName, sp);
        printf("\tProduct Name                  :\t%s\n", product.productName);
        
        sp = strtok(NULL, ",");
        product.productPrice = atoi(sp);
        printf("\tProduct Price                 :\t%d\n", product.productPrice);

        sp = strtok(NULL, ",");
        product.productQuantity = atoi(sp);
        printf("\tProduct Quantity              :\t%d\n", product.productQuantity);

        printf("\n\n");
        i++;
    }

    fclose(fp);    
}

void FindProductByProductKey(int *productKey, Product *targetProduct){

    FILE *fp;
    Product product;
    

    char line[1000];
    int i = 1;
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        
        if(i == *productKey){
            
            // Product Name
            sp = strtok(line, ",");
            strcpy(targetProduct->productName, sp);
            
            // Product Price
            sp = strtok(NULL, ",");
            targetProduct->productPrice = atoi(sp);
            
            // Product Quantity
            sp = strtok(NULL, ",");
            targetProduct->productQuantity = atoi(sp);
            *productKey = 0;
            break;   
        }

        i++;
    }   
    return;
}


void AddProductToCart(User *currentUser){

    FILE *fp;
    FILE *fpOpenProduct;
    Product *targetProduct;
    targetProduct = calloc(1, sizeof(Product));

    UserCart *userCart;
    userCart = calloc(1, sizeof(UserCart));

    fp = fopen("database/UserCard.csv","a+");

    if(fp == NULL){
        printf("Error Opening UserCard.csv\n");
        return;
    }


    char continueOrNot = 'y';
    int productKey;
    while (continueOrNot == 'y'){
        printf("Add Product To Your Cart\n");
        PrintProductForUser();
        printf("Enter Product Key To Add Product To Cart\n");
        scanf("%d",&productKey);
        FindProductByProductKey(&productKey, targetProduct);
        if(productKey == 0){
            strcpy(userCart->cartOwner, currentUser->userName);
            strcpy(userCart->productName, targetProduct->productName);
            userCart->singlePriceProduct = targetProduct->productPrice;
            userCart->timeStamp = time(NULL);
            

            int quantity = 0;
            while (quantity == 0){
                printf("Please Enter How Many Do You Want To Add In Cart\t:\t");
                scanf("%d",&quantity);
            }
            
            int totalCost;
            totalCost = userCart->singlePriceProduct * quantity;
            userCart->totalCost = totalCost;
            userCart->totalInCart = quantity;

            printf("\n========== Product Detail ==========\n");
            printf("\tCartOwner             :\t%s\n",userCart->cartOwner);
            printf("\tProductName           :\t%s\n",userCart->productName);
            printf("\tSinglePriceProduct    :\t%d\n",userCart->singlePriceProduct);
            printf("\tTimeStamps            :\t%s\n",ctime(&userCart->timeStamp));
            printf("\tToTalCost             :\t%d\n",userCart->totalCost);
            printf("\tToTalInCart           :\t%d\n",userCart->totalInCart);


        }

        printf("Do You Want To Continue This Process Or Not\n");
        scanf("%s",&continueOrNot);

    }

}


