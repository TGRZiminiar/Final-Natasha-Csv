#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"

void test(){
    printf("TEST");
}

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
        fp = fopen("Product.dat","a+");
        fwrite(&product, sizeof(Product), 1, fp);
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

    fp = fopen("Product.dat","r");
    printf("\n ****Product Information****\n");
    int i = 1;
    while (fread(&product, sizeof(Product), 1, fp)){
        printf("----------- Product Number : %d -------------\n\n",i);
        printf("\tProduct Name              :\t%s\n", product.productName);
        printf("\tProduct Price             :\t%d\n", product.productPrice);
        printf("\tProduct Quantity          :\t%d\n", product.productQuantity);
        printf("\tProduct minimumQuantity   :\t%d\n", product.minimumQuantity);
        printf("\n\n");
        i++;
    }
    fclose(fp);    
}

void EditProductInDB(){
    Product product;
    Product updateProduct;
    FILE *fp, *fp1;

    char targetProduct[50];
    PrintProduct();
    printf("Enter Product Name That You Want To Edit\t:\t");
    fgets(targetProduct, 50, stdin);
    targetProduct[strlen(targetProduct)-1] = 0;

    fp = fopen("Product.dat","a+");
    fp1 = fopen("tempProduct.dat","w");

    char temp[50];
    int found = 0;
    
    while (fread(&product, sizeof(Product), 1, fp)){
        printf("THIS IS PRODUCT NAME %s\n",product.productName);
        if(strcmp(targetProduct, product.productName) == 0){
            
            found = 1;

            printf("\nEnter Product Name:\t");
            fgets(temp, 50,stdin);
            temp[strlen(temp)-1] = 0;
            strcpy(updateProduct.productName, temp);

            printf("\nEnter Product Price:\t");
            scanf("%d",&updateProduct.productPrice);

            printf("\nEnter Product Quantity:\t");
            scanf("%d",&updateProduct.productQuantity);

            printf("\nEnter Product Minimum Quantity:\t");
            scanf("%d",&updateProduct.minimumQuantity);

        }
        fwrite(&updateProduct, sizeof(Product), 1, fp1);
    }

    fclose(fp);
    fclose(fp1);
    if(found == 1){
        fp1 = fopen("tempProduct.dat","r");
        fp = fopen("Product.dat","w");

        while (fread(&updateProduct, sizeof(Product), 1, fp1)){
            fwrite(&updateProduct, sizeof(Product), 1, fp);
        }
        
        fclose(fp);
        fclose(fp1);
        printf("Update Product Success\n");

    }
    else {
        printf("Data Not Found\n");
    }

}


void RemoveProduct(){

    Product product;
    FILE *fp, *fp1;

    char targetProduct[50];

    fp = fopen("Product.dat","a+");
    fp1 = fopen("tempProduct.dat","w");

    PrintProduct();
    printf("Enter Product Name That You Want To Delete\t:\t");
    fgets(targetProduct, 50, stdin);
    targetProduct[strlen(targetProduct) - 1] = 0;
    int found = 0;

    while (fread(&product, sizeof(Product), 1, fp)){
        if(strcmp(targetProduct, product.productName) == 0){
            found = 1;
        }
        else {
            fwrite(&product, sizeof(Product), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);
     
    if(found == 1){
        fp1 = fopen("tempProduct.dat","r");
        fp = fopen("Product.dat","w");
        while (fread(&product, sizeof(Product), 1, fp1)){
            fwrite(&product, sizeof(Product),1 ,fp);
        }
        printf("Remove Product Success\n");
        fclose(fp1);
        fclose(fp);
    }
    else {
        printf("Item Not Found\n");
    }

}


