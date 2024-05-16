#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct Foodie_Manager_Food
{
    char food_name[50];
    int quantity;
    float price;
    int food_id;
    struct Foodie_Manager *next;
} food;

typedef struct Foodie_Manager_Customer
{
    char customer_name[50];
    char customer_phone_number[20];
    float item_price;
    int c_food_id;
    int ordered_food_quantity;
    char ordered_food_name[50];
    struct Foodie_Manager_Customer *link;
} customer;

void help()
{
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t      HELP SECTION\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\n\tWelcome to the Help Section of Foodie Manager!\n");
    printf("\n\tHere are the functionalities you can perform:\n");
    printf("\n\t1.Customer Section: This section allows customers to place orders and view the menu.\n");
    printf("\n\t2.Manager Section: In this section, managers can access manager-specific functions such as viewing manager lists.\n");
    printf("\n\t3.Admin Section: The admin section provides access to admin-specific functions such as managing customer\n\tlists and sales.\n");
    printf("\n\t4.Help: You are currently in the Help Section. Here, you can get help information about each functionality.\n");
    printf("\n\t5.Exit: Choose this option to exit the program.\n");
    printf("\n\tFeel free to explore the different sections of the program!\n");
    printf("\n\n\t\tPress Any Key To Continue. . .");
    getch();
    system("cls");
}

void manager_login_panel_registration(food *ptr,customer *ptr_c)
{
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\tManager New Registration\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    FILE *file_login = fopen("manager_login_panel.txt", "a+");
    char name[30], phone_number[30], manager_id[20], username[20], password[10];
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your Name : ");
    scanf("%[^\n]s", name);
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your Phone Number : ");
    scanf("%[^\n]s", phone_number);
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your Manager ID : ");
    scanf("%[^\n]s", manager_id);
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your User-name : ");
    scanf("%[^\n]s", username);
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your Four Digits Password : ");
    scanf("%[^\n]s", password);
    fprintf(file_login, "%s %s %s %s %s\n", name, phone_number, manager_id, username, password);
    fclose(file_login);
    printf("\n\n\t\t\t\t\tRegistration Successful!!");
    printf("\n\n\t\t\t\tPress Any Key To Continue. . .");
    getch();
    manager_section(ptr,ptr_c);
}
void manager_login_panel_login(food *ptr,customer *ptr_c)
{
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t    Manager Login\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    FILE *file_login = fopen("manager_login_panel.txt", "r");
    char name[30], phone_number[30], manager_id[20], username[20], password[10], test_username[30], test_password[10];
    int flag = 0;
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your User-name : ");
    scanf(" %s", test_username);
    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Your Four Digits Password : ");
    scanf(" %s", test_password);

    while (fscanf(file_login, "%s %s %s %s %s\n", username, phone_number, manager_id, username, password) != EOF)
    {
        if (strcmp(username, test_username) == 0 && strcmp(password, test_password) == 0)
        {
            flag = 1;
            manager_menu(ptr,ptr_c);
        }
    }
    if (flag == 0)
    {
        printf("\n\t\t\t\t\tUser-name And Password Are Not Match\n");
        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        system("cls");
    }
    fclose(file_login);
}


void delete_food_item_from_display_menu(food *ptr)
{
    food *temp,*temp1;
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t   Delete Item Form Menu\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    int test_f_id, flag = 0;
    char f_name_c[30];
    printf("\n\t\t\t\tEnter Food ID You Want To Delete : ");
    scanf("%d", &test_f_id);

    if (ptr->next == NULL)
    {
        printf("\n\t\t\tList Is Empty\n");
    }

    else
    {
        while (ptr->next != NULL)
        {
            temp1=ptr->next;
            if (temp1->food_id == test_f_id)
            {
                printf("\n\t\t\t\tFood Name : %s", temp1->food_name);
                strcpy(f_name_c, temp1->food_name);
                flag = 1;
                temp = ptr->next;
                ptr->next = temp->next;
                free(temp);
                printf("\n\t\t\t\t%d(%s) Is Removed From Your Order List\n", test_f_id, f_name_c);
                break;
            }
            ptr = ptr->next;
        }

        if (flag==0)
        {
            printf("\n\t\t\t\tFood Item with ID %d not found in the menu.\n", test_f_id);
        }
    }
}

