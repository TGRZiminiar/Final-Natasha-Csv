/* 
1. ฟังก์ชัน PRINT Product ทั้งหมดที่มี = PrintProduct
2. ฟังก์ชั่นเพิ่มสินค้า = AddProduct
3. ฟังก์ชัน EDIT สินค้า = EditProductInDB
4. ฟังก์ชันลบสินค้า = RemoveProduct
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.route.h"
#include <stdbool.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

void saveUpdateProduct(char *line, char *sp, int *found, Product tempProduct, FILE *fpTemp, char *targetProduct);

void PrintProduct(){
    Product product;
    FILE *fp;
    
    fp = fopen("database/Product.csv","r");
    printf("\n ****Product Information****\n");
    int i = 1;
    char line[1000];
    char *sp;

    while (fgets(line, 1000, fp) != NULL){

        printf("----------- Product Number : %d -------------\n\n",i);
        // printf("\n%s\n",line);
        sp = strtok(line, ",");
        strcpy(product.productName, sp);
        printf("\tProduct Name                  :\t%s\n", product.productName);
        
        sp = strtok(NULL, ",");
        product.productPrice = atoi(sp);
        // printf("SP => %s\n",sp);
        printf("\tProduct Price                 :\t%d\n", product.productPrice);

        sp = strtok(NULL, ",");
        product.productQuantity = atoi(sp);
        printf("\tProduct Quantity              :\t%d\n", product.productQuantity);
        
        sp = strtok(NULL, ",");
        product.productCost = atoi(sp);
        printf("\tProduct Quantity              :\t%d\n", product.productCost);
      
        sp = strtok(NULL, ",");
        product.productProfit = atoi(sp);
        printf("\tProduct Quantity              :\t%d\n", product.productProfit);


        sp = strtok(NULL, ",");
        product.minimumQuantity = atoi(sp);
        printf("\tProduct minimumQuantity       :\t%d\n", product.minimumQuantity);

        
        printf("\n\n");
        i++;
    }

    fclose(fp);    
}


void AddProduct(){
    
    Product product;
    FILE *fp;
    char temp[50];

    system("cls");
    printf("\n========= Add Product To Store =========\n");
    printf("Enter Product Name:\t");

    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strlen(temp)-1] = '\0';
    strcpy(product.productName, temp);

    printf("\nEnter Product Quantity:\t");
    if(scanf("%d",&product.productQuantity) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        AddProduct();
        return;
    }
            
    
    printf("\nEnter Product Price:\t");
    if(scanf("%d",&product.productPrice) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        AddProduct();
        return;
    }
  
    printf("\nEnter Product Cost:\t");
    if(scanf("%d",&product.productCost) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        AddProduct();
        return;
    }

    printf("\nEnter Product Profit:\t");
    if(scanf("%d",&product.productProfit) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        AddProduct();
        return;
    }

    printf("\nEnter Product Minimum Quantity:\t");
     if(scanf("%d",&product.minimumQuantity) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        AddProduct();
        return;
    }

    printf("\n\t------------- Product Detail ---------------\n\n");
    printf("\tProduct Name              :\t%s\n", product.productName);
    printf("\tProduct Price             :\t%d\n", product.productPrice);
    printf("\tProduct Quantity          :\t%d\n", product.productQuantity);
    printf("\tProduct Cost              :\t%d\n", product.productCost);
    printf("\tProduct Profit            :\t%d\n", product.productProfit);
    printf("\tProduct minimumQuantity   :\t%d\n", product.minimumQuantity);
    printf("\n\n");
    printf("\nConfirm To Add This Product? [y/n]:\t");
    char saveProduct;
    scanf("%s",&saveProduct);
    // printf("THIS IS PRODUCT NAME %s\n",product.productName);

    if(saveProduct == 'y'){
        fp = fopen("database/Product.csv","a+");
        fprintf(fp,
            "%s,%d,%d,%d,%d,%d\n",
            product.productName,
            product.productPrice,
            product.productQuantity,
            product.productCost,
            product.productProfit,
            product.minimumQuantity
        );
        if(fwrite != 0){
            printf("\nSuccessfully saved\n");
        }
        else{
            printf("\nError saving");
        } 
        fclose(fp);
    }
}



void EditProductInDB(){
    Product tempProduct;
    FILE *fp, *fpTemp;


    char line[1000];
    int found = 0;
    
    PrintProduct();

    printf("Enter Product Key That You Want To Edit\t:\t");
    char targetProduct[50];
    int targetLine;

    fflush(stdin);
    if(scanf("%d",&targetLine) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        EditProductInDB();
    }
    
    // fgets(targetProduct, 50, stdin); 
    // targetProduct[strlen(targetProduct)-1] = 0;

    // printf("THIS IS TARGET PRODUCT %s\n",targetProduct);
    

    fp = fopen("database/Product.csv","r");
    fpTemp = fopen("database/TempProduct.csv","w");
    char *sp;
    
    Product updateProduct;
    int i = 1;

    while (fgets(line, 1000, fp) != NULL){

        // sscanf(line, "%s", &updateProduct.productName); 

        sp = strtok(line, ",");
        strcpy(updateProduct.productName, sp);
        
        sp = strtok(NULL, ",");
        updateProduct.productPrice = atoi(sp);

        sp = strtok(NULL, ",");
        updateProduct.productQuantity = atoi(sp);
       
        sp = strtok(NULL, ",");
        updateProduct.productCost = atoi(sp);

        sp = strtok(NULL, ",");
        updateProduct.productProfit = atoi(sp);

        sp = strtok(NULL, ",");
        updateProduct.minimumQuantity = atoi(sp);

        if(targetLine == i){

            found = 1;
            fflush(stdin);
            printf("Current Product Name For Product is %s: Please Enter New Value :\t", updateProduct.productName);
            fgets(updateProduct.productName ,50,stdin);
            updateProduct.productName[strlen(updateProduct.productName)-1] = 0;

            printf("Current Product Price For Product is %d: Please Enter New Value :\t", updateProduct.productPrice);
            if(scanf("%d",&updateProduct.productPrice) != 1) {
                system("clear");
                printf("Please Enter Correct Type\n");
                EditProductInDB();
                return;
            }
            
            printf("Current Product Quantity For Product is %d: Please Enter New Value :\t", updateProduct.productQuantity);
            if(scanf("%d",&updateProduct.productQuantity) != 1) {
                system("clear");
                printf("Please Enter Correct Type\n");
                EditProductInDB();
                return;
            }
            
            printf("Current Product Cost For Product is %d: Please Enter New Value :\t", updateProduct.productCost);
            if(scanf("%d",&updateProduct.productCost) != 1) {
                system("clear");
                printf("Please Enter Correct Type\n");
                EditProductInDB();
                return;
            }
            
            printf("Current Product Profit For Product is %d: Please Enter New Value :\t", updateProduct.productProfit);
            if(scanf("%d",&updateProduct.productProfit) != 1) {
                system("clear");
                printf("Please Enter Correct Type\n");
                EditProductInDB();
                return;
            }

            printf("Current Product Minimum Quantity For Product is %d: Please Enter New Value :\t", updateProduct.minimumQuantity);
            if(scanf("%d",&updateProduct.minimumQuantity) != 1) {
                system("clear");
                printf("Please Enter Correct Type\n");
                EditProductInDB();
                return;
            }

            fprintf(fpTemp,
                "%s,%d,%d,%d,%d,%d\n",
                updateProduct.productName,
                updateProduct.productPrice,
                updateProduct.productQuantity,
                updateProduct.productCost,
                updateProduct.productProfit,
                updateProduct.minimumQuantity
            );
            
            if(fwrite != 0){
                printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 
            
        }

        else {

            fprintf(fpTemp,
                "%s,%d,%d,%d,%d,%d\n",
                updateProduct.productName,
                updateProduct.productPrice,
                updateProduct.productQuantity,
                updateProduct.productCost,
                updateProduct.productProfit,
                updateProduct.minimumQuantity
            );

            if(fwrite != 0){
                printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 
        }
        i++;
    }
    
    fclose(fp);
    fclose(fpTemp);

    if(found == 1){
        fp = fopen("database/Product.csv","w");
        fpTemp = fopen("database/TempProduct.csv","r");

        while (fgets(line, 1000, fpTemp) != NULL){

            // sscanf(line, "%s", &tempProduct.productName);

            sp = strtok(line, ",");
            strcpy(tempProduct.productName, sp);
            
            sp = strtok(NULL, ",");
            tempProduct.productPrice = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.productQuantity = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.productCost = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.productProfit = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.minimumQuantity = atoi(sp);

         
            fprintf(fp,
            "%s,%d,%d,%d,%d,%d\n",
                tempProduct.productName,
                tempProduct.productPrice,
                tempProduct.productQuantity,
                tempProduct.productCost,
                tempProduct.productProfit,
                tempProduct.minimumQuantity
            );
        }
        fclose(fp);
        fclose(fpTemp);        

    }
    else {
        printf("DATA NOT FOUND\n");
    }

}


void RemoveProduct(){

    Product product;
    FILE *fp, *fpTemp;

    char targetProduct[50];
    
    char fileName[FILENAME_SIZE] = "database/Product.csv";
    char tempFileName[FILENAME_SIZE];
    char buffer[MAX_LINE];
    int deleteLine = 0;

    PrintProduct();
    strcpy(tempFileName, "temp____");
    strcat(tempFileName, fileName);

    printf("Delete Line: ");
    scanf("%d",&deleteLine);

    if(scanf("%d",&deleteLine) != 1) {
        system("clear");
        printf("Please Enter Correct Type\n");
        RemoveProduct();
    }


    fp = fopen(fileName,"r");
    fpTemp = fopen(tempFileName,"w");

    if(fp == NULL || fpTemp == NULL){
        printf("FILE FORMAT ERROR\n");
        return;
    }

    bool keepReading = true;
    int currentLine = 1;

 
    do{
        
        fgets(buffer, 1024, fp);
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
    printf("Remove Product Success\n");
    return;
}


void saveUpdateProduct(char *line, char *sp, int *found, Product tempProduct, FILE *fpTemp, char *targetProduct){
    
   
}
