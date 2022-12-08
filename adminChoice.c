/* 
1. หน้าให้แอดมินเลือกว่าจะทำเกี่ยวกับ user หรือ product = AdminSelection
2. ปริ้นสิ่งที่ ADMIN สามารถทำกับ USER ได้ = CommandUser
3. ปริ้นสิ่งที่ ADMIN ทำกับ PRODUCT ได้ = CommandProduct
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.route.h"
#include "user.route.h"

void AdminSelection(User *currentUser){
    int choice;
    printf("\n\nHey Admin! What you want to do here");
    printf("\n(1) See All Command User");
    printf("\n(2) See All Command Product");
    printf("\n(3) Go To User Selection");
    printf("\n(4) Exist");
    printf("\n\nYour choice\t:\t");
    scanf("%d",&choice);


    switch (choice){
    case 1:
        CommandUser(currentUser);
        break;
    case 2:
        CommandProduct();
        break;

    case 3:
        UserSelection(currentUser);
        break;

    case 4:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        AdminSelection(currentUser);
        break;
    }

}

void CommandUser(User *currentUser){

    int choice;
    printf("\n\nHey Admin! What you want to do for user?");
    printf("\n(1) Number User");
    printf("\n(2) PrintDb User");
    printf("\n(3) Edit User");
    printf("\n(4) Remove User");
    printf("\n(5) Back To Admin Dashboard");
    printf("\n(6) Exist");
    printf("\n\nYour choice\t:\t");
    scanf("%d",&choice);


    switch (choice){
    case 1:
        printf("Number Of User %d\n",NumberOfUser());
        break;

    case 2:
        PrintUserData();
        break;

    case 3:
        EditUser();
        break;

    case 4:
        RemoveUser();
        break;

    case 5:
        AdminSelection(currentUser);
        break;

    case 6:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        CommandUser(currentUser);
        break;
    }
}

void CommandProduct(){
    
    int choice;
    printf("\n\nHey Admin! What you want to do for user?");
    printf("\n(1) Print Product");
    printf("\n(2) Add Product");
    printf("\n(3) Edit Product");
    printf("\n(4) Remove Product");
    printf("\n(5) Exit");
    printf("\n\nYour choice\t:\t");
    scanf("%d",&choice);


    switch (choice){
    case 1:
        PrintProduct();
        break;

    case 2:
        AddProduct();
        break;

    case 3:
        EditProductInDB();
        break;

    case 4:
        RemoveProduct();
        break;

    case 5:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        CommandProduct();
        break;
    }
}