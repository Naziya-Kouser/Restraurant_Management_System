#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#include <unistd.h>


#define MAX_WORD_LENGTH 15
#define MAX_ATTEMPTS 6
#define MAX_REVIEWS 5
#define MAX_INGREDIENTS 5
#define MAX_NAME_LENGTH 50
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL,*newnode,*tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

struct RatingReview {
    char username[50];
    int rating;
    char review[100];
};

typedef struct {
    int orderId;
    char status[50];
} Order;

typedef struct Recipe {
    char name[MAX_NAME_LENGTH];
    char ingredients[MAX_INGREDIENTS][MAX_NAME_LENGTH];
    int numIngredients;
} Recipe;




void menu(void);
void displayList();
void calculatetotsales();
int deleteadmin();
int deletecustomer();
void displaybill();
void adminmenu();
void customermenu();
void admin();
void customer();
void recipe();
void login();
void games();




void displayOrder(Order order) {
    printf("Order ID: %d\nStatus: %s\n", order.orderId, order.status);
}

void drawVerticalLine(int length) {
    for (int i = 0; i < length; ++i) {
        printf("| \n");
    }
}

void drawBox(const char *text, int length) {
    int leadingSpaces = (length - strlen(text)) / 2;
    int trailingSpaces = length - strlen(text) - leadingSpaces;

    printf("+");
    for (int i = 0; i < length; ++i) {
        printf("-");
    }
    printf("+\n");

    printf("|");
    for (int i = 0; i < leadingSpaces; ++i) {
        printf(" ");
    }
    printf("%s", text);
    for (int i = 0; i < trailingSpaces; ++i) {
        printf(" ");
    }
    printf("|\n");

    // Draw a horizontal line at the center of the box
    printf("+");
    for (int i = 0; i < length; ++i) {
        if (i == length / 2) {
            printf("-");
        } else {
            printf("-");
        }
    }
    printf("+\n");
}

void updateOrderStatus(Order *order, const char *newStatus) {
    strcpy(order->status, newStatus);
}

void animateStatusTransition(const char *status, int length) {
    // Draw the vertical line with a dot moving along it
    for (int i = 0; i < length; ++i) {
        printf("| ");
        if (i == length / 2) {
            printf("*");  // Place the dot in the middle of the line
        } else {
            printf(" ");
        }
        printf("\n");
    }

    // Draw a centered box around the status
    drawBox(status, length);
    sleep(2);  // Delay for 2 seconds
}

void animateStatus(const char *status, int length) {
    // Draw a centered box around the status
    drawBox(status, length);
    sleep(2);  // Delay for 2 seconds
}

void setcolor(int ForgC)
{ WORD wColor;
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
{
	wColor=(csbi.wAttributes & 0xF0)+(ForgC & 0x0F);
//	SetConsoleTextAttributes(hStdOut,wColor);
	SetConsoleTextAttribute(hStdOut,wColor);

}
}




void playGuessingGame() {
    FILE *fp;
    char c;int minNumber = 1;
    int maxNumber = 100;
    system("cls");
    main:
    // Set the range for the random number
    // Generate a random number within the specified range
    srand(time(NULL));
    int targetNumber = rand() % (maxNumber - minNumber + 1) + minNumber;

    int guess;
    int attempts = 0;

    printf("Welcome to the Guessing Game!\n");
    printf("Try to guess the number between %d and %d.\n", minNumber, maxNumber);

    do {
        // Get the player's guess
        printf("Enter your guess: ");
        scanf("%d", &guess);

        // Provide feedback
        if (guess < targetNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > targetNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations! You guessed the correct number in %d attempts.\n", attempts + 1);
        }

        attempts++;

    } while (guess != targetNumber);

    printf("The correct number was %d.\n", targetNumber);

do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to recipe section");

	}
	while((c = getch()) =='\r');
	recipe();

}





char* wordList[] = {"biryani", "pani puri", "rasgulla", "fried rice", "pasta", "malai kofta", "popcorn","spring rolls","soup","sandwich"};
void playRecipeGame() {
    FILE *fp;
    char c;
    system("cls");
    main:
    srand(time(NULL));

    // Select a random word from the list
    int randomIndex = rand() % (sizeof(wordList) / sizeof(wordList[0]));
    char* targetWord = wordList[randomIndex];

    int wordLength = strlen(targetWord);
    char guessedWord[MAX_WORD_LENGTH];
    strcpy(guessedWord, targetWord);  // Initialize guessedWord with the target word
    for (int i = 0; i < wordLength; ++i) {
        if (targetWord[i] != ' ') {
            guessedWord[i] = '_';  // Replace letters with underscores in the guessedWord
        }
    }

    int attempts = 0;
    char guessedLetters[MAX_WORD_LENGTH] = {'\0'};

    printf("Welcome to the Word Guessing Game!\n");
    printf("Try to guess the word.\n");

    do {
        printf("\nCurrent word: %s\n", guessedWord);
        printf("Guessed letters: %s\n", guessedLetters);
        printf("Attempts left: %d\n", MAX_ATTEMPTS - attempts);

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);  // Using a space before %c to consume any newline characters in the buffer

        if (strchr(guessedLetters, guess) != NULL) {
            printf("You've already guessed the letter '%c'. Try again.\n", guess);
        } else {
            guessedLetters[strlen(guessedLetters)] = guess;  // Add guessed letter to the list

            if (strchr(targetWord, guess) != NULL) {
                // Update guessedWord with the correctly guessed letter
                for (int i = 0; i < wordLength; ++i) {
                    if (targetWord[i] == guess) {
                        guessedWord[i] = guess;
                    }
                }
            } else {
                printf("Incorrect guess! Try again.\n");
                attempts++;
            }
        }

        // Check if the player guessed the entire word
        if (strcmp(guessedWord, targetWord) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", targetWord);
            break;
        }

    } while (attempts < MAX_ATTEMPTS);

    if (attempts == MAX_ATTEMPTS) {
        printf("\nSorry, you've reached the maximum number of attempts. The correct word was: %s\n", targetWord);
    }
