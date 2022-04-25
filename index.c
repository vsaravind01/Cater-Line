#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"


/* function to store the username
   in the by passing the memory
   address of a string variable (character array)
*/
void getUsername(char *user)
{
    printf("\n\n\tUsername : ");
    scanf("%[^\n]",user);
}



/* function to store the password
   in the by passing the memory
   address of a string variable (character array)
*/
void getPassword(char *pass)
{

    printf("\n\tPassword : ");
    char c;
    int i = 0;

    while((c = getch()) != '\r')
    {
        // checking for valid character
        if(c > 31 && c < 127 && i < 22)
        {
            printf("%c",221);   // morphing the entered character by the user
            pass[i++] = c;
        }
    }
    pass[i] = '\0';
}



//Login page function
void login()
{
    mainScreen();

    printf("\n\t\tLOGIN");
    fflush(stdin);

    char username[50];
    getUsername(username);

    char password[23];
    getPassword(password);

    char user_status = search(username,password);   // fetching the user credentials status

    /*  
    user_status :
        'u' - The credentials corresponds to a "user"
        'a' - The credentials corresponds to an "admin"
        'p' - Incorrect password
        'n' - The user dosen't exist
    */

    // checking whether the user exists
    if(user_status != 'n' && user_status != 'p')
    {
        // checking whether the credentials corresponds to a "user"
        if(user_status == 'u'){
            while (1)
            {
                mainScreen();

                printf("\n\t\t   Hi, %s.\n\n\t1. Place Order\n\t2. View Orders\n\t3. Exit\n\n\tEnter your choice > ",username);
                char ch = getch();

                // redirects to the ordering page
                if(ch == '1')
                {
                    dish(username);
                }
                // displays the orders history of the respective user
                if(ch == '2')
                {
                    orders(username,0);
                }
                // exits the application
                if(ch == '3')
                {
                    mainScreen();
                    printf("\n\n\tThank you for using CANTEEN MANAGEMENT SYSTEM!\n\n\n\n");
                    break;
                }
            }
        }
        // at this point, if it's not "user" then it's "admin"
        else
        {
            while (1)
            {
                mainScreen();

                printf("\n\n\t1. View Orders\n\t2. Modify Dish\n\t3. Add Dish\n\t4. Remove Dish\n\t5. Exit\n\n\tEnter your choice > ");
                char ch = getch();

                // displays the orders of all the users
                if(ch == '1')
                {
                    orders(username,1);
                }
                // redirects to the page where the users can modify the dish parameters
                if(ch == '2')
                {
                    char choice;
                    mainScreen();
                    getchar();

                    printf("\n\n\t1. Modify dish name\n\t2. Modify dish price\n\t3. Modify dish quantity\n\n\tEnter your choice > ");
                    choice = getch();

                    int sno;
                    char new_data[25];
                    int dish_exist;

                    // modifying the dish name
                    if(choice == '1')
                    {
                        do
                        {
                            mainScreen();
                            
                            display_dishes();
                            
                            printf("\n\n\tEnter the serial number of the dish to be modified > ");
                            scanf("%d",&sno);
                            getchar();
                            
                            dish_exist = modify("just to check", 0, sno); // fetching the status of availability of the dish
                            
                            /*  
                            dish_exist :
                                1 - Dish exists
                                0 - Dish dosen't exist
                            */
                            if(dish_exist)
                            {
                                mainScreen();
                                
                                printf("\n\nEnter your new dish name > ");
                                scanf("%[^\n]",new_data);
                                modify(new_data,1,sno);
                                break;
                            }else
                            {
                                mainScreen();
                                
                                printf("\n\nSorry, the dish serial number does not exist\n\tPress any key > ");
                                getchar();
                                getch();
                                continue;
                            }
                        }while(1);
                    }

                    // modifying the dish price
                    else if(choice == '2')
                    {
                        do
                        {
                            mainScreen();
                            
                            display_dishes(); // Display the available dishes
                            
                            printf("\n\n\tEnter the serial number of the dish to be modified > ");
                            scanf("%d",&sno);
                            getchar();
                            
                            dish_exist = modify("just to check", 0, sno);
                            
                            if(dish_exist)
                            {
                                mainScreen();

                                printf("Enter your new price for the dish > ");
                                scanf("%[^\n]",new_data);
                                modify(new_data,3,sno);
                                break;
                            }else
                            {
                                mainScreen();

                                printf("Sorry, the dish serial number does not exist\n\tPress any key > ");
                                getchar();
                                getch();
                                continue;
                            }
                        }while(1);
                    }

                    // adding dish stock
                    else if (choice == '3')
                    {
                        do
                        {
                            mainScreen();
                            
                            display_dishes();
                            
                            printf("\n\n\tEnter the serial number of the dish to be modified > ");
                            scanf("%d",&sno);
                            getchar();
                            
                            dish_exist = modify("just to check", 0, sno);
                            
                            if(dish_exist)
                            {
                                mainScreen();

                                printf("Enter your quantity in integers to be added to the stock > ");
                                scanf("%[^\n]",new_data);
                                modify(new_data,4,sno);
                                break;
                            }else
                            {
                                mainScreen();

                                printf("Sorry, the dish serial number does not exist\n\tPress any key > ");
                                getchar();
                                getch();
                                continue;
                            }
                        }while(1);
                    }           
                }

                // adding a new dish to the database
                if(ch == '3'){
                    mainScreen();

                    fflush(stdin);
                    dish_database dish;
                    printf("Enter your dish name : ");
                    scanf("%[^\n]",dish.dish);

                    printf("Enter price : ");
                    scanf("%f",&dish.price);

                    printf("Enter quantity : ");
                    scanf("%d",&dish.quantity);

                    int lines = records("dishes.csv");
                    FILE *file_modify = fopen("dishes.csv","a+");
                    fprintf(file_modify,"\n%d,%s,%.2f,%d",lines+1,dish.dish,dish.price,dish.quantity);
                    fclose(file_modify);
                    printf("\n\n\t'%s' has been added successfully in the dishes catalogue!\n\tPress any key to redirect to continue > ",dish.dish);
                    getchar();
                    getch();
                }

                if(ch == '4')
                {
                    while(1)
                    {
                        mainScreen();

                        display_dishes();

                        int sno;

                        printf("Enter the serial number of the dish to be removed from the database > ");
                        scanf("%d",&sno);
                        
                        int removed = remove_dish(sno);

                        if(removed)
                        {
                            printf("The dish has been successfully removed from the database!\nPress any key to continue");
                            getchar();
                            getch();
                            break;
                        }else
                        {
                            printf("The dish is not available in the database!\nPlease enter a valid serial number.\nPress any key to continue");
                            getchar();
                            getch();
                        }
                    }
                }

                // Exiting the application
                if(ch == '5')
                {
                    mainScreen();
                    printf("\n\n\tThank you for using CANTEEN MANAGEMENT SYSTEM!\n\n\n\n\n");
                    break;
                }
            }
        }
    }

    // Actions for invalid user credentials
    else
    {
        if(user_status == 'p')
        {
            printf("\n\n\tIncorrect password!\n\tPress any key > ");
        }
        else
        {
            printf("\n\n\tSorry, the username '%s' dosen't exist!\n\tPress any key > ",username);
        }
        getchar();
        getch();
        login();
    }
}

