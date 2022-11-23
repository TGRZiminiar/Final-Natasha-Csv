#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.route.h"
#include <stdbool.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

void AddProduct(){
    
    Product product;

    FILE *fp;
    system("cls");
    printf("\n========= Add Product To Store =========");

    printf("\nEnter Product Name:\t");
    // fgets(product.productName, 50, stdin);
    // product.productName[strlen(product.productName)-1] = 0;
    char temp[50];
    fgets(temp, 50,stdin);
    temp[strlen(temp)-1] = 0;
    strcpy(product.productName, temp);

    printf("\nEnter Product Quantity:\t");
    scanf("%d",&product.productQuantity);
    
    printf("\nEnter Product Price:\t");
    scanf("%d",&product.productPrice);

    printf("\nEnter Product Minimum Quantity:\t");
    scanf("%d",&product.minimumQuantity);

    printf("\n\t------------- Product Detail ---------------\n\n");
    printf("\tProduct Name              :\t%s\n", product.productName);
    printf("\tProduct Price             :\t%d\n", product.productPrice);
    printf("\tProduct Quantity          :\t%d\n", product.productQuantity);
    printf("\tProduct minimumQuantity   :\t%d\n", product.minimumQuantity);
    printf("\n\n");
    printf("\nConfirm To Add This Product? [y/n]:\t");
    char saveProduct;
    scanf("%s",&saveProduct);
    printf("THIS IS PRODUCT NAME %s\n",product.productName);

    if(saveProduct == 'y'){
        fp = fopen("database/Product.csv","a+");
        fprintf(fp,
            "%s,%d,%d,%d\n",
            product.productName,
            product.productPrice,
            product.productQuantity,
            product.minimumQuantity
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

void PrintProduct(){
    Product product;
    FILE *fp;

    fp = fopen("database/Product.csv","r");
    printf("\n ****Product Information****\n");
    int i = 1;
    char line[1000];
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
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
        // printf("SP => %s\n",sp);
        printf("\tProduct Quantity              :\t%d\n", product.productQuantity);

        sp = strtok(NULL, ",");
        product.minimumQuantity = atoi(sp);
        // printf("SP => %s\n",sp);
        printf("\tProduct minimumQuantity       :\t%d\n", product.minimumQuantity);


        // sp = strtok(NULL, ",");
        // product.productPrice = atoi(strtok(NULL, sp));
        // // printf("\tProduct Price             :\t%d\n", product.productPrice);
        // printf("\tProduct Price             :\t%d\n", atoi(strtok(NULL, sp)));
        
        // sp = strtok(NULL, ",");
        // product.productQuantity = atoi(strtok(NULL, sp));
        // printf("\tProduct Quantity          :\t%d\n", product.productQuantity);

        // sp = strtok(NULL, ",");
        // product.minimumQuantity = atoi(strtok(NULL, sp));
        // printf("\tProduct minimumQuantity   :\t%d\n", product.minimumQuantity);

        printf("----------- Product Number : %d -------------\n\n",i);
        printf("\n\n");
        i++;
    }

    fclose(fp);    
}

void EditProductInDB(){
    Product tempProduct;
    Product updateProduct;
    FILE *fp, *fpTemp;


    char targetProduct[50];
    char line[1000];
    int found = 0;
    
    PrintProduct();
    printf("Enter Product Name That You Want To Edit\t:\t");
    fgets(targetProduct, 50, stdin);
    targetProduct[strlen(targetProduct)-1] = 0;

    fp = fopen("database/Product.csv","r");
    fpTemp = fopen("database/TempProduct.csv","w");
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        sscanf(line, "%s", &updateProduct.productName);

        sp = strtok(line, ",");
        strcpy(updateProduct.productName, sp);
        
        sp = strtok(NULL, ",");
        updateProduct.productPrice = atoi(sp);

        sp = strtok(NULL, ",");
        updateProduct.productQuantity = atoi(sp);

        sp = strtok(NULL, ",");
        updateProduct.minimumQuantity = atoi(sp);

        if(strcmp(targetProduct, updateProduct.productName) == 0){

            found = 1;

            printf("Current Product Name For Product is %s: Please Enter New Value", updateProduct.productName);
            fgets(updateProduct.productName ,50,stdin);
            updateProduct.productName[strlen(updateProduct.productName)-1] = 0;

            printf("Current Product Price For Product is %d: Please Enter New Value", updateProduct.productPrice);
            scanf("%d", &updateProduct.productPrice);
            
            printf("Current Product Quantity For Product is %d: Please Enter New Value", updateProduct.productQuantity);
            scanf("%d", &updateProduct.productQuantity);

            printf("Current Product Minimum Quantity For Product is %d: Please Enter New Value", updateProduct.minimumQuantity);
            scanf("%d", &updateProduct.minimumQuantity);

            fprintf(fpTemp,
            "%s,%d,%d,%d\n",
            updateProduct.productName,
            updateProduct.productPrice,
            updateProduct.productQuantity,
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
            "%s,%d,%d,%d\n",
            updateProduct.productName,
            updateProduct.productPrice,
            updateProduct.productQuantity,
            updateProduct.minimumQuantity
            );

            if(fwrite != 0){
                printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 

        }
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
            tempProduct.minimumQuantity = atoi(sp);

         
            fprintf(fp,
            "%s,%d,%d,%d\n",
            tempProduct.productName,
            tempProduct.productPrice,
            tempProduct.productQuantity,
            tempProduct.minimumQuantity
            );
        }
        fclose(fp);
        fclose(fpTemp);        

    }
    else {
        printf("DATA NOT FOUND\n");
    }

    // fp = fopen("Product.dat","a+");
    // fp1 = fopen("tempProduct.dat","w");

    // char temp[50];
    // int found = 0;
    
    // while (fread(&product, sizeof(Product), 1, fp)){
    //     printf("THIS IS PRODUCT NAME %s\n",product.productName);
    //     if(strcmp(targetProduct, product.productName) == 0){
            
    //         found = 1;

    //         printf("\nEnter Product Name:\t");
    //         fgets(temp, 50,stdin);
    //         temp[strlen(temp)-1] = 0;
    //         strcpy(updateProduct.productName, temp);

    //         printf("\nEnter Product Price:\t");
    //         scanf("%d",&updateProduct.productPrice);

    //         printf("\nEnter Product Quantity:\t");
    //         scanf("%d",&updateProduct.productQuantity);

    //         printf("\nEnter Product Minimum Quantity:\t");
    //         scanf("%d",&updateProduct.minimumQuantity);

    //     }
    //     fwrite(&updateProduct, sizeof(Product), 1, fp1);
    // }

    // fclose(fp);
    // fclose(fp1);
    // if(found == 1){
    //     fp1 = fopen("tempProduct.dat","r");
    //     fp = fopen("Product.dat","w");

    //     while (fread(&updateProduct, sizeof(Product), 1, fp1)){
    //         fwrite(&updateProduct, sizeof(Product), 1, fp);
    //     }
        
    //     fclose(fp);
    //     fclose(fp1);
    //     printf("Update Product Success\n");

    // }
    // else {
    //     printf("Data Not Found\n");
    // }

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