void manager_menu(food *ptr,customer *ptr_c)
{
    system("cls");
    food *temp=ptr;
    food *temp1=ptr;
    customer *temp_c=ptr_c;
    int count = 0;
    while (ptr->next != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t    Manager Section\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t   |   1.Display Menu   |    |    2.Total Sales   |    |    3.Add New Items   |");
    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t   |   4.Delete Item    |    |   5.Ordered Items  |    |        6.Back        |");
    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\n\t\t\t\t\tEnter Your Choice. . .");

    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    {
        display_menu(temp);
        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    case 2:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     Display Total Sales\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        char name[50];
        int quantity;;
        float price,total_amount=0;
        FILE *file_t = fopen("Sold_food_Lsit.csv", "r");
        printf("\n\n\t\t\t\tFood Name \tQuantities\tPrice\t\tTotal Price");
        printf("\n\t\t\t\t------------------------------------------------------------\n");
        while (fscanf(file_t, "%49[^,],%d,%f\n", name, &quantity, &price) == 3)
        {
            printf("\t\t\t\t%-15s %-15d %-15.2f %.2f\n", name, quantity, price,quantity*price);
            total_amount+=quantity*price;
        }
        printf("\t\t\t\t------------------------------------------------------------\n");
        fclose(file_t);
        printf("\t\t\t\tTotal Sale :\t\t\t%.2f Taka",total_amount);

        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    case 3:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     Add New Item\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        char new_f_name[50];
        int new_f_quantity;
        float new_f_price;
        printf("\n\t\t\t\tEnter Food Item Name : ");
        fflush(stdin);
        scanf("%[^\n]s", new_f_name);
        printf("\n\t\t\t\tEnter Food Quantity : ");
        scanf("%d",&new_f_quantity);
        printf("\n\t\t\t\tEnter Food Price : ");
        scanf("%f",&new_f_price);

        while (temp1->next != NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = (food *)malloc(sizeof(food));
        temp1 = temp1->next;
        strcpy(temp1->food_name, new_f_name);
        temp1->quantity = new_f_quantity;
        temp1->price = new_f_price;
        temp1->food_id = count+101;
        temp1->next = NULL;
        printf("\n\n\t\t\t\tFood added Successfully!!");
        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        temp1=temp;
        break;
    }
    case 4:
    {
        delete_food_item_from_display_menu(temp);
        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    case 5:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     Display Total Sales\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        float total_amount=0;
        int i=0,flag=0;
        while(ptr_c->link!=NULL)
        {

            ptr_c=ptr_c->link;
            if(i==0)
            {
                system("cls");
                printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
                printf("\t\t\t\t|\t\t     Display Total Sales\t\t|");
                printf("\n\t\t\t\t+-------------------------------------------------------+\n");
                printf("\n\n\t\t\t\tFood ID\t\tFood Name\t  Quantities");
                printf("\n\t\t\t\t--------------------------------------------");
            }
            printf("\n\t\t\t\t%-15d%-18s %-15d",ptr_c->c_food_id,ptr_c->ordered_food_name,ptr_c->ordered_food_quantity);
            flag=1;
            i++;
        }
        if(flag==0)
        {
            printf("\n\n\t\t\t\tEmpty\n");
            printf("\n\n\t\t\tEnter Any Key To Continue...");
            getch();
            return;
        }
        printf("\n\n\t\t\tEnter Any Key To Continue : ");
        getch();
        break;
    }
    case 6:
    {
        main_menu_show(temp1,ptr_c);
        break;
    }
    }
    manager_menu(temp1,ptr_c);
}


void manager_section(food *ptr, customer *ptr_c)
{
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t    Manager Section\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    printf("\n\t\t\t\t          ------------------  \t---------------------  ");
    printf("\n\t\t\t\t          |     1.Login    |  \t|   2.Registration  |");
    printf("\n\t\t\t\t          ------------------  \t---------------------  ");
    printf("\n\t\t\t\t\t\t  ----------------------");
    printf("\n\t\t\t\t\t\t  |      5.Back        |");
    printf("\n\t\t\t\t\t\t  ----------------------\n");;
    int choice;
    printf("\n\t\t\t\t Enter Your Choice. . .");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        manager_login_panel_login(ptr,ptr_c);
        break;
    case 2:
        manager_login_panel_registration(ptr,ptr_c);
        break;
    case 3:
        main_menu_show(ptr,ptr_c);
        break;
    default:
    {
        system("cls");
        printf("\n\n\t\t\t\tWrong Choice...");
        printf("\n\t\t\t\tPres 1 or 3 Only\n");
        printf("\n\n\t\t\tEnter Any Key To Continue : ");
        getch();
    }
    break;
    }
}

void customer_menu()
{
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t    Customer Section\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t   |   1.Display Menu   |    |    2.Place Order   |    | 3.View Ordered Items |");
    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t   |   4.Delete Item    |    |5.Display final bill|    |     6.Cash Counter   |");
    printf("\n\t\t\t   ----------------------    ----------------------    ------------------------");
    printf("\n\t\t\t\t\t\t     ----------------------");
    printf("\n\t\t\t\t\t\t     |      7.Exit        |");
    printf("\n\t\t\t\t\t\t     ----------------------\n");
    printf("\n\n\t\t\t\t Enter Your Choice. . .");

}