do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to recipe section");

	}
	while((c = getch()) =='\r');
	recipe();

}






char* wordLists[] = {"wonderland", "programming", "twilight", "algorithm", "enchanting", "smile", "moon","jubilant","aurora","sunshine"};

void playWordGuessingGame() {
    FILE *fp;
    char c;
    system("cls");
    main:
    srand(time(NULL));

    // Select a random word from the list
    int randomIndex = rand() % (sizeof(wordLists) / sizeof(wordLists[0]));
    char* targetWord = wordLists[randomIndex];

    int wordLength = strlen(targetWord);
    char guessedWord[MAX_WORD_LENGTH];
    strcpy(guessedWord, targetWord);  // Initialize guessedWord with the target word
    for (int i = 0; i < wordLength; ++i) {
        if (targetWord[i] != ' ') {
            guessedWord[i] = '_';  // Replace letters with underscores in the guessedWord
        }
    }

    int attempts = 0;
    char guessedLetters[MAX_WORD_LENGTH] = {'\0'};

    printf("Welcome to the Word Guessing Game!\n");
    printf("Try to guess the word.\n");

    do {
        printf("\nCurrent word: %s\n", guessedWord);
        printf("Guessed letters: %s\n", guessedLetters);
        printf("Attempts left: %d\n", MAX_ATTEMPTS - attempts);

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);  // Using a space before %c to consume any newline characters in the buffer

        if (strchr(guessedLetters, guess) != NULL) {
            printf("You've already guessed the letter '%c'. Try again.\n", guess);
        } else {
            guessedLetters[strlen(guessedLetters)] = guess;  // Add guessed letter to the list

            if (strchr(targetWord, guess) != NULL) {
                // Update guessedWord with the correctly guessed letter
                for (int i = 0; i < wordLength; ++i) {
                    if (targetWord[i] == guess) {
                        guessedWord[i] = guess;
                    }
                }
            } else {
                printf("Incorrect guess! Try again.\n");
                attempts++;
            }
        }

        // Check if the player guessed the entire word
        if (strcmp(guessedWord, targetWord) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", targetWord);
            break;
        }

    } while (attempts < MAX_ATTEMPTS);

    if (attempts == MAX_ATTEMPTS) {
        printf("\nSorry, you've reached the maximum number of attempts. The correct word was: %s\n", targetWord);
    }
do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to recipe section");

	}
	while((c = getch()) =='\r');
	recipe();

}






int rev() {FILE *fp;
    char c;int numReviews;
    system("cls");
    main:

    system("cls");
    printf("Enter the number of reviews: ");
    scanf("%d", &numReviews);

    if (numReviews <= 0 || numReviews > MAX_REVIEWS) {
        printf("Invalid number of reviews. Exiting.\n");
        return 1;
    }

    struct RatingReview reviews[MAX_REVIEWS];

    for (int i = 0; i < numReviews; i++) {
        printf("Enter your username: ");
        scanf(" %[^\n]", reviews[i].username);

        printf("Ratings for our service (between 1 and 5): ");
        scanf("%d", &reviews[i].rating);

        // Check if the rating is within the valid range
        if (reviews[i].rating < 1 || reviews[i].rating > 5) {
            printf("Invalid rating. Ratings must be between 1 and 5. Exiting.\n");
            return 1;
        }

        printf("Enter your review about our restaurant: ");
        scanf(" %[^\n]", reviews[i].review);  // Read the review until the newline character
    }

    printf("\nReviews and Ratings for the Restaurant:\n");
    for (int i = 0; i < numReviews; i++) {
        printf("Username: %s\n", reviews[i].username);
        printf("Rating: %d\n", reviews[i].rating);
        printf("Review: %s\n", reviews[i].review);
        printf("\n");
    }

    // Calculate and display the average rating
    int totalRating = 0;
    for (int i = 0; i < numReviews; i++) {
        totalRating += reviews[i].rating;
    }

    double averageRating = (double)totalRating / numReviews;

    printf("Average rating for the restaurant: %.2f\n", averageRating);
do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to main menu...");

	}
	while((c = getch()) =='\r');
	menu();
    return 0;
}




