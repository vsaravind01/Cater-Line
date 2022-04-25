/* structure to collect and
   store the users records
*/
typedef struct 
{
    char users[50];
    char password[23];
    char type[5];
}user_database;

/* structure to collect and
   store the dishes records
*/
typedef struct
{
    int sno;
    char dish[25];
    float price;
    int quantity;
}dish_database;

/* structure to collect and
   store the order records
*/
typedef struct
{
    int sno;
    char name[25];
    int order_quantity;
    float order_price;
}order;

/* function to clear the screen 
   and display the header
*/
void mainScreen(){
    system("cls");
    printf("\n\t\tCANTEEN MANAGEMENT SYSTEM\n\n");
}

/* function to compute and
   return the number of records 
   in a given database
*/
int records(char filename[25]){
    FILE *file;
    char ch;
    int lines=0;

    file=fopen(filename,"r");
    if(file==NULL) {
        printf("File \"%s\" does not exist!!!\n","users.csv");
        return -1;
    }

    while((ch=fgetc(file))!=EOF) {
        if(ch=='\n')
            lines++;
    }
    fclose(file);
    return lines;
}

/* removes the dish with
   the given serial number
*/
int remove_dish(int sno)
{
    int dish_records = records("dishes.csv");

    dish_database data[dish_records];
    FILE *File = fopen("dishes.csv", "r+");

    if(File == NULL){
        printf("File did not open");
    }
    
    char line[500];
    
    fgets(line,1024,File);
    int i = 0;

    order dish[dish_records];

    /* fetching the dishes data 
       and storing it in the
       form of an array of 
       'dish_database' structure
    */ 
    while(fgets(line,500,File) != NULL){
        data[i].sno = atoi(strtok(line,","));
        strcpy(data[i].dish, strtok(NULL,","));
        data[i].price = atof(strtok(NULL,","));
        data[i].quantity = atoi(strtok(NULL,",\n"));
        i++;
    }

    /* variable to hold the status of
       dish availabiliy 
    */
    int data_exist = 0;

    // creating a new file called "temp.csv"
    FILE *file_modify = fopen("temp.csv","a+");

    // appending the column header
    fprintf(file_modify,"SNO,ITEM,PRICE,QUANTITY");

    int dish_sno = 1;
    for(int j = 0 ; j < dish_records ; j++)
    {
        /* appends the records to the temp.csv if 
           the serial number dosen't match
        */
        if(sno != data[j].sno)
        {
            fprintf(file_modify,"\n%d,%s,%.2f,%d", dish_sno, data[j].dish, data[j].price, data[j].quantity);
            dish_sno = dish_sno + 1;
        }
        else
        {
            data_exist = 1;
        }
        
    }
    fclose(File);
    fclose(file_modify);

    // Deleting the pre-existing dish database "dishes.csv"
    remove("dishes.csv");

    // renaming "temp.csv" to "dishes.csv"
    rename("temp.csv","dishes.csv");

    // returning the status of dish availabilty
    return data_exist;
}

/* function to modify a dish
   by passing the new data to be modified,
   parameter to be modified and the serial
   number of the dish to be modified.
*/
int modify(char new_data[25], int choice, int sno)
{
    int dish_records = records("dishes.csv");

    dish_database data[dish_records];
    FILE *File = fopen("dishes.csv", "r+");

    if(File == NULL)
    {
        printf("File did not open");
    }
    
    char line[500];

    fgets(line,1024,File);
    int i = 0;

    order dish[dish_records];

    /* fetching the dishes data 
       and storing it in the
       form of an array of 
       'dish_database' structure
    */ 
    while(fgets(line,500,File) != NULL){
        data[i].sno = atoi(strtok(line,","));
        strcpy(data[i].dish, strtok(NULL,","));
        data[i].price = atof(strtok(NULL,","));
        data[i].quantity = atoi(strtok(NULL,",\n"));
        i++;
    }

    /* variable to hold the status of
       dish availabiliy 
    */
    int data_exist = 0;

    for(int j = 0 ; j < dish_records ; j++)
    {
        // checks whether the serial number exists
        if(sno == data[j].sno)
        {
            data_exist = 1;
            switch(choice)
            {
                case 1:
                    strcpy(data[j].dish,new_data);
                    break;
                case 2:
                    data[j].quantity = data[j].quantity - atoi(new_data);
                    break;
                case 3:
                    data[j].price = atof(new_data);
                    break;
                case 4:
                    data[j].quantity = data[j].quantity + atoi(new_data);
                    break;
            }
        }
    }
    fclose(File);

    // creating a new file called "temp.csv"
    FILE *file_modify = fopen("temp.csv","a+");

    // appending the column header
    fprintf(file_modify,"SNO,ITEM,PRICE,QUANTITY");
    int lines = records("dishes.csv");

    // appending the modified dish record
    for(int i = 0; i < lines; i++)
    {
        fprintf(file_modify,"\n%d,%s,%.2f,%d", data[i].sno, data[i].dish, data[i].price, data[i].quantity);
    }
    fclose(file_modify);

    // Deleting the pre-existing dish database "dishes.csv"
    remove("dishes.csv");

    // renaming "temp.csv" to "dishes.csv"
    rename("temp.csv","dishes.csv");

    // returning the status of dish availabilty
    return data_exist;
}