// Sign-up page function
void sign_up()
{
    mainScreen();
    fflush(stdin);

    printf("\n\t\tSIGN-UP");

    char username[50];
    getUsername(username);

    char password[23];
    getPassword(password);
    
    char type;

    do
    {
        mainScreen();
        printf("Account type : [U - User | A - Admin] > ");
        type = getch();
    } while (type != 'u' && type != 'U' && type != 'a' && type != 'A');

    // checking whether the user name dosen't exist before
    if(search(username,password) == 'n')
    {
        FILE *file_modify = fopen("users.csv","a+");
        fprintf(file_modify,"\n%s,%s,%s",username,password,(type=='u'|| type=='U')?"user":"admin");
        fclose(file_modify);
        printf("\n\n\tYour account has been successfully registered!\n\tPress any key to redirect to login page > ");
        getchar();
        getch();
        login();
    }
    // Actions to be taken if the username already exists
    else
    {
        mainScreen();
        printf("\nSorry, the username is already taken!");
        getchar();
        getch();
        sign_up();
    }
    
}
// Main function
int main(void)
{
    mainScreen();

    while(1)
    {
        // Displaying the menu and getting the user's choice
        printf("\n\n\t1. Sign-in\n\t2. Sign-up\n\t3. Quit\n\n\tEnter your choice > ");
        char ch = getch();

        if(ch == '1')
        {
            login();
            continue;
        }
        else if(ch == '2' )
        {
            sign_up();
            continue;
        }
        else if(ch == '3')
        {
            break;
        }
        mainScreen();
    }
    return 0;
}