void login()
{

int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";
    do
{

    printf("\n  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb LOGIN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  ");
    printf(" \n                        USERNAME:-");
	scanf("%s", &uname);
	printf(" \n                        PASSWORD:-");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	//char code=pword;
	i=0;
	//scanf("%s",&pword);
		if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0)
	{
	printf("  \n\n\nWELCOME TO YUMTALES RESTAURENT !!!! LOGIN IS SUCCESSFUL");
	printf("\n\n SYSTEM IS LOADING. PLEASE WAIT... \n");
	printf("\n\n\n\t\tPress any key to continue...");
	getch();//holds the screen
	break;
	}
	else
	{
		printf("\nSORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		getch();//holds the screen

	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");

		getch();

		}
		system("cls");
		admin();
}







void menu(void)
{int num;
	int choice;
	system("cls");
	main:
	printf("\n                                                  %s****************************************************************%s\n",GREEN,RESET);
	printf("\n      \t\t\t\t\t\t\t\t\t%sYUMTALES RESTAURENT%s\t\t\t\t\t\t\t\n\n ",RED,RESET);
	printf("                                                 %s****************************************************************%s\n\n\n",GREEN,RESET);
    	printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    	printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    	printf("\t\t\t\t\t\t\t3. RECIPE BOOK-->\n");
    	printf("\t\t\t\t\t\t\t4. REVIEW-->\n");
    	printf("\t\t\t\t\t\t\t5. EXIT-->\n\n");
        printf("\n\n\t\t\t\t\t\tEnter your choice[1-5]");
	scanf("%i", &choice);

	system("cls");

	switch(choice)
	{
        case 1:
            login();
			admin();
			break;
		case 2:
			customer();
			break;
		case 3:
			games();
			break;
        case 4:
            rev();
            break;
		case 5:
		printf("System Exit");
		exit(0);
		break;


		default:
		printf("Invalid Choice! System Exit\n");
			getch();
	}

}







struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}







struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}





void displayList(struct node *head)
{
    struct node *temp1 = head;

    if (temp1 == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        printf("\t\t\t\t%-5s%-25s\t\t%s\n", "ID", "Food Name", "Price");
        printf("\t\t\t\t------------------------------------------------------\n");

        while (temp1 != NULL)
        {
            printf("\t\t\t\t%-5d%-25s\t\t%-12.2f\n", temp1->data, temp1->foodname, temp1->price);

            temp1 = temp1->next;
        }
        printf("\n");
    }
}











struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}









void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}