void display_menu(food *ptr)
{
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\tDisplaying All Items Of Food   \t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\n\n\t\t\t\tExisting Food Items Are : ");
    printf("\n\n\t\t\tFood ID \tFood Name\t\tPrice\t\tQuantity");
    printf("\n\t\t\t=================================================================");

    int count = 0;
    if (ptr->next == NULL)
    {
        printf("\n\n\n\t\t\tThe List Empty\n");
    }
    while (ptr->next != NULL)
    {
        count++;
        ptr = ptr->next;
        printf("\n\t\t\t%-15d %-23s %-15.2f %d", ptr->food_id, ptr->food_name, ptr->price, ptr->quantity);
    }
    printf("\n\t\t\t-----------------------------------------------------------------\n");
    printf("\t\t\tTotal Food Items Existing Here : %d\n", count);
}


void place_order(food *ptr,customer *ptr_c,char c_name[],char c_phone_number[])
{
    system("cls");
    food *temp=ptr;
    customer *temp_c=ptr_c;
    display_menu(ptr);
    int number, f_id, flag=0;

    printf("\n\t\t\tHow Many Different Food Items You Wanna Order : ");

    float total_price=0;
    int f_quantites;
    scanf("%d", &number);

    for (int i = 0; i < number; i++)
    {
        printf("\n\t\t\t\tEnter The Food's ID : ");
        scanf("%d", &f_id);

        while (ptr->next != NULL)
        {
            ptr = ptr->next;
            if (f_id==ptr->food_id)
            {
                flag = 1;
                printf("\t\t\t\tHow Many Quantities You Wanna Order : ");
                scanf("%d", &f_quantites);

                while(ptr_c->link!=NULL)
                {
                    ptr_c=ptr_c->link;
                }

                ptr_c->link=(customer*)malloc(sizeof(customer));
                ptr_c=ptr_c->link;

                strcpy(ptr_c->customer_name,c_name);
                strcpy(ptr_c->customer_phone_number,c_phone_number);
                ptr_c->item_price=ptr->price;
                strcpy(ptr_c->ordered_food_name,ptr->food_name);
                ptr_c->ordered_food_quantity=f_quantites;
                ptr_c->c_food_id=ptr->food_id;
                ptr_c->link=NULL;
                ptr->quantity=ptr->quantity-f_quantites;  //update quantities in menu
            }

        }
        ptr=temp;
        ptr_c=temp_c;
        if (flag == 0)
        {
            printf("\t\t\t\"%d\" is not present at the list\n", f_id);
            printf("\n\n\t\t\tEnter Any Key To Continue. . .");
            getch();
            break;
        }
    }
    FILE *file_t = fopen("Sold_food_Lsit.csv", "a+");
    while(ptr_c->link!=NULL)
    {
        ptr_c=ptr_c->link;
        if (strcmp(ptr_c->customer_name, c_name) == 0)
        {
            fprintf(file_t,"%s,%d,%.2f\n",ptr_c->ordered_food_name,ptr_c->ordered_food_quantity,ptr_c->item_price);
        }
    }
    fclose(file_t);
    ptr_c=temp_c;
    printf("\n\t\t\t\tThank You For Ordering Food");
    printf("\n\t\t\t\tWait 2 Minutes,We Will Serve Your Food\n");
    printf("\n\n\t\t\tEnter Any Key To Continue. . .");
    getch();
}
void view_order_item(customer *ptr_c,char c_name[],char c_phone_number[])
{
    system("cls");
    int flag=0;
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t  Display Ordered Items\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    float total_amount=0;
    int i=0;
    while(ptr_c->link!=NULL)
    {
        ptr_c=ptr_c->link;
        if (strcmp(ptr_c->customer_name, c_name) == 0)
        {
            if(i==0)
            {
                system("cls");
                printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
                printf("\t\t\t\t|\t\t  Display Ordered Items\t\t\t|");
                printf("\n\t\t\t\t+-------------------------------------------------------+\n");
                printf("\n\n\t\t\t\tName : %s",ptr_c->customer_name);
                printf("\n\t\t\t\tPhone Number : %s\n",ptr_c->customer_phone_number);
                printf("\n\t\t\t\tYou Have Ordered : ");
                printf("\n\t\t\t\t-----------------");
                printf("\n\n\t\t\t\tFood ID\t\tFood Name\t  Quantities");
                printf("\n\t\t\t\t--------------------------------------------");
            }
            printf("\n\t\t\t\t%-15d%-18s %-15d",ptr_c->c_food_id,ptr_c->ordered_food_name,ptr_c->ordered_food_quantity);
            i++;
        }
    }
    printf("\n\t\t\t\t--------------------------------------------");
    printf("\n\n\t\t\tEnter Any Key To Continue : ");
    getch();

}
void delete_order_item(customer *ptr_c,char c_name[],char c_phone_number[])
{
    system("cls");
    customer *temp_c;
    char f_name_c[50];
    int test_f_id,flag=0;
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\tRemove Item Form Ordered List\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\n\t\t\t\tEnter Food ID : ");
    scanf("%d",&test_f_id);
    while(ptr_c->link!=NULL)
    {
        if(ptr_c->link->c_food_id==test_f_id)
        {
            printf("\n\t\t\t\tFood Name : %s(%d)",ptr_c->link->ordered_food_name,ptr_c->link->ordered_food_quantity);
            strcpy(f_name_c,ptr_c->link->ordered_food_name);
            flag=1;
            temp_c=ptr_c->link;
            ptr_c->link=temp_c->link;
            free(temp_c);
            printf("\n\t\t\t\t%d(%s) Is Removed From Your Order List\n",test_f_id,f_name_c);
            break;
        }
        ptr_c=ptr_c->link;
    }
    if(flag==0)
    {
        printf("\n\t\t\t\t%d Food ID Is Not Found In Your Food Order List\n");
    }
    printf("\n\n\t\t\tEnter Any Key To Continue...");
    getch();

}
void display_final_bill(customer *ptr_c,char c_name[],char c_phone_number[])
{
    system("cls");
    int flag=0;
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    float total_amount=0;
    int i=0;
    while(ptr_c->link!=NULL)
    {
        ptr_c=ptr_c->link;
        if (strcmp(ptr_c->customer_name, c_name) == 0)
        {
            if(i==0)
            {
                system("cls");
                printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
                printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
                printf("\n\t\t\t\t+-------------------------------------------------------+\n");
                printf("\n\n\t\t\t\tName : %s",ptr_c->customer_name);
                printf("\n\t\t\t\tPhone Number : %s\n",ptr_c->customer_phone_number);
                printf("\n\t\t\t\tYou Have Bought : ");
                printf("\n\t\t\t\t-----------------");
                printf("\n\n\t\t\t\tFood Name \tQuantities\tPrice\t\tTotal Price(Taka)");
                printf("\n\t\t\t\t-----------------------------------------------------------------");
            }
            printf("\n\t\t\t\t%-15s %-15d %-15.2f %dx%.2f = %.2f ",ptr_c->ordered_food_name,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity*ptr_c->item_price);
            total_amount=total_amount+(ptr_c->ordered_food_quantity*ptr_c->item_price);
            flag=1;
            i++;
        }
    }
    if(flag==0)
    {
        printf("\n\n\t\t\t\tName : %s",c_name);
        printf("\n\t\t\t\tPhone Number : %s\n",c_phone_number);
        printf("\n\n\t\t\t\tYou Have Not Any Bill\n");
        printf("\n\t\t\t\tYou Must Order First,Then You Calculate Your Bill\n");
        printf("\n\n\t\t\tEnter Any Key To Continue...");
        getch();
        return;
    }
    printf("\n\t\t\t\t-----------------------------------------------------------------");
    printf("\n\t\t\t\tTotal Charge      :\t\t\t\t%.2f Taka",total_amount);
    printf("\n\t\t\t\tWith 10%% Discount\n\t\t\t\tYour Payable Bill Is:\t\t\t\t%.2f Taka",(total_amount*90)/100.0);
    printf("\n\t\t\t\t\t   To Pay Your Bill Go To Cash Counter");
    printf("\n\n\t\t\tEnter Any Key To Continue : ");
    getch();
}


