#include <stdio.h>
#include <stdlib.h>

#define RED "\033[31m"
#define DEFAULT "\033[37m"
#define GREEN "\033[32m"

typedef struct
{
    char index[50];
    char title[50];
    char author[20];
    char sect[10];
    int year;

    int status;
    char patron[20];
    int time_for_retrieval;
    int status; // 1 for available, 0 for loaned
} Book;
int bookCount;

// SMALL LIBRARY FOR SMALL PCS
Book shelf[50];    
int bookCount = 0; 

// PROTÓTIPOS DE FUNÇÃO
void AddBook();
void ListBooks();
Book SetBook(char index[50], char title[50], char author[20], char sect[10], int year);

int main()
{
    Book shelf[50];
    char input;

    printf("o============================o\n");
    while (1)
    {
        printf("\no============================o\n");
        printf("|                            |\n");
        printf("|          > MENU <          |\n");
        printf("|                            |\n");
        printf("|     [B]ook leaning         |\n");
        printf("|     [H]elp                 |\n");
        printf("|     [E]xit the Libray      |\n");
        printf("|     [A]dd Book             |\n");
        printf("|     [A]dd a new book       |\n");
        printf("|     [L]ist all books       |\n");
        printf("|     [E]xit the Library     |\n");
        printf("|                            |\n");
        printf("|                            |\n");
        printf("o============================o\n");
        printf(" > ");

        input = getchar();
        while (getchar() != '\n')
            ;

        switch (toupper(input))
        {
        case 'B':
            printf("Success!");

        case 'A':
            AddBook();
            break;
        case 'L':
            ListBooks();
            break;
        case 'E':
            printf("Goodbye!\n");
            return 0; // Exit the program
        default:
            printf("%c", input);
            printf(RED "Invalid option, please try again.\n" DEFAULT);
        }
    }

}

void AddBook()
{
    if (bookCount >= 50)
    {
        printf(RED "The shelf is full! Cannot add more books.\n" DEFAULT);
        return;
    }

    char index[50];
    char title[50];
    char author[20];
    char sect[10];
    char safe_time[20];
    int time;
    char year_str[10];
    int year;

    printf("Please insert the Index for the book:\n > ");
    fgets(index, sizeof(index), stdin);
    printf("Now insert the Title of the new book:\n > ");
    fgets(title, sizeof(title), stdin);
    printf("Now insert the library sector where this book will be stored:\n > ");
    fgets(sect, sizeof(sect), stdin);
    printf("Now insert the author of the book:\n > ");
    fgets(author, sizeof(author), stdin);
    printf("Now insert the library section for this book:\n > ");
    fgets(sect, sizeof(sect), stdin);
    printf("Finally, insert the year of publication:\n > ");
    fgets(year_str, sizeof(year_str), stdin);
    year = atoi(year_str); // Convert string to integer

    // Create the book and add it to our shelf
    shelf[bookCount] = SetBook(index, title, author, sect, year);
    bookCount++;

    printf(GREEN "\nBook added successfully!\n" DEFAULT);
}

void ListBooks()
{
    if (bookCount == 0)
    {
        printf(RED "\nThere are no books on the shelf.\n" DEFAULT);
        return;
    }

    printf("\n--- List of All Books ---\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("Book #%d\n", i + 1);
        printf("  Title: %s", shelf[i].title);
        printf("  Author: %s", shelf[i].author);
        printf("  Index: %s", shelf[i].index);
        printf("  Section: %s", shelf[i].sect);
        printf("  Year: %d\n", shelf[i].year);
        printf("  Status: %s\n", shelf[i].status == 1 ? "Available" : "Loaned");
        printf("---------------------------\n");
    }
}

Book SetBook(char index[50], char title[50], char author[20], char sect[10], int year)
{
    Book new_book;
    strcpy(new_book.author, author);
    strcpy(new_book.sect, sect);
    new_book.year = year;
    new_book.status = 1;

    strtok(new_book.index, "\n");
    strtok(new_book.title, "\n");
    strtok(new_book.author, "\n");
    strtok(new_book.sect, "\n");

    return new_book;
}