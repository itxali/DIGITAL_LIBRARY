                                    //MUHAMMAD ALI
                                    //20MDELE109
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define IN 1
#define OUT 0

void Addbook();
void Searchbook();
void Displaybook();
void Exit();

char info[500];

struct
{
    int bid;
    char bname[25];
    char author[25];
    int nooftitles;
    char titles[500];
    int status;
} book;

struct
{
    int mid;
    char mname[25];
    char department[25];
    int availibcard;
    int phno;

} membr;

//initializing the files used in the program

FILE *librecord;
FILE *membrrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;

int main()
{
    int choice = 0, i;

    printf("\n\t\t<<DIGITAL LIBRARY MANAGEMENT SYSTEM>>\n");
    do
    {
        printf("\n\t********MENU***********\n 1> Add A New Book\n 2> Search a book\n 3> Exit\n\n");
        printf("Enter your OPTION:\n");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            Addbook();
            break;
        case 2:
            Searchbook();
            break;
        case 3:
            Exit();
        default:
            printf(" ! Invalid Input...\n");
        }
    } 
    while (choice != 10);

    return (0);
}

void Addbook()
{
    int i;
    book.status = IN;
    //opening the librecord file
    librecord = fopen("librecord.txt", "a+");
    printf("Enter The uniqueid of The Book :(Integer) \n");
    scanf("%d", &book.bid);
    printf("Enter The Name of The Book :\n");
    scanf("%s", book.bname);
    printf("Enter The Name of Author :\n");
    scanf("%s", book.author);
    printf("Enter The Number of Titles Of The Book:(Integer)\n");
    scanf("%d", &book.nooftitles);
    fprintf(librecord, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
    printf("Enter The Titles Of The Book : \n");
    for (i = 0; i < book.nooftitles; i++)
    {
        scanf("%s", book.titles);
        fprintf(librecord, "%s\t", book.titles);
    }
    fclose(librecord);
    printf(" (' ' ) A New Book has been Added Successfully...\n");
}

void Displaybook()
{
    librecord = fopen("librecord.txt", "a+");
    printf("\nBookid\tName\tAuthor\tStatus\tNo.\tTitles\n", info);
    do
    {
        fgets(info, 500, librecord);
        printf("%s\n", info);
    } while (!feof(librecord));
    fclose(librecord);
    membrrecord = fopen("membrrecord.txt", "a+");
    printf("\nMid\tName\tDept\tPh.no\tAvailablecards\n");
    do
    {
        fgets(info, 500, membrrecord);
        printf("%s\n", info);
    } while (!feof(membrrecord));
    fclose(membrrecord);
}

void Searchbook()
{
    int i;
    char Target[25], stats[3];
    int Found = 0;
    if ((librecord = fopen("librecord.txt", "r")) == NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
        scanf("%s", Target);
        while (!feof(librecord) && Found == 0)
        {
            fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
            if (strcmp(Target, book.bname) == 0)
                Found = 1;
            for (i = 0; i < book.nooftitles; i++)
                fscanf(librecord, "%s", book.titles);
        }
        if (Found)
        {
            if (book.status == IN)
                strcpy(stats, "IN");
            else
                strcpy(stats, "OUT");

            printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n", book.bid, book.bname, book.author, stats);
        }
        else if (!Found)
            printf("! There is no such Entry...\n");
        fclose(librecord);
    }
}

void Exit()
{
    exit(0);
}