void cash_counter(customer *ptr_c,char c_name[],char c_phone_number[])
{
    system("cls");
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t     Cash Counter\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");

    printf("\n\t\t\t\t%s Please Select Any Payment Method\n",c_name);
    printf("\n\t\t\t ------------------------    ----------------------------     ---------------------");
    printf("\n\t\t\t | 1.Bkash/Nagad/Rocket |    | 2.Credit Card/Debit Card |     |   3.Cash Payment  |");
    printf("\n\t\t\t ------------------------    ----------------------------     ---------------------");
    printf("\n\t\t\t\t\t\t         --------------------");
    printf("\n\t\t\t\t\t\t         |     4.Back       |");
    printf("\n\t\t\t\t\t\t         --------------------\n");
    printf("\n\n\t\t\t\t Enter Your Choice. . .");



    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    {
        int flag=0;
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");



        float total_amount=0;
        int i=0;
        while(ptr_c->link!=NULL)
        {
            ptr_c=ptr_c->link;
            if (strcmp(ptr_c->customer_name, c_name) == 0)
            {
                if(i==0)
                {
                    system("cls");
                    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
                    printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
                    printf("\n\t\t\t\t+-------------------------------------------------------+");
                    printf("\n\n\t\t\t\tName : %s",ptr_c->customer_name);
                    printf("\n\t\t\t\tPhone Number : %s\n",ptr_c->customer_phone_number);
                    printf("\n\t\t\t\tYour Payment Method : \"Bkash/Nagad/Rocket\" ");
                    printf("\n\t\t\t\tYou Have Bought : ");
                    printf("\n\t\t\t\t-----------------");
                    printf("\t\t\t\tDate : %d-%d-%d\n\t\t\t\t\t\t\t\t\t\tTime : %d:%d:%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900,tm.tm_hour, tm.tm_min, tm.tm_sec);
                    printf("\n\n\t\t\t\tFood Name \tQuantities\tPrice\t\tTotal Price(Taka)");
                    printf("\n\t\t\t\t-----------------------------------------------------------------");
                }
                printf("\n\t\t\t\t%-15s %-15d %-15.2f %dx%.2f = %.2f ",ptr_c->ordered_food_name,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity*ptr_c->item_price);
                total_amount=total_amount+(ptr_c->ordered_food_quantity*ptr_c->item_price);
                flag=1;
                i++;
            }
        }
        printf("\n\t\t\t\t-----------------------------------------------------------------");
        printf("\n\t\t\t\tTotal Charge      :\t\t\t\t%.2f Taka",total_amount);
        printf("\n\t\t\t\tWith 10%% Discount\n\t\t\t\tYour Payable Bill Is:\t\t\t\t%.2f Taka",(total_amount*90)/100.0);
        printf("\n\n\t\t\tEnter Any Key To Continue : ");
        getch();
        system("cls");
        break;
    }
    case 2:
    {
        int flag=0;
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");

        float total_amount=0;
        int i=0;
        while(ptr_c->link!=NULL)
        {
            ptr_c=ptr_c->link;
            if (strcmp(ptr_c->customer_name, c_name) == 0)
            {
                if(i==0)
                {
                    system("cls");
                    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
                    printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
                    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
                    printf("\n\n\t\t\t\tName : %s",ptr_c->customer_name);
                    printf("\n\t\t\t\tPhone Number : %s\n",ptr_c->customer_phone_number);
                    printf("\n\t\t\t\tYour Payment Method : \"Credit Card/Debit Card\" ");
                    printf("\n\t\t\t\tYou Have Bought : ");
                    printf("\n\t\t\t\t-----------------");
                    printf("\t\t\t\tDate : %d-%d-%d\n\t\t\t\t\t\t\t\t\t\tTime : %d:%d:%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900,tm.tm_hour, tm.tm_min, tm.tm_sec);
                    printf("\n\n\t\t\t\tFood Name \tQuantities\tPrice\t\tTotal Price(Taka)");
                    printf("\n\t\t\t\t-----------------------------------------------------------------");
                }
                printf("\n\t\t\t\t%-15s %-15d %-15.2f %dx%.2f = %.2f ",ptr_c->ordered_food_name,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity*ptr_c->item_price);
                total_amount=total_amount+(ptr_c->ordered_food_quantity*ptr_c->item_price);
                flag=1;
                i++;
            }
        }
        printf("\n\t\t\t\t-----------------------------------------------------------------");
        printf("\n\t\t\t\tTotal Charge      :\t\t\t\t%.2f Taka",total_amount);
        printf("\n\t\t\t\tWith 10%% Discount\n\t\t\t\tYour Payable Bill Is:\t\t\t\t%.2f Taka",(total_amount*90)/100.0);
        printf("\n\n\t\t\tEnter Any Key To Continue : ");
        getch();
        system("cls");
        break;
    }
    case 3:
    {
        int flag=0;
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");

        float total_amount=0;
        int i=0;
        while(ptr_c->link!=NULL)
        {
            ptr_c=ptr_c->link;
            if (strcmp(ptr_c->customer_name, c_name) == 0)
            {
                if(i==0)
                {
                    system("cls");
                    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
                    printf("\t\t\t\t|\t\t  Total Amount Of Charge\t\t|");
                    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
                    printf("\n\n\t\t\t\tName : %s",ptr_c->customer_name);
                    printf("\n\t\t\t\tPhone Number : %s\n",ptr_c->customer_phone_number);
                    printf("\n\t\t\t\tYour Payment Method : \"Cash Payment\" ");
                    printf("\n\t\t\t\tYou Have Bought : ");
                    printf("\n\t\t\t\t-----------------");
                    printf("\t\t\t\tDate : %d-%d-%d\n\t\t\t\t\t\t\t\t\t\tTime : %d:%d:%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900,tm.tm_hour, tm.tm_min, tm.tm_sec);
                    printf("\n\n\t\t\t\tFood Name \tQuantities\tPrice\t\tTotal Price(Taka)");
                    printf("\n\t\t\t\t-----------------------------------------------------------------");
                }
                printf("\n\t\t\t\t%-15s %-15d %-15.2f %dx%.2f = %.2f ",ptr_c->ordered_food_name,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity,ptr_c->item_price,ptr_c->ordered_food_quantity*ptr_c->item_price);
                total_amount=total_amount+(ptr_c->ordered_food_quantity*ptr_c->item_price);
                flag=1;
                i++;
            }
        }
        printf("\n\t\t\t\t-----------------------------------------------------------------");
        printf("\n\t\t\t\tTotal Charge      :\t\t\t\t%.2f Taka",total_amount);
        printf("\n\t\t\t\tWith 10%% Discount\n\t\t\t\tYour Payable Bill Is:\t\t\t\t%.2f Taka",(total_amount*90)/100.0);
        printf("\n\n\t\t\tEnter Any Key To Continue : ");
        getch();
        system("cls");
        break;
    }
    default:
        printf("\n\n\t\t\tWrong Choice. . .\n");
        break;
    }
}
void customer_option(food *ptr, customer *ptr_c,char c_name[],char c_phone_number[])
{
    system("cls");
    customer_menu();
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        display_menu(ptr);
        printf("\n\n\t\t\t\tPress Any Key To Continue. . .");
        getch();
        break;
    }
    case 2:
        place_order(ptr,ptr_c,c_name,c_phone_number);
        break;
    case 3:
        view_order_item(ptr_c,c_name,c_phone_number);
        break;
    case 4:
        delete_order_item(ptr_c,c_name,c_phone_number);
        break;
    case 5:
        display_final_bill(ptr_c,c_name,c_phone_number);
        break;
    case 6:
        cash_counter(ptr_c,c_name,c_phone_number);
        break;
    case 7:
        main_menu_show(ptr,ptr_c);
        break;
    default:
    {
        system("cls");
        printf("\n\n\t\t\t\tWrong Choice...");
        printf("\n\t\t\t\tPres 1 To 7 Only\n");
        printf("\n\n\t\t\tEnter Any Key To Continue : ");
        getch();
        break;
    }
    }
    customer_option(ptr,ptr_c,c_name,c_phone_number);
}

