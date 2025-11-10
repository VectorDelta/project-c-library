/*
    This is about a library where time is the main management dogma
    - Developer's entry

    BTW THIS IS ALL MADE BY ME(yes): V I T O R   L E N N O N  L I M A  D A  C O S T A
*/

/*
                                  
                                  ///--------------\\\
    SILLY STORIES:                \\\--------------///

    We're running low on digital infrastructure resources! We have to use C, oh noes!
    By the way, I'm quite worried about the time that the books would be retrieved, so please
    make it works with a time based management!

    - The poor Library Manager running on Macintosh and TCP without cryptography.
*/
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define DEFAULT "\033[37m"

typedef struct
{
    char isbn[50];
    char title[50];
    char author[20];
    char sect[10];
    int year;

    char patron[20];
    int time_for_retrieval;
    int status;
} Book;
int bookCount;

void ReceiveBookInput();

int main()
{
    Book shelf[50];
    char input;

    printf("o============================o\n");
    printf("|                            |\n");
    printf("|          > MENU <          |\n");
    printf("|                            |\n");
    printf("|     [B]ook leaning         |\n");
    printf("|     [H]elp                 |\n");
    printf("|     [E]xit the Libray      |\n");
    printf("|     [A]dd Book             |\n");
    printf("|                            |\n");
    printf("|                            |\n");
    printf("o============================o\n");

    input = getchar();

    switch (toupper(input))
    {
    case 'B':
        printf("Success!");

    default:
        printf("%c", input);
    }
}

void ReceiveBookInput()
{
    char isbn[50];
    char title[50];
    char author[20];
    char sect[10];
    char safe_time[20];
    int time;

    printf("Please insert the ISBN identifier for the book.\n > ");
    fgets(isbn, sizeof(isbn), stdin);
    printf("Now insert the Title of the new book:\n > ");
    fgets(title, sizeof(title), stdin);
    printf("Now insert the library sector where this book will be stored:\n > ");
    fgets(sect, sizeof(sect), stdin);
    printf("Now insert the name of the author:\n > ");
    fgets(author, sizeof(author), stdin);
    printf("Now insert the year of the publication.");
    fgets(safe_time, sizeof(safe_time), stdin);
    time = (int)strtol(safe_time, NULL, 10);
}

Book SetBook(char isbn[50], char title[50], char author[20], char sect[10])
{
}