/* displays all the available dishes in the database
   made for the admins
*/
void display_dishes()
{
    int dish_records = records("dishes.csv");

    dish_database data[dish_records];
    FILE *File = fopen("dishes.csv", "r");

    char line[500];
    int i = 0;

    fgets(line,1024,File);

    /* fetching the dishes data 
       and storing it in the
       form of an array of 
       'dish_database' structure
    */ 
    while(fgets(line,500,File) != NULL)
    {
        data[i].sno = atoi(strtok(line,","));
        strcpy(data[i].dish, strtok(NULL,","));
        data[i].price = atof(strtok(NULL,","));
        data[i].quantity = atoi(strtok(NULL,",\n"));
        i++;
    }

    printf("\n\nAvailable Dishes in Database : \n");

    for(int j=0 ; j<dish_records ; j++)
    {
        printf("%d) %s\t\t - x%d\t\t - Rs. %.2f\n",data[j].sno, data[j].dish, data[j].quantity, data[j].price);
    }

    fclose(File);
}

/* checking for the availability
   of the user credentials
*/
char search(char username[50], char password[23])
{
    int user_records = records("users.csv");
    user_database data[user_records];

    FILE *inFile = fopen("users.csv", "r");

    char line[500];
    int i = 0;

    fgets(line,1024,inFile);

    /* fetching the users data 
       and storing it in the
       form of an array of 
       'user_database' structure
    */ 
    while(fgets(line,500,inFile) != NULL){
        strcpy(data[i].users, strtok(line,","));
        strcpy(data[i].password, strtok(NULL,","));
        strcpy(data[i].type, strtok(NULL,",\n"));
        i++;
    }

    for(int j=0 ; j<user_records ; j++)
    {
        // checks for the availability of the username
        if(!strcmp(username, data[j].users))
        {
            // checks for the password match of the users'
            if(!strcmp(password, data[j].password))
            {
                // finding the type of the account
                if(strcmp(data[j].type,"user") == 0){
                    return 'u';
                }
                else
                {
                    return 'a';
                }
            }else
            {
                return 'p';
            }
            
        }
    }
    return 'n';
}