void customer_section(food *ptr, customer *ptr_c)
{
    system("cls");
    customer *temp=ptr_c;
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t    Customer Section\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\n\t\t\t\t  -----------------------  \t---------------------  ");
    printf("\n\t\t\t\t  | 1.Display Food Menu |  \t|   2.Order Food    |");
    printf("\n\t\t\t\t  -----------------------  \t---------------------  ");
    printf("\n\t\t\t\t\t\t ----------------------");
    printf("\n\t\t\t\t\t\t |      3.Exit        |");
    printf("\n\t\t\t\t\t\t ----------------------\n");
    printf("\n\n\t\t\tEnter Your Choice : ");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    {
        display_menu(ptr);
        printf("\n\n\t\t\t\tPress Any Key To Continue. . .");
        getch();
        break;
    }
    case 2:
    {
        char c_name[50],c_phone_number[20];
        printf("\n\t\t\t\tFor Ordering Purpose. . .");
        printf("\n\n\t\t\t\tEnter Your Name : ");
        fflush(stdin);
        scanf("%[^\n]s", c_name);
        printf("\n\t\t\t\tEnter Your Phone Number : ");
        fflush(stdin);
        scanf("%[^\n]s", c_phone_number);
        customer_option(ptr,ptr_c,c_name,c_phone_number);
        break;
    }
    case 3:
        main_menu_show(ptr,ptr_c);
        break;
    default:
    {
        system("cls");
        printf("\n\n\t\t\t\tWrong Choice...");
        printf("\n\t\t\t\tPres 1 To 3 Only\n");
        printf("\n\t\t\t\tTry Again\n");
        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    }
    customer_section(ptr, ptr_c);
}


