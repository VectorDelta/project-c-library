#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define RED "\033[31m"
#define DEFAULT "\033[37m"
#define GREEN "\033[32m"


// THE AMAZING WORLD OF MAGICAL NUMBERS! TOO MUCH TO HANDLE SO I'LL KEEP IT LIKE THT LOL
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
} Book;

Book shelf[50];    
int bookCount = 0; 

void AddBook();
void ListBooks();
void LoanBook();
void SaveLibrary();
void LoadLibrary();

Book SetBook(char index[50], char title[50], char author[20], char sect[10], int year);

int main()
{
    char input;

    while (1)
    {
        printf("\no============================o\n");
        printf("|                            |\n");
        printf("|            MENU            |\n");
        printf("|                            |\n");
        printf("|     [B]ook Leanding        |\n");
        printf("|     [H]elp                 |\n");
        printf("|     [E]xit the Libray      |\n");
        printf("|     [A]dd Book             |\n");
        printf("|     [L]ist all books       |\n");
        printf("|     [S]ave library         |\n");
        printf("|  Loa[D] Library            |\n");
        printf("o============================o\n");
        printf(" > ");

        input = getchar();
        while (getchar() != '\n')
            ;

        switch (toupper(input))
        {
        case 'B':
            LoanBook();
            break;
        case 'D':
            LoadLibrary();
            break;
        case 'A':
            AddBook();
            break;
        case 'H':
            printf("To use the Library's terminal, as you've used to open this HELP manual, input the\n \
                characters as specified on uppercase");
            break;
        case 'L':
            ListBooks();
            break;
        case 'S':
            SaveLibrary();
            break;
        case 'E':
            printf("Goodbye!\n");
            return 0;
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
    printf("Finally, insert the year of publication:\n > ");
    fgets(year_str, sizeof(year_str), stdin);
    year = atoi(year_str);

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

    memset(&new_book, 0, sizeof(Book));
    strcpy(new_book.author, author);
    strcpy(new_book.sect, sect);
    strcpy(new_book.title, title);
    strcpy(new_book.index, index);
    new_book.year = year;

    new_book.status = 1;

    strtok(new_book.index, "\n");
    strtok(new_book.title, "\n");
    strtok(new_book.author, "\n");
    strtok(new_book.sect, "\n");

    return new_book;
}

void LoanBook() {
    int bookID;
    char inputBuffer[10];

    ListBooks(); 

    if (bookCount == 0) return;

    printf("\nEnter the Book Number you want to borrow: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    bookID = atoi(inputBuffer);

    if (bookID < 1 || bookID > bookCount) {
        printf(RED "OUT OF BOUNDS BOOK!\n" DEFAULT);
        return;
    }

    Book *targetBook = &shelf[bookID - 1];

    if (targetBook->status == 0) {
        printf(RED "Sorry, '%s' is already loaned to %s.\n" DEFAULT, targetBook->title, targetBook->patron);
        return;
    }
    printf("Who is borrowing this book? ");
    fgets(targetBook->patron, sizeof(targetBook->patron), stdin);
    strtok(targetBook->patron, "\n");
    targetBook->status = 0;

    printf(GREEN "Success! '%s' has been loaned to %s.\n" DEFAULT, targetBook->title, targetBook->patron);
}

void SaveLibrary() {
    // START YELLING
    FILE *fptr = fopen("library_data.txt", "w");

    if (fptr == NULL) {
        printf(RED "CANNOT OPEN THE FILE!\n" DEFAULT);
        return;
    }

    for (int i = 0; i < bookCount; i++) {

        fprintf(fptr, "%s|%s|%s|%s|%d|%d|%s\n",
                shelf[i].index,
                shelf[i].title,
                shelf[i].author,
                shelf[i].sect,
                shelf[i].year,
                shelf[i].status,
                shelf[i].patron);
    }

    fclose(fptr);

    printf(GREEN "PROGRAM STREAM CLOSED/WRITTEN TO THE DISK!\n" DEFAULT);
}

void LoadLibrary()
{
    FILE *fptr = fopen("library_data.txt", "r");
    printf(GREEN "TXT READ\n" DEFAULT);

    bookCount = 0;

    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        if (bookCount >= 50) break;

        char *index = strtok(buffer, "|");
        char *title = strtok(NULL, "|");
        char *author = strtok(NULL, "|");
        char *sect = strtok(NULL, "|");
        char *year_str = strtok(NULL, "|");
        char *status_str = strtok(NULL, "|");
        char *patron = strtok(NULL, "\n"); 

        
        strcpy(shelf[bookCount].index, index);
        strcpy(shelf[bookCount].title, title);
        strcpy(shelf[bookCount].author, author);
        strcpy(shelf[bookCount].sect, sect);

        shelf[bookCount].year = atoi(year_str);
        shelf[bookCount].status = atoi(status_str);

        if (patron != NULL) {
            strcpy(shelf[bookCount].patron, patron);
        } else {
            strcpy(shelf[bookCount].patron, "");
        }

        bookCount++;
    }

    fclose(fptr);
    printf(GREEN "Stream closed and the things got saved. %d files written.\n" DEFAULT, bookCount);
}