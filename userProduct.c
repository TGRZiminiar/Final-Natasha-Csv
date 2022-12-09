/* 
ไฟล์ที่เกี่ยวกับให้พวกตะกร้าสินค้าของ user ทุกอย่างที่ user ต้องเกี่ยวข้องกับสินค้าจะรวมไว้ที่นี้
1. Print Product ทั้งหมดที่มีให้ user ดู = PrintProductForUser
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user.route.h"
#include "admin.route.h"

void AddSaveProductCard(UserCart *userCart, User *currentUser, Product *targetProduct);
void PrintUserCartSpecifig(char *target, UserCart itemsInCart[], int *itemsCount, int *sumPrice);
void CheckBillSelection(User *currentUser);
void EditItemInCart(User *currentUser);
void RemoveItemInCart(User *currentUser);

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
    fp = fopen("database/Product.csv","r");

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

    
    // FILE *fpOpenProduct;
    Product *targetProduct;
    targetProduct = calloc(1, sizeof(Product));

    UserCart *userCart;
    userCart = calloc(1, sizeof(UserCart));

    char continueOrNot = 'y';
    int productKey;
    while (continueOrNot == 'y'){

        printf("Add Product To Your Cart\n");
        PrintProductForUser();
        
        printf("Enter Product Key To Add Product To Cart :\t");
        scanf("%d",&productKey);
        
        FindProductByProductKey(&productKey, targetProduct);
        printf("TARGET PRODUCT %s\n",targetProduct->productName);
        
        if(productKey == 0){
            
            AddSaveProductCard(userCart, currentUser, targetProduct);
            printf("Do You Want To Continue This Process? [y/n]:\t");
            scanf("%s",&continueOrNot);

        }

        printf("Do You Want To Continue This Process Or Not (y):(n)\n");
        scanf("%s",&continueOrNot);

    }

}



void AddSaveProductCard(UserCart *userCart, User *currentUser, Product *targetProduct){
    
    FILE *fp;
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
    printf("\tTimeStamps            :\t%s",ctime(&userCart->timeStamp));
    printf("\tToTalInCart           :\t%d\n",userCart->totalInCart);
    printf("\tToTalCost             :\t%d\n",userCart->totalCost);
    printf("\nConfirm To Add This Product? [y/n]:\t");
    
    char saveProductToCart;
    scanf("%s",&saveProductToCart);

    if(saveProductToCart == 'y'){

        fp = fopen("database/UserCart.csv","a+");

        if(fp == NULL){
            printf("Error Opening UserCart.csv\n");
            return;
        }

        printf("Time in string %s",ctime(&userCart->timeStamp));
        printf("Time in millisecond %d",userCart->timeStamp);
        fprintf(fp,
            "%s,%s,%d,%d,%d,%d\n",
            userCart->cartOwner,
            userCart->productName,
            userCart->singlePriceProduct,
            // strtok(ctime(&userCart->timeStamp),"\n"),
            userCart->totalInCart,
            userCart->totalCost,
            userCart->timeStamp
        );
        
        if(fwrite != 0){
            printf("\nSuccessfully saved");
        }
        else{
            printf("\nError saving");
        } 

        fclose(fp);

    }
}

void PrintUserCart(){

    FILE *fp;
    UserCart userCart;

    fp = fopen("database/UserCart.csv","r");
    printf("\n =========   USER CART  ========== \n");

    char line[1000];
    char *sp;
    int i = 1;


    while (fgets(line, 1000, fp) != NULL){
        printf("--------------- Item In Cart  :  %d ----------------\n\n",i);

        sp = strtok(line, ",");
        strcpy(userCart.cartOwner, sp);
        printf("\tCart Owner                  :\t%s\n", userCart.cartOwner);

        sp = strtok(NULL, ",");
        strcpy(userCart.productName, sp);
        printf("\tProduct Name                :\t%s\n", userCart.productName);
       
        sp = strtok(NULL, ",");
        userCart.singlePriceProduct = atoi(sp);
        printf("\tSingle Price Product        :\t%d\n", userCart.singlePriceProduct);
        

        sp = strtok(NULL, ",");
        userCart.totalInCart = atoi(sp);
        printf("\tTotal In Cart               :\t%d\n", userCart.totalInCart);

        sp = strtok(NULL, ",");
        userCart.totalCost = atoi(sp);
        printf("\tTotal Cost                  :\t%d\n", userCart.totalCost);
      
        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);

        userCart.timeStamp = (time_t) tempTime;
        printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&userCart.timeStamp),"\n"));
        // strptime(sp, "%s", &userCart.timeStamp);
      
        printf("\n\n");
      
        i++;

    }

    fclose(fp);
    

}





void CheckBill(User *currentUser){

    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);

    PrintUserCartSpecifig(target, userCart, &itemsCount, &sumPrice);

    CheckBillSelection(currentUser);



}


void PrintUserCartSpecifig(char *target, UserCart itemsInCart[], int *itemsCount, int *sumPrice){

    FILE *fp;
    // UserCart userCart;

    fp = fopen("database/UserCart.csv","r");
    // printf("\n =========   USER CART  ========== \n");

    char line[1000];
    char *sp;
    int i = 1;


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        
        if(strcmp(sp, target) == 0){

            printf("--------------- Number of Items In Your Cart  :  %d ----------------\n\n",*itemsCount+1);

            strcpy(itemsInCart[*itemsCount].cartOwner, sp);
            printf("\tCart Owner                  :\t%s\n", itemsInCart[*itemsCount].cartOwner);

            sp = strtok(NULL, ",");
            strcpy(itemsInCart[*itemsCount].productName, sp);
            printf("\tProduct Name                :\t%s\n", itemsInCart[*itemsCount].productName);
        
            sp = strtok(NULL, ",");
            itemsInCart[*itemsCount].singlePriceProduct = atoi(sp);
            printf("\tSingle Price Product        :\t%d\n", itemsInCart[*itemsCount].singlePriceProduct);
            

            sp = strtok(NULL, ",");
            itemsInCart[*itemsCount].totalInCart = atoi(sp);
            printf("\tTotal In Cart               :\t%d\n", itemsInCart[*itemsCount].totalInCart);

            sp = strtok(NULL, ",");
            itemsInCart[*itemsCount].totalCost = atoi(sp);
            printf("\tTotal Cost                  :\t%d\n", itemsInCart[*itemsCount].totalCost);
            *sumPrice = *sumPrice + itemsInCart[*itemsCount].totalCost;

            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);

            itemsInCart[*itemsCount].timeStamp = (time_t) tempTime;
            printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&itemsInCart[*itemsCount].timeStamp),"\n"));
            // strptime(sp, "%s", &userCart.timeStamp);
            *itemsCount = *itemsCount + 1;
            printf("\n\n");
        }
      
        i++;

    }

    printf("Total Price In Your Cart :\t%d\n",*sumPrice);

    fclose(fp);
    

}


void CheckBillSelection(User *currentUser){
    
    int choice;

    printf("\n\nWhat you want to do here");
    printf("\n(1) Pay Bill");
    printf("\n(2) Edit Item In Cart");
    printf("\n(3) Remove Item In Cart");
    printf("\n(4) Exist");
    printf("\n\nYour choice\t:\t");
    fflush(stdin);
    scanf("%d",&choice);
    switch (choice){
    case 1:
        // PrintProductForUser();
        break;

    case 2:
        EditItemInCart(currentUser);
        break;

    case 3:
        RemoveItemInCart(currentUser);
        break;

    case 4:
        // CheckBill(currentUser);
        break;
    
    case 5:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        CheckBillSelection(currentUser);
        break;
    }
}

void EditItemInCart(User *currentUser){
    
    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);
    PrintUserCartSpecifig(target, userCart, &itemsCount, &sumPrice);
    
    
    UserCart tempCart;
    FILE *fp, *fpTemp;

    char line[1000];

    int targetLine;
    fflush(stdin);
    printf("Enter Number Of Item That You Want To Edit :\t");

    if(scanf("%d",&targetLine) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        EditItemInCart(currentUser);
    }

    fp = fopen("database/UserCart.csv","r");
    fpTemp = fopen("database/TempUserCart.csv","w");
    char *sp;
    UserCart updateCart;
    int i = 0;
    int found = 0;

    while (fgets(line, 1000, fp) != NULL){
        

        sp = strtok(line, ",");
        strcpy(updateCart.cartOwner, sp);
        if(strcmp(updateCart.cartOwner, currentUser->userName) == 0) i++;

        sp = strtok(NULL, ",");
        strcpy(updateCart.productName, sp);

        sp = strtok(NULL, ",");
        updateCart.singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        updateCart.totalInCart = atoi(sp);

        sp = strtok(NULL, ",");
        updateCart.totalCost = atoi(sp);

        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        updateCart.timeStamp = (time_t) tempTime;

        if(targetLine == i && strcmp(updateCart.cartOwner, currentUser->userName) == 0){

            found = 1;

            printf("Current Total In Cart Is %d: Please Enter New Value :\t", updateCart.totalInCart);
            scanf("%d", &updateCart.totalInCart);

            updateCart.totalCost = updateCart.singlePriceProduct * updateCart.totalInCart;

            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                updateCart.cartOwner,
                updateCart.productName,
                updateCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                updateCart.totalInCart,
                updateCart.totalCost,
                updateCart.timeStamp
            );

            if(fwrite != 0){
                // printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 

        }     
        else {
            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                updateCart.cartOwner,
                updateCart.productName,
                updateCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                updateCart.totalInCart,
                updateCart.totalCost,
                updateCart.timeStamp
            );

            if(fwrite != 0){
                // printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 
        }   

    }
        
    fclose(fp);
    fclose(fpTemp);

    if(found == 1){
        
        fp = fopen("database/UserCart.csv", "w");
        fpTemp = fopen("database/TempUserCart.csv", "r");

        while (fgets(line, 1000, fpTemp) != NULL){

            sp = strtok(line, ",");

            strcpy(tempCart.cartOwner, sp);
            // printf("\tCart Owner                  :\t%s\n", tempCart.cartOwner);

            sp = strtok(NULL, ",");
            strcpy(tempCart.productName, sp);
            // printf("\tProduct Name                :\t%s\n", tempCart.productName);
        
            sp = strtok(NULL, ",");
            tempCart.singlePriceProduct = atoi(sp);
            // printf("\tSingle Price Product        :\t%d\n", tempCart.singlePriceProduct);
            

            sp = strtok(NULL, ",");
            tempCart.totalInCart = atoi(sp);
            // printf("\tTotal In Cart               :\t%d\n", tempCart.totalInCart);

            sp = strtok(NULL, ",");
            tempCart.totalCost = atoi(sp);
            // printf("\tTotal Cost                  :\t%d\n", tempCart.totalCost);

            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);

            tempCart.timeStamp = (time_t) tempTime;
            // printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&tempCart.timeStamp),"\n"));
            // strptime(sp, "%s", &userCart.timeStamp);

            fprintf(fp,
                "%s,%s,%d,%d,%d,%d\n",
                tempCart.cartOwner,
                tempCart.productName,
                tempCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                tempCart.totalInCart,
                tempCart.totalCost,
                tempCart.timeStamp
            );

        }

        fclose(fp);
        fclose(fpTemp);
        printf("Successfully saved\n");
    }

    else {
        printf("DATA NOT FOUND\n");
    }


}

void RemoveItemInCart(User *currentUser){

 

    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);
    PrintUserCartSpecifig(target, userCart, &itemsCount, &sumPrice);
   
    

    return;

}