void admin_control_menu(food *ptr,customer *ptr_c)
{
    customer *temp_c=ptr_c;
    system("cls");
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t     Admin Section\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\n\t\t\t     ---------------------------         ----------------------------");
    printf("\n\t\t\t     | 1.Show All Manager List |         | 2.Show All Customer List |");
    printf("\n\t\t\t     ---------------------------         ----------------------------");
    printf("\n\t\t\t     ---------------------------         ----------------------------");
    printf("\n\t\t\t     |    3.Show Total Sale    |         |    4.Reset All Settings  |");
    printf("\n\t\t\t     ---------------------------         ----------------------------");
    printf("\n\t\t\t\t\t\t   ----------------------");
    printf("\n\t\t\t\t\t\t   |      5.Back        |");
    printf("\n\t\t\t\t\t\t   ----------------------\n");
    printf("\n\n\t\t\t\t\tEnter Your Choice : ");

    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     All Manager List\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        char name[30], phone_number[30], manager_id[20], username[20],password[10];
        FILE *file_login = fopen("manager_login_panel.txt", "r");
        printf("\n\n\t\t\t\tName\t\tPhone Number\t\tManager ID\t User-name");
        printf("\n\t\t\t\t------------------------------------------------------------------");
        while(fscanf(file_login,"%s %s %s %s %s",name,phone_number,manager_id,username,password)!=EOF)
        {
            printf("\n\t\t\t\t%-15s %-23s %-16s %s",name,phone_number,manager_id,username);
        }
        fclose(file_login);
        printf("\n\n\t\t\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    case 2:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     All Customer List\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        char name[40];
        if(temp_c->link==NULL)
        {
            printf("\n\t\t\t\tList Is Empty\n");
        }
        else
        {
            printf("\n\n\t\t\t\tName\t\tPhone Number");
            printf("\n\t\t\t\t----------------------------");
            while(temp_c->link!=NULL)
            {
                temp_c=temp_c->link;
                if(strcmp(name,temp_c->customer_name)!=0)
                {
                    printf("\n\t\t\t\t%-15s %s",temp_c->customer_name,temp_c->customer_phone_number);
                    strcpy(name,temp_c->customer_name);
                }
            }
        }

        printf("\n\n\t\t\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    case 3:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     Display Total Sales\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        char name[50];
        int quantity;;
        float price,total_amount=0;
        FILE *file_t = fopen("Sold_food_Lsit.csv", "r");
        printf("\n\n\t\t\t\tFood Name \tQuantities\tPrice\t\tTotal Price");
        printf("\n\t\t\t\t------------------------------------------------------------\n");
        while (fscanf(file_t, "%49[^,],%d,%f\n", name, &quantity, &price) == 3)
        {
            printf("\t\t\t\t%-15s %-15d %-15.2f %.2f\n", name, quantity, price,quantity*price);
            total_amount+=quantity*price;
        }
        printf("\t\t\t\t------------------------------------------------------------\n");
        fclose(file_t);
        printf("\t\t\t\tTotal Amount :\t\t\t%.2f Taka",total_amount);

        printf("\n\n\t\t\tEnter Any Key To Continue. . .");
        getch();
        break;
    }
    case 4:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t\tReset\t\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\n\t\t\t\t   ------------------------     ----------------------");
        printf("\n\t\t\t\t   | 1.Reset All Settings |     |  2.Reset All Data  |");
        printf("\n\t\t\t\t   ------------------------     ----------------------");
        printf("\n\t\t\t\t\t\t   --------------------");
        printf("\n\t\t\t\t\t\t   |      3.Back      |");
        printf("\n\t\t\t\t\t\t   --------------------");

    printf("\n\n\t\t\t\t\tEnter Your Choice : ");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t    Reset All Settings\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\n\t\t\t\tAfter Getting Reset,You Lost All Settings!!");
        printf("\n\n\t\t\t\tAre You Sure To Reset All Settings??");
        printf("\n\n\t\t\t\tPress Only 'Y' For Reset Or press Any Key For Skip : ");
        char c;
        scanf(" %c",&c);
        if(c=='Y' || c=='y')
        {
            printf("\n\n\t\t\t\tReset Done\n");
        }
        else
        {
            admin_control_menu(ptr,ptr_c);
        }

        break;
    }
    case 2:
    {
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t    Reset All Data\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\n\t\t\t\tAfter Getting Reset,You Lost All Data!!");
        printf("\n\n\t\t\t\tAre You Sure To Reset All Data??");
        printf("\n\n\t\t\t\tPress Only 'Y' For Reset Or press Any Key For Skip : ");
        char c;
        scanf(" %c",&c);
        if(c=='Y' || c=='y')
        {
            remove("manager_login_panel.txt");
            remove("Sold_food_Lsit.csv");
            printf("\n\n\t\t\t\tReset Done\n");
        }
        else
        {
            admin_control_menu(ptr,ptr_c);
        }
        break;
    }
    }
    printf("\n\n\t\t\tEnter Any Key To Continue. . .");
    getch();
    }