int deleteadmin()
{   printf("\t\t\t\t\t\t\t\t%sDELETING ITEMS%s\n\n",MAGENTA,RESET);
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=heada;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = delete(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}








int deletecustomer()
{   printf("\t\t\t\t\t\t\t\t%sDELETING ITEMS\n\n%s",MAGENTA,RESET);
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}







void displaybill()
{
    printf("\n\t\t\t\t\t\t\t\t\t ###%s Final Bill %s###\n",CYAN,RESET);

    struct node *temp = headc;
    float total_price = 0;
    int total_quantity = 0;

    printf("\t\t\t\t\t\t-------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t  %-5s%-25s%-10s%-10s%-15s\n", "No.", "Item", "Quantity", "Price","Total");
    printf("\t\t\t\t\t\t-------------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("\t\t\t\t\t\t  %-5d%-25s%-10d%-10.2f%-15.2f\n", temp->data, temp->foodname, temp->quantity, temp->price / temp->quantity,temp->price);
        total_price += temp->price;
        total_quantity += temp->quantity;
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t-------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t  %-40s%-10d%-15.2f\n", "Total", total_quantity, total_price);
    printf("\t\t\t\t\t\t-------------------------------------------------------------\n");
}








struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}









void admin()
{
    FILE *fp;
    char c;
    system("cls");
    main:
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t%s    ADMIN SECTION%s\n",CYAN,RESET);
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Back to main menu\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice ---> ");
	int opt;
	scanf("%d",&opt);
	system("cls");
        switch (opt)
        {
            case 1:
    calculatetotsales();
    printf("\n\t\t\t\t\t\t\t  ###%s Total Sales %s###\n",YELLOW,RESET);

    struct node *temp_s = head_s;

    if (temp_s == NULL)
    {
        printf("\n\t\t\t\t\t\t\tNo sales data available.\n");
    }
    else
    {
        printf("\n");
        printf("\t\t\t\t\t\t%-5s%-25s%-10s% -15s\n", "No.", "Item", "Quantity", "Profit");
        printf("\t\t\t\t\t\t-------------------------------------------\n");

        float totalProfit = 0.0;

        while (temp_s != NULL)
        {
            float profit = temp_s->price - (temp_s->quantity * temp_s->price);
            printf("\t\t\t\t\t\t%-5d%-25s%-10d%-15.2f\n", temp_s->data, temp_s->foodname, temp_s->quantity, profit);
            totalProfit += profit;
            temp_s = temp_s->next;
        }

        printf("\t\t\t\t\t\t-------------------------------------------\n");
        printf("\t\t\t\t\t\t%-40s%-  15.2f\n", "Total Profit", totalProfit);
        printf("\t\t\t\t\t\t-------------------------------------------\n");
        printf("\n");
    }
    break;


            case 2:
                printf("\t\t\t\t\t\t\t\t\t%sADDING ITEMS%s\n \n",MAGENTA,RESET);
                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\t\t\t\t\t\t\tEnter food item name: ");
                scanf("%s",name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            case 3:
                if(deleteadmin())
                {
                    printf("\n\t\t\t\t\t\t\t\t### %sUpdated list of food items menu%s ###\n",BLUE,RESET);
                    displayList(heada);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t\t   ###%s Order menu %s###\n",BLUE,RESET);
                displayList(heada);
                break;
            case 5:
                menu();
            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to admin section");

	}
	while((c = getch()) =='\r');
	admin();

}









void customer()
{FILE *fp;
    char c;
    int flag=0,j=1;
    char ch;
    system("cls");
    main:
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    %sCUSTOMER SECTION%s\n",CYAN,RESET);
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Track the order\n");
    printf("\t\t\t\t\t\t\t6. Back to main menu\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice: --->");

        int opt;char str[100];
        scanf("%d",&opt);
	system("cls");

        switch (opt)
        {
            case 1:
                printf("\t\t\t\t\t\t\t\t%sORDER SECTION%s\n",MAGENTA,RESET);
                displayList(heada);
 		int or_no=1;
		int order_no;
		printf("\n\t\t\t\t\t\tEnter number of items you want to order: ");
                scanf("%d",&order_no);
		for (int or_no=1;or_no<=order_no;or_no++)
		{
                printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("\t\t\t\t\t\tEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);}

                printf("\n\t\t\t\t\t\t%sORDER HAS BEEN PLACED SUCCESSFULLY!!!%s\n",MAGENTA,RESET);


                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ###%s List of ordered items%s ###\n",GREEN,RESET);
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n\t\t\t\t\t\t###%s Updated list of your ordered food items%s ###\n",GREEN,RESET);
                    displayList(headc);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();
                displaybill();
                headc = deleteList(headc);
                flag=1;
                break;
            case 5:
                printf("\t\t\t\t\t\t\t%sTracking the order%s\n",RED,RESET);
                printf("\n\t\t\t\t\t\tEnter your location (address): ");
                scanf(" %[^\n]", str);
                //printf("\n\t\t\t\t\t\t%sORDER HAS BEEN PLACED SUCCESSFULLY!!!%s\n",MAGENTA,RESET);
                printf("\n\t\t\t\t\t\t%sYOUR ORDER WILL BE DELIVERED WITHIN 15MINS%s\n",MAGENTA,RESET);
                Order myOrder;
    myOrder.orderId = 101;
    strcpy(myOrder.status, "Ordered");

    printf("Order Tracking :\n");
    printf("------------------------\n");

    displayOrder(myOrder);

    // Animation for "Ordered" status
    animateStatus("Ordered", 10);

    // Animation for "Shipped" status
    animateStatusTransition("Shipped", 10);

    // Update order status to "Shipped"
    updateOrderStatus(&myOrder, "Shipped");
    displayOrder(myOrder);

    // Animation for "Delivered" status
    animateStatusTransition("Delivered", 10);

    // Update order status to "Delivered"
    updateOrderStatus(&myOrder, "Delivered");
    displayOrder(myOrder);
                printf("\n\t\t\t\t\t\t%sTHANK YOU!!!%s\n",MAGENTA,RESET);

                break;

            case 6:
                menu();

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }

do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to customer section");

	}
	while((c = getch()) =='\r');
	customer();

}










void recipe() {
FILE *fp;
    char c;
    system("cls");
    main:
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    %sRECIPE SECTION%s\n",CYAN,RESET);
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t%s1. Non Vegetarian%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s2. Vegetarian%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s3. Noodles & Soup%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s4. Juice%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s5. Desserts%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s6. Back to main menu%s\n",YELLOW, RESET);
    printf("\t\t\t\t\t\t\tEnter your choice to view the recipe:");

    int opt;
    scanf("%d", &opt);
    system("cls");
    switch (opt) {
        case 1:
            printf("\t\t\t\t\t\t\t\t\t%sTINY TUMMY TREATS%s\n\n",GREEN,RESET);
            printf("\033[31mChicken Sandwich:\033[0m\n\n");
			printf("\033[36mIngredients:\033[0m\n\n");
			printf("\033[35mFor the Marinade:\033[0m\n");
			printf("4 small-medium organic chicken breast,1/2 cup dill pickle juice,1/3 cup cold water\n");
			printf("\033[35mFor coating:\033[0m\n");
			printf("1/2 cup milk,1 large egg,1 cup all-purpose flour,2 tablespoons confectioners' sugar,1/2 teaspoon baking powder,1/2 teaspoon paprika,1 teaspoon freshly ground black pepper,1/2 teaspoon chili powder,1/2 teaspoon sea salt\n");
			printf("\033[35mFor the Chick-fil-A Special Sauce:\033[0m\n");
			printf("1/2 cup mayonnaise,1 teaspoons dijon mustard,2 teaspoons yellow mustard,2 teaspoon smoky barbecue sauce,1 1/2 tablespoons honey,1 1/2 teaspoons freshly squeezed lemon juice,1/2 teaspoon garlic powder,1/2 teaspoon paprika,1/4 teaspoon salt\n");
			printf("\033[35mFor the Sandwich:\033[0m\n");
			printf("4 standard size hamburger buns, lightly toasted,2 tablespoons salted butter,Iceberg lettuce,1 beefsteak tomato,sliced,Dill pickle slices,peanut oil, for frying.\n\n");
			printf("\033[33mPreparation:\033[0m\n\n");
			printf("1.For the Marinate: Place the pickle juice and water in a shallow glass dish. Add the chicken breast and marinate in the refrigerator for 30 minutes rotating once.\n");
			printf("2.For the Coating: In a small another mixing bowl add the milk and egg and blend well. Set aside.\n");
			printf("3.In a larger mixing bowl add the flour, confectioners  sugar, baking powder, paprika, black pepper, chili powder and salt.Mix well and set aside for later.\n");
			printf("4.For the Special Sauce: In another small mixing bowl (or glass jar) add the mayonnaise, dijon mustard, yellow mustard, barbecue sauce, honey, lemon juice, garlic powder, paprika and salt. Mix to blend and refrigerate until needed.\n");
			printf("5.In a medium saucepan add about 2 cups peanut oil and place over a medium high flame. Using an instant read thermometer, heat oil to 350 degrees F. Line a baking sheet with paper towels and set near your work station.\n\n");

			printf("%sBaked Lemon Garlic Chicken:%s\n\n", RED, RESET);
			printf("%sIngredients%s:\n\n4 boneless, skinless chicken breasts\n"
"1 pound baby potatoes, halved\n"
"1 cup baby carrots\n"
"1 cup broccoli florets\n"
"4 cloves garlic, minced\n"
"1 lemon, sliced\n"
"3 tablespoons olive oil\n"
"1 teaspoon dried thyme\n"
"1 teaspoon dried rosemary\n"
"Salt and black pepper to taste\n"
"Fresh parsley for garnish (optional)\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.Preheat your oven to 400 F (200 C).\n"
"2.Season chicken breasts with salt, black pepper, dried thyme, and dried rosemary on both sides.\n"
"3.In a large mixing bowl, toss the halved baby potatoes, baby carrots, and broccoli florets with minced garlic and olive oil. Season with salt and pepper.\n"
"4.Place the seasoned chicken breasts on one side of a baking sheet and arrange the seasoned vegetables on the other side. Distribute lemon slices over the chicken and vegetables.\n"
"5.Bake in the preheated oven for 25-30 minutes or until the chicken is cooked through and the vegetables are tender. Make sure the internal temperature of the chicken reaches 165 F (74 C).\n"
"6.Garnish with fresh parsley if desired. Serve the baked lemon garlic chicken over the roasted vegetables.\n"
"7.Enjoy your easy and delicious one-pan meal!\n\n",YELLOW,RESET);

printf("%sGarlic Butter Chicken:%s\n\n", RED, RESET);
			printf("%sIngredients%s:\n\n4 boneless, skinless chicken breasts\n"
"1 pound (450g) baby potatoes, halved\n"
"1 cup baby carrots\n"
"1 cup broccoli florets\n"
"4 tablespoons unsalted butter, melted\n"
"4 cloves garlic, minced\n"
"1 teaspoon dried thyme\n"
"Salt and black pepper to taste\n"
"Fresh parsley for garnish (optional)\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.Preheat your oven to 400 F (200 C).\n"
"2.Season chicken breasts with salt and black pepper on both sides.\n"
"3.In a large mixing bowl, toss the halved baby potatoes, baby carrots, and broccoli florets with melted butter, minced garlic, dried thyme, salt, and black pepper.\n"
"4.Place the seasoned chicken breasts on a baking sheet. Arrange the seasoned vegetables around the chicken.\n"
"5.Bake in the preheated oven for 25-30 minutes or until the chicken is cooked through and the vegetables are tender.\n"
"6.Garnish with fresh parsley if desired. Serve the garlic butter chicken over the roasted vegetables.\n"
"7.Enjoy this simple and delicious one-pan meal!\n\n",YELLOW,RESET);

            break;
        case 2:
            printf("\t\t\t\t\t\t\t\t\t%sTINY TUMMY TREATS%s\n\n",GREEN,RESET);
            printf("%sFried Rice:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n2 cups cooked rice\n"
                   "1 cup mixed vegetables (peas, carrots, corn)\n"
                   "1/2 cup diced tofu or cooked chicken\n"
                   "2 eggs, beaten\n"
                   "3 tablespoons soy sauce\n"
                   "1 tablespoon oil\n"
                   "1/2 cup spring onions, chopped\n"
                   "Salt and pepper to taste\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n"
                   "1.Heat oil in a pan, add mixed vegetables and tofu or chicken. Cook until tender.\n"
"2.Push the vegetables to the side and pour beaten eggs into the pan. Scramble until cooked.\n"
"3.Add cooked rice and soy sauce. Mix well.\n"
"4.Stir in spring onions and season with salt and pepper.\n"
"5.Cook for a few more minutes, stirring continuously.\n\n",YELLOW,RESET);
printf("\033[31mPenne Pasta,Peas and Bacon:\033[0m\n\n");
			printf("\033[36mIngredients%s:\033[0m\n\n");
			printf("tablespoon olive oil,1/2 diced very small yellow onion,1 cup frozen peas,6 thick slices cut into small slices bacon,3/4 pound penne pasta,1/4 cup heavy cream\n\n");
			printf("\033[33mPreparation:\033[0m\n\n");
			printf("1.Bring a large pot of salted water to a boil and add the pasta.Halfway thru cooking the pasta,refer to package cooking instructions, add the frozen peas to the water\n");
			printf("2.Meanwhile, in a large skillet,add the olive oil over medium-high, and add the finely diced onions and the bacon.Cook until the bacon and onions are crisp but not burned.\n");
			printf("3.Drain the pasta and peas and add them to the onion bacon mixture. Lower the heat to medium and add the heavy cream.\n");
			printf("4.Stir well, add more cream if needed and serve immediately.\n\n");

            printf("%sVegetable Stir Fry:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n2 cups mixed vegetables (broccoli florets, bell peppers, carrots, snap peas, etc.), chopped\n"
"2 tablespoons vegetable oil\n"
"2 cloves garlic, minced\n"
"1 teaspoon ginger, grated\n"
"1 tablespoon soy sauce\n"
"1 tablespoon oyster sauce (optional)\n"
"1 teaspoon sesame oil\n"
"Salt and pepper to taste\n"
"Cooked rice or noodles for serving\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.Wash and chop the mixed vegetables into bite-sized pieces.\n"
"2.Heat vegetable oil in a large pan or wok over medium-high heat.\n"
"3.Add minced garlic and grated ginger to the hot oil. Saut  for about 30 seconds until fragrant.\n"
"4.Add the chopped mixed vegetables to the pan. Stir-fry for 3-5 minutes or until they are slightly tender but still crisp.\n"
"5.In a small bowl, mix soy sauce, oyster sauce (if using), and sesame oil. Pour the sauce over the vegetables and toss to coat evenly. Season with salt and pepper to taste.\n"
"6.Continue to stir-fry for an additional 2-3 minutes until the vegetables are cooked to your liking. Be careful not to overcook; you want them to remain slightly crunchy.\n"
"7.Serve the vegetable stir-fry over cooked rice or noodles.\n"
"8.Enjoy this simple and nutritious vegetable stir-fry as a standalone dish or as a side to your favorite main course.\n\n",YELLOW,RESET);
            break;
        case 3:
            printf("\t\t\t\t\t\t\t\t\t%sTINY TUMMY TREATS%s\n\n",GREEN,RESET);
            // Recipe for Hakka Noodles
            printf("%sHakka Noodles:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n200g Hakka noodles\n"
                   "2 tablespoons oil\n"
                   "1 tablespoon ginger-garlic paste\n"
                   "1 cup mixed vegetables (carrots, beans, bell peppers)\n"
                   "2 tablespoons soy sauce\n"
                   "1 tablespoon chili sauce\n"
                   "1 tablespoon vinegar\n"
                   "Salt and pepper to taste\n"
                   "Spring onions for garnish\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n"
                   "1.Boil Hakka noodles according to package instructions. Drain and set aside.\n"
"2.Heat oil in a wok, add ginger-garlic paste and saut .\n"
"3.Add mixed vegetables and stir-fry until slightly tender.\n"
"4.Toss in the cooked noodles, soy sauce, chili sauce, and vinegar. Mix well.\n"
"5.Season with salt and pepper. Garnish with spring onions before serving.\n\n",YELLOW,RESET);
            printf("%s Hot and Sour Soup:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n4 cups chicken or vegetable broth\n"
                   "1 cup tofu, diced\n"
                   "1/2 cup bamboo shoots, sliced\n"
                   "1/2 cup wood ear mushrooms, soaked and sliced\n"
                   "1/4 cup soy sauce\n"
                   "2 tablespoons rice vinegar\n"
                   "1 tablespoon sesame oil\n"
                   "1 teaspoon sugar\n"
                   "1/2 teaspoon white pepper\n"
                   "2 tablespoons cornstarch, dissolved in water\n"
                   "2 eggs, beaten\n"
                   "Green onions, chopped, for garnish\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.In a pot, bring the broth to a simmer.\n2.Add tofu, bamboo shoots, and mushrooms. Cook for 5 minutes.\n3.Stir in soy sauce, rice vinegar, sesame oil, sugar, and white pepper.\n4.Slowly pour in the cornstarch mixture, stirring continuously to thicken the soup.\n5.Pour beaten eggs into the soup, stirring gently to create ribbons.\n6.Garnish with chopped green onions before serving.\n\n",YELLOW,RESET);

            // Recipe for Manchow Soup
            printf("%sManchow Soup:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n2 tablespoons oil\n"
                   "1 tablespoon garlic, minced\n"
                   "1 tablespoon ginger, grated\n"
                   "1/4 cup cabbage, shredded\n"
                   "1/4 cup carrots, julienned\n"
                   "1/4 cup bell peppers, chopped\n"
                   "1/4 cup spring onions, chopped\n"
                   "1/4 cup mushrooms, sliced\n"
                   "2 tablespoons soy sauce\n"
                   "1 tablespoon vinegar\n"
                   "1 tablespoon chili sauce\n"
                   "1 tablespoon cornflour, dissolved in water\n"
                   "4 cups vegetable or chicken broth\n"
                   "Salt and pepper to taste\n"
                   "Spring onions for garnish\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n"
                   "1.Heat oil in a pan and saut  garlic and ginger.\n"
"2.Add vegetables and stir-fry for a few minutes.\n"
"3.Pour in soy sauce, vinegar, and chili sauce. Mix well.\n"
"4.Add broth and bring to a boil. Season with salt and pepper.\n"
"5.Slowly pour in the cornflour mixture, stirring until the soup thickens.\n"
"6.Garnish with spring onions before serving.\n\n",YELLOW,RESET);
            // Recipe for Manchurian Noodles
            printf("%s Manchurian Noodles:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n\n200g Hakka noodles\n"
                   "1 cup vegetable Manchurian balls\n"
                   "2 tablespoons soy sauce\n"
                   "1 tablespoon chili sauce\n"
                   "1 tablespoon vinegar\n"
                   "1 tablespoon oil\n"
                   "1 onion, thinly sliced\n"
                   "1 bell pepper, thinly sliced\n"
                   "2 cloves garlic, minced\n"
                   "Salt and pepper to taste\n"
                   "Spring onions for garnish\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n"
                   "1.Heat oil in a wok, add garlic, and stir-fry.\n"
"2.Add sliced onions and bell peppers, cook until slightly tender.\n"
"3.Add Manchurian balls, soy sauce, chili sauce, and vinegar. Mix well.\n"
"4.Toss in cooked noodles, stir until everything is well combined.\n"
"5.Season with salt and pepper. Garnish with spring onions.\n\n",YELLOW,RESET);
            break;
        case 4:
            printf("\t\t\t\t\t\t\t\t\t%sTINY TUMMY TREATS%s\n\n",GREEN,RESET);
            // Recipe for Fried Rice
            printf("\033[31mHealthy Fruit Juice:\033[0m\n\n");
			printf("\033[36mIngredients:\033[0m\n\n");
			printf("1 cup pomegranate seeds,1 cup grapefruit,2 tablespoon lemon juice,1 tablespoon honey,1/2 cup water,1 orange,1 mango,1/2 cup ice cubes,2 sprigs mint leaves,\n\n");
			printf("\033[33mPreparation:\033[0m\n\n");
			printf("1.Wash, peel & chop the fruits.To prepare this healthy fruit juice, wash all the fruits properly and peel and chop them if required.\n");
			printf("2.Blend the fruits with water, ice cubes, lemon juice & honey.Add them to a food processor with water, lemon juice, ice cubes and honey and blend them together.\n");
			printf("3.Strain Homemade Fruit Juice into glasses!\n");
			printf("4.Then, pour the juice into a chilled glass using a strainer to remove the pulp. Garnish with mint leaves and serve.\n\n");
printf("%s Cucumber Mint Lemonade:%s\n\n", RED, RESET);
            printf("%sIngredients:%s\n\n1 large cucumber, peeled and sliced\n"
"1/4 cup fresh mint leaves, loosely packed\n"
"Juice of 3-4 lemons (about 1 cup)\n"
"1/2 cup honey or simple syrup (adjust to taste)\n"
"4 cups cold water\n"
"Ice cubes\n"
"Lemon slices and mint leaves for garnish (optional)\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.Peel the cucumber and slice it into rounds. Pick fresh mint leaves.\n"
"2.In a blender, combine cucumber slices, mint leaves, and lemon juice. Blend until you get a smooth mixture.\n"
"3.Add honey or simple syrup to the blender. Adjust the sweetness to your liking. Blend again to incorporate.\n"
"4.If you prefer a smoother juice, you can strain the mixture using a fine mesh sieve or cheesecloth to remove pulp. This step is optional.\n"
"5.In a large pitcher, combine the cucumber-mint-lemon mixture with cold water. Stir well to combine.\n"
"6.Refrigerate the lemonade for at least 1-2 hours to allow the flavors to meld.\n"
"7.Pour the cucumber mint lemonade over ice cubes in glasses.\n"
"8.Garnish with lemon slices and mint leaves for a decorative touch.\n\n",YELLOW,RESET);
printf("%sOrange Carrot Ginger Juice:%s\n\n", RED, RESET);
printf("%sIngredients:%s\n\n4 large carrots, peeled and chopped\n"
"3 oranges, peeled and segmented\n"
"1-inch piece of fresh ginger, peeled\n"
"1-2 tablespoons honey (optional, for sweetness)\n"
"Ice cubes (optional)\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.Peel and chop the carrots. Peel and segment the oranges. Peel the ginger.\n"
"2.In a juicer, combine the chopped carrots, orange segments, and peeled ginger. Juice the ingredients according to your juicer's instructions.\n"
"3.Taste the juice and add honey if you prefer a sweeter flavor. Blend again to incorporate the sweetness.\n"
"4.If you want a smoother juice, you can strain the mixture using a fine mesh sieve or cheesecloth to remove pulp. This step is optional.\n"
"5.Refrigerate the juice for a short time or serve immediately over ice cubes.\n"
"6.Pour the orange carrot ginger juice into glasses.\n\n",YELLOW,RESET);
            break;
        case 5:
            printf("\t\t\t\t\t\t\t\t\t%sTINY TUMMY TREATS%s\n\n",GREEN,RESET);
            printf("\033[31mChocolate Snowballs:\033[0m\n\n");
			printf("\033[36mIngredients:\033[0m\n\n");
			printf("1 (11-ounce) box vanilla wafers,3/4 cup confectioners sugar, plus more for rolling,2 tablespoons unsweetened cocoa powder,1/4 cup mini dark chocolate chips, or finely chopped dark chocolate,2 tablespoons maple syrup,1/3 cup plus 1 tablespoon dark rum, plus more as needed\n\n");
			printf("\033[33mPreparation:\033[0m\n\n");
			printf("1.Combine vanilla wafers, powdered sugar, cocoa powder, and chocolate chips in a food processor. Pulse on and off until mixture is finely ground.\n");
			printf("2.Add maple syrup and rum. Pulse until mixture comes together to form a stiff, but moldable dough. If mixture is too dry to scoop and roll balls, add more rum, a little at a time, and pulse again, until the proper texture is reached.\n");
			printf("3.Scoop out portions of dough and roll into smooth balls. The ideal size is between 1 and 1 1/2 inches. Place on a plate; cover with plastic wrap and refrigerate while you prepare the white chocolate coating.\n");
			printf("4.Wrap and refrigerate until needed. Rum balls are best made ahead and left to  age.  Can be made a week or more ahead, as long as they are kept tightly wrapped.\n\n");
printf("%sStrawberry Cheese Cupcakes:%s\n\n", RED, RESET);
printf("%sIngredients:%s\n\n 1/2 cups graham cracker crumbs\n"
"1/3 cup melted butter\n"
"1 cup cream cheese, softened\n"
"1/2 cup powdered sugar\n"
"1 teaspoon vanilla extract\n"
"1 cup whipped cream\n"
"Fresh strawberries for topping\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.In a bowl, combine graham cracker crumbs and melted butter. Press this mixture into the base of serving cups.\n"
"2.In a separate bowl, beat together softened cream cheese, powdered sugar, and vanilla extract until smooth.\n"
"3.Gently fold in the whipped cream until well combined.\n"
"4.Spoon the cheesecake mixture over the graham cracker crust in each serving cup.\n"
"5.Refrigerate the cheesecake cups for at least 2-3 hours to set.\n"
"6.Before serving, top each cheesecake cup with fresh strawberries.\n\n",YELLOW,RESET);
            printf("%sChocolate Chip Cookies:%s\n\n", RED, RESET);
printf("%sIngredients:%s\n\n1 cup (2 sticks) unsalted butter, softened\n"
"1 cup granulated sugar\n"
"1 cup packed brown sugar\n"
"2 large eggs\n"
"1 teaspoon vanilla extract\n"
"3 cups all-purpose flour\n"
"1 teaspoon baking soda\n"
"1/2 teaspoon baking powder\n1/2 teaspoon baking powder\n"
"1/2 teaspoon salt\n2 cups chocolate chips\n\n",CYAN,RESET);
            printf("%sPreparation:%s\n\n1.Preheat your oven to 350 F (175 C).In a large bowl, cream together the softened butter, granulated sugar, and brown sugar until light and fluffy.\n"
"2.Beat in the eggs one at a time, then stir in the vanilla extract.\n"
"3.In a separate bowl, whisk together the flour, baking soda, baking powder, and salt.\n"
"4.Gradually add the dry ingredients to the wet ingredients, mixing until just combined.\n"
"5.Gently fold in the chocolate chips until evenly distributed throughout the dough.\n"
"6.Drop rounded tablespoons of dough onto ungreased baking sheets.\n\n"
"7.Bake in the preheated oven for 10-12 minutes or until the edges are golden brown.\n"
"8.Allow the cookies to cool on the baking sheets for a few minutes before transferring them to wire racks to cool completely.\n\n",YELLOW,RESET);
            break;
        case 6:
                menu();
        default:
            printf("Invalid Choice!\n");
    }
do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to recipe section");
}
while((c = getch()) =='\r');
recipe();
}








void games(){
    FILE *fp;
    char c;int opt;
    system("cls");
    main:
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    %s:) FUN TIME :)%s\n",CYAN,RESET);
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t%s1. :)Guess the number%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s2. :)Guess the recipe%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s3. :)Guess the word%s\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t%s4. :)Back to main menu%s\n\n", YELLOW, RESET);
    printf("\t\t\t\t\t\t\t:)Play the games to view the recipes:)\n\n ");
    printf("\t\t\t\t\t\t\tEnter your choice to play the game: ");

    scanf("%d", &opt);
    system("cls");
    switch (opt) {
        case 1:
            playGuessingGame();
            break;
        case 2:
            playRecipeGame();
            break;
        case 3:
            playWordGuessingGame();
            break;
        case 4:
            menu();
        default:
            printf("Invalid Choice!\n");
do{
fp=fopen("NextFile.dat","a");
printf("\nPress any other key to go to main menu");
}
while((c = getch()) =='\r');
menu();
}
}