/* funciton to provide
   dish ordering page
*/
void dish(char username[50]){

    mainScreen();

    int dish_records = records("dishes.csv");

    dish_database data[dish_records];
    FILE *File = fopen("dishes.csv", "r");

    char line[500];

    fgets(line,1024,File);
    int i = 0;

    order dish[dish_records];
    int dish_no = 0, shop = 1;

    /* fetching the dishes data 
       and storing it in the
       form of an array of 
       'dish_database' structure
    */ 
    while(fgets(line,500,File) != NULL){
        data[i].sno = atoi(strtok(line,","));
        strcpy(data[i].dish, strtok(NULL,","));
        data[i].price = atof(strtok(NULL,","));
        data[i].quantity = atoi(strtok(NULL,",\n"));
        i++;
    }

    // loops until the 'shop' points a TRUE value
    while (shop)
    {
        mainScreen();

        printf("\n\nAvailable Dishes : \n");
        for(int j=0 ; j<dish_records ; j++){

            // displaying the available dishes (quantity > 0)
            if(data[j].quantity != 0)
                printf("%d) %s\t\t - Rs. %.2f\n",data[j].sno, data[j].dish, data[j].price);
        }

        int choice, quantity;
        printf("\nEnter your choice [Serial Number] > ");
        scanf("%d",&choice);getchar();

        int dish_exist = 0;
        for(int k=0 ; k<dish_records ; k++)
        {
            if(data[k].sno == choice)
            {   
                dish_exist = 1;
                mainScreen();
                printf("\nEnter the quantity >");
                scanf("%d",&quantity);getchar();

                /* checks for the quantity overflow
                   and prompts the user whether he/she
                   is willing to buy all the stock
                   of the dish available
                */
                if(quantity > data[k].quantity)
                {
                    mainScreen();
                    printf("\nSorry, we have only %d left in %s.\n",data[k].quantity, data[k].dish);
                    printf("\nDo you wish to buy %d quantity of %s?\n[y - Yes | n - Re-enter quantity | Any other key - No] >",data[k].quantity, data[k].dish);
                    char ch;
                    scanf(" %c",&ch);
                    fflush(stdin);
                    if(ch == 'y' || ch == 'Y')
                    {
                        dish[dish_no].sno = data[k].sno;
                        strcpy(dish[dish_no].name, data[k].dish);
                        dish[dish_no].order_quantity = data[k].quantity;
                        dish[dish_no].order_price = dish[dish_no].order_quantity * data[k].price;
                        dish_no++;
                        dish[dish_no].sno = -1;
                    }
                    else if (ch == 'n' || ch == 'N')
                    {
                        k = k - 1;
                        continue;
                    }
                    else
                    {
                        shop = 1;
                        continue;
                    }       
                }
                else
                {
                    dish[dish_no].sno = data[k].sno;
                    strcpy(dish[dish_no].name, data[k].dish);
                    dish[dish_no].order_quantity = quantity;
                    dish[dish_no].order_price = dish[dish_no].order_quantity * data[k].price;
                    dish_no = dish_no + 1;
                    dish[dish_no].sno = -1;
                }

                mainScreen();
                printf("\n\nYour current order : \n");
                for(int i = 0; dish[i].sno != -1; i++)
                {
                    printf("%d) %s\t-\tx%d\t-\tRs. %.2f\n",i+1, dish[i].name, dish[i].order_quantity, dish[i].order_price);
                }
                printf("Do you need to buy anything more? [ y - Yes | Any other key - No ] > ");
                char ch = getchar();
                if(ch == 'y' || ch == 'Y'){
                    shop = 1;
                }else
                {
                    shop = 0;
                }
            }
        }

        // actions for the unavailability of the dish
        if(!dish_exist)
        {
            mainScreen();
            printf("Sorry... the choice you entered isn't in our catalogue menu...\n");
            printf("Please enter a choice from the catalogue menu...\n");
            printf("Press any key to continue > ");
            getchar();
        }
    }
    fclose(File);

    FILE *file_order = fopen("orders.csv","a+");
    char quantity[20];

    // appending the records to the "orders.csv" file
    for(int i = 0; dish[i].sno != -1; i++)
    {
        fprintf(file_order,"\n%s,%d,%s,%d,%.2f", username, dish[i].sno, dish[i].name, dish[i].order_quantity, dish[i].order_price);
        modify(itoa(dish[i].order_quantity,quantity,10), 2, dish[i].sno);
    }
    fclose(file_order);
}

/* Function to display the orders.
   Displays all the orders to an admin,
   But for an user displays only the orders
   placed by the respective user alone.
*/
void orders(char username[50], int isAdmin){

    mainScreen();

    int order_records = records("orders.csv");
    order data[order_records];

    FILE *inFile = fopen("orders.csv", "r");

    char line[500];
    fgets(line,1024,inFile);

    int i = 0;
    char user[order_records][50];

    while(fgets(line,500,inFile) != NULL){
        strcpy(user[i], strtok(line,","));
        data[i].sno = atoi(strtok(NULL,","));
        strcpy(data[i].name, strtok(NULL,","));
        data[i].order_quantity = atoi(strtok(NULL,","));
        data[i].order_price = atof(strtok(NULL,","));
        i++;
    }

    i = 0;

    int ordered = 0; // variable to hold the status of the availablity of order history

    for(int j=0 ; j<order_records ; j++)
    {
        // condition to chech whether the account is "Admin" (or) username of the "user" exists
        if(isAdmin || !strcmp(username, user[j]))
        {
            ordered = 1;
            i++;
            printf("\n%d) %s\t-\tx%d\t-\tRs. %5.2f\n",i, data[j].name, data[j].order_quantity, data[j].order_price);
        }
    }

    // action for the unavailability of any order history
    if(!ordered){
        printf("\tSorry, you haven't ordered anything yet!");
    }
    fclose(inFile);
    printf("\n\n\tEnter any key to continue > ");
    getch();
}