case 5:
    main_menu_show(ptr,ptr_c);
    break;
}
admin_control_menu(ptr,ptr_c);
}


void admin_section(food *ptr,customer *ptr_c)
{
    system("cls");
    int choice;
    printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|\t\t     Admin Section\t\t\t|");
    printf("\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\n\t\t\t\t\t\t     ------------------");
    printf("\n\t\t\t\t\t\t     |     1.Login    |");
    printf("\n\t\t\t\t\t\t     ------------------");
    printf("\n\t\t\t\t\t\t     ------------------");
    printf("\n\t\t\t\t\t\t     |     2.Back     |");
    printf("\n\t\t\t\t\t\t     ------------------");
    printf("\n\n\t\t\t\t\tEnter Your Choice : ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    {
        system("cls");
        printf("\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
        printf("\t\t\t\t|\t\t     Admin Login\t\t\t|");
        printf("\n\t\t\t\t+-------------------------------------------------------+\n");
        char name[30],password[10];
        printf("\n\n\t\t\t\t\tEnter Admin User Name : ");
        fflush(stdin);
        scanf("%[^\n]s", name);
        printf("\n\t\t\t\t\tEnter Admin Password : ");
        fflush(stdin);
        scanf("%[^\n]s",password);

        if(strcmp(name,"redoy")==0 && strcmp(password,"1491")==0)
        {
            admin_control_menu(ptr,ptr_c);
        }
        else
        {
            printf("\n\n\t\t\t\tTry Again\n");
        }

        break;
    }
    case 2:
        main_menu_show(ptr,ptr_c);
        break;
    default:
    {
        system("cls");
        printf("\n\n\t\t\t\tWrong Choice...");
        printf("\n\t\t\t\tPres 1 To 2 Only\n");
        printf("\n\t\t\t\tTry Again\n");
        printf("\n\n\t\t\t\t\tEnter Any Key To Continue. . .");
        getch();
        admin_section(ptr,ptr_c);
        break;
    }
    }
    printf("\n\n\t\t\t\t\tEnter Any Key To Continue. . .");
    getch();
    system("cls");
}