int main()
{
    heada = createadmin(heada,1,"Chicken Sandwich",120);
    heada = createadmin(heada,2,"Baked Lemon Garlic Chicken",200);
    heada = createadmin(heada,3,"Garlic Butter Chicken",150);
    heada = createadmin(heada,4,"Fried Rice",70);
    heada = createadmin(heada,5,"Penne Pasta,Peas and Bacon",80);
    heada = createadmin(heada,6,"Vegetable Stir Fry",50);
    heada = createadmin(heada,7,"Hakka Noodles",60);
    heada = createadmin(heada,8,"Hot and Sour Soup",75);
    heada = createadmin(heada,9,"Manchow Soup",65);
    heada = createadmin(heada,10,"Manchurian Noodles",85);
    heada = createadmin(heada,11,"Healthy Fruit Juice",25);
    heada = createadmin(heada,12,"Cucumber Mint Lemonade",30);
    heada = createadmin(heada,13,"Orange Carrot Ginger Juice",25);
    heada = createadmin(heada,14,"Chocolate Snowballs",80);
    heada = createadmin(heada,15,"Strawberry Cheese Cupcakes",100);
    heada = createadmin(heada,16,"Chocolate Chip Cookies",85);

    while(1)
    {   
        menu();
        int choice;
        scanf("%d",&choice);

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                games();
                break;
            case 4:
		printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
                break;
            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}