void insert_item_in_menu(food *ptr, char f_name[], int f_quantity, float f_price, int f_id)
{
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = (food *)malloc(sizeof(food));
    ptr = ptr->next;
    strcpy(ptr->food_name, f_name);
    ptr->quantity = f_quantity;
    ptr->price = f_price;
    ptr->food_id = f_id;
    ptr->next = NULL;
}

void display_food_menu_item_insert(food *ptr)
{
    //food menu//

//Burger item//
    int i=101;
    insert_item_in_menu(ptr,"Chicken Burger",25,180,i++);
    insert_item_in_menu(ptr,"Beef Burger",25,200,i++);
    insert_item_in_menu(ptr,"Cheese Burger",25,150,i++);
    insert_item_in_menu(ptr,"Egg Burger",25,120,i++);
    insert_item_in_menu(ptr,"Spicy Burger",25,120,i++);

//Appetizers item//
    insert_item_in_menu(ptr,"Fruit Salad",25,100,i++);
    insert_item_in_menu(ptr,"Sandwich",25,120,i++);
    insert_item_in_menu(ptr,"French Fries",25,100,i++);
    insert_item_in_menu(ptr,"Nuggets",25,100,i++);

//Beverage item//
    insert_item_in_menu(ptr,"Orange Juice",25,50,i++);
    insert_item_in_menu(ptr,"Mango Juice",25,50,i++);
    insert_item_in_menu(ptr,"Strawberry Juice",25,100,i++);
    insert_item_in_menu(ptr,"Lemon Juice",25,50,i++);
    insert_item_in_menu(ptr,"Mineral Water",25,20,i++);


//Coffee item//
    insert_item_in_menu(ptr,"Americano",25,120,i++);
    insert_item_in_menu(ptr,"Cappuccino",25,120,i++);
    insert_item_in_menu(ptr,"Latte",25,100,i++);
    i++;


}
void main_menu_show(food *ptr,customer *ptr_c)
{
    system("cls");
    while (1)
    {
        printf("\n\n\n\t\t\t\t+=======================================================+\n");
        printf("\t\t\t\t|\t\t     FOODIE MANAGER\t\t\t|");
        printf("\n\t\t\t\t+=======================================================+\n");
        printf("\n\t\t\t  ----------------------   ---------------------     ---------------------");
        printf("\n\t\t\t  | 1.Customer Section |   | 2.Manager Section |     |  3.Admin Section  |");
        printf("\n\t\t\t  ----------------------   ---------------------     ---------------------");
        printf("\n\t\t\t\t  ----------------------\t----------------------");
        printf("\n\t\t\t\t  |      4.Help        |\t|      5.Exit        |");
        printf("\n\t\t\t\t  ----------------------\t----------------------\n");
        printf("\n\n\t\t\t\t\tEnter Your Choice : ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            customer_section(ptr,ptr_c);
            break;
        case 2:
            manager_section(ptr,ptr_c);
            break;
        case 3:
            admin_section(ptr,ptr_c);
            break;
        case 4:
            help();
            break;
        case 5:
            exit(5);
            break;
        default:
        {
            system("cls");
            printf("\n\n\t\t\t\tWrong Choice...");
            printf("\n\t\t\t\tPres 1 To 5 Only\n");
            printf("\n\t\t\t\tTry Again\n");
            printf("\n\n\t\t\tEnter Any Key To Continue : ");
            getch();
            system("cls");
            break;
        }
        }
    }
}

int main()
{
    system("color E5");
    food *head, *ptr;
    head = (food *)malloc(sizeof(food));
    head->next = NULL;
    ptr = head;


    customer *head_c,*ptr_c;
    head_c=(customer *)malloc(sizeof(customer));
    head_c->link=NULL;
    ptr_c=head_c;

    display_food_menu_item_insert(ptr);

    printf("\n\n\n\t\t\t\t+=======================================================+\n");
    printf("\t\t\t\t|\t\t     FOODIE MANAGER\t\t\t|");
    printf("\n\t\t\t\t+=======================================================+\n");

    printf("\n\t\t\t\t\t\tData Structure Project\n");
    printf("\t\t\t\t\t       ------------------------\n");
    printf("\n\t\t\t\tBy :");

    printf("\n\t\t\t\t\t                    \"tech wizards\"");
    printf("\n\t\t\t\t\t  +------------------------------+");
    printf("\n\t\t\t\t\t  |   Ashraful Islam Redoy(178)  |");
    printf("\n\t\t\t\t\t  |   Tarak Rahman        (137)  |");
    printf("\n\t\t\t\t\t  |   Sakib Ahmned        (085)  |");
    printf("\n\t\t\t\t\t  |   Rokibul Islam Robin (154)  |");
    printf("\n\t\t\t\t\t  +------------------------------+");

    printf("\n\n\n\t\t\t\tPress Any Key To Continue. . .");
    getch();

    main_menu_show(ptr,ptr_c);
    return 0;
}

