#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>




#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"


#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"


#define BRIGHT_RED "\x1b[91m"
#define BRIGHT_GREEN "\x1b[92m"
#define BRIGHT_YELLOW "\x1b[93m"
#define BRIGHT_CYAN "\x1b[96m"
#define BRIGHT_WHITE "\x1b[97m"

FILE *fp;


struct Book {
    char ISBN[100];
    char NAME[250];
    char AUTHOR_NAME[100];
    int Available_copies;
    int id;
    char Shelf[100];
    char section[100];
    char row[200];

};

struct student {
    char NAME[100];
    char SECTION[100];
    int Class;
    int roll;
    char issue_date[200];
    char return_date[200];

    int ID;
    char BOOKNAME[250];

};



void clear_input_buffer();
void addBook();
void delete_book();
void lsbook();
void issue_book();
void return_book();
void issue_list();
void search_book();
void modify_book();


int main()
{
    int ch;
    while(1)
    {

        system("cls");
        printf(BOLD BRIGHT_CYAN "\n\n********************************************Welcome to School Library Management System*************************************************************\n\n" RESET);
        printf(YELLOW " 1.Add Book\n" RESET);
        printf(YELLOW " 2.Delete Book\n" RESET);
        printf(YELLOW " 3.Show Book list\n" RESET);
        printf(YELLOW " 4.Issue Book\n" RESET);
        printf(YELLOW " 5.Return Book\n" RESET);
        printf(YELLOW " 6.Show Issued Book List\n" RESET);

        printf(YELLOW " 7.Search Book\n" RESET);
        printf(YELLOW " 8.Modify Book Details\n"RESET);
        printf(BRIGHT_RED " 0.Exit\n" RESET);

        printf(BOLD "\n Enter your choice: " RESET);
        if (scanf("%d" , &ch) != 1) {
            printf(RED "\nInvalid input! Please enter a number.\n" RESET);
            clear_input_buffer();
            getch();
            continue;
        }

        clear_input_buffer();

        switch(ch){
            case 1:
            {
                addBook();
                getch();
                break;
            }
            case 2:
                {
                    delete_book();
                    getch();
                    break;
                }
            case 3:
                {
                    lsbook();
                    getch();
                    break;
                }
            case 4:
                {
                    issue_book();
                    getch();
                    break;
                }
            case 5:
                {
                    return_book();
                    getch();
                    break;
                }
            case 6:
                {
                    issue_list();
                    getch();
                    break;
                }
            case 7:
                {
                    search_book();
                    getch();
                    break;
                }
            case 8:
                {
                    modify_book();
                    getch();
                    break;
                }
            case 0:
            {
                printf(BRIGHT_GREEN "\nExiting Library Management System. Goodbye!\n" RESET);
                return 0;
            }
            default:
            {
                printf(RED "\nInvalid choice. Please enter a number between 0 and 8.\n" RESET);
                getch();
                break;
            }
        }
    }
}



void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}



void addBook()
{
    struct Book newBook;

    printf(BOLD MAGENTA "\n\t\t--- Add New Book ---\t\t\n" RESET);

    printf("Enter Book ID: ");
    if (scanf("%d", &newBook.id) != 1) {
        printf(RED "Invalid ID input. Book not added.\n" RESET);
        clear_input_buffer();
        return;
    }

    clear_input_buffer();

    printf("Enter Book Name: ");
    fgets(newBook.NAME, sizeof(newBook.NAME), stdin);
    newBook.NAME[strcspn(newBook.NAME, "\n")] = 0;

    printf("Enter Author Name: ");
    fgets(newBook.AUTHOR_NAME, sizeof(newBook.AUTHOR_NAME), stdin);
    newBook.AUTHOR_NAME[strcspn(newBook.AUTHOR_NAME, "\n")] = 0;

    printf("Enter ISBN Number: ");
    fgets(newBook.ISBN, sizeof(newBook.ISBN), stdin);
    newBook.ISBN[strcspn(newBook.ISBN, "\n")] = 0;

    printf("Enter Available Copies: ");
    if (scanf("%d", &newBook.Available_copies) != 1) {
        printf(RED "Invalid copies input. Book not added.\n" RESET);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter Shelf No. ");
    fgets(newBook.Shelf , sizeof(newBook.Shelf) , stdin);
    newBook.Shelf[strcspn(newBook.Shelf, "\n")] = 0;

    printf("Enter Section Name: ");
    fgets(newBook.section , sizeof(newBook.section) , stdin);
    newBook.section[strcspn(newBook.section, "\n")] = 0;

    printf("Enter Row No. " );
    fgets(newBook.row , sizeof(newBook.row) , stdin);
    newBook.row[strcspn(newBook.row, "\n")] = 0;

    fp = fopen("Book.dat","ab");
    if (fp == NULL) {
        perror(RED "Error opening Book.dat" RESET);
        return;
    }

    fwrite(&newBook , sizeof(struct Book) , 1 , fp);

    fclose(fp);

    printf(BRIGHT_GREEN "Book Added Successfully! Press any key to return to the menu.\n" RESET);
}

void delete_book()
{
    FILE *fptemp;

    struct Book b;
    int f = 0;
    int id_to_delete;

    system("cls");
    printf(BOLD MAGENTA "\n\t\t*************** Delete Books ***************\t\t\n" RESET);

    printf("Enter book ID To Delete: ");

    if (scanf("%d" , &id_to_delete) != 1) {
        printf(RED "Invalid ID input. Returning to menu.\n" RESET);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    fp = fopen("Book.dat" , "rb");
    if (fp == NULL) {
        printf(RED "Error: Book database ('Book.dat') not found or could not be opened.\n" RESET);
        return;
    }

    fptemp = fopen("Temp.dat" , "wb");
    if (fptemp == NULL) {
        perror(RED "Error opening temporary file 'Temp.dat'" RESET);
        fclose(fp);
        return;
    }

    while(fread(&b , sizeof(struct Book), 1 ,fp) == 1)
    {
        if(id_to_delete == b.id)
        {
            f = 1;
        }
        else{
            fwrite(&b , sizeof(struct Book), 1 ,fptemp);
        }
    }

    fclose(fp);
    fclose(fptemp);

    if(f == 1)
    {
        printf(BRIGHT_GREEN "\nBook (ID: %d) Deleted Successfully.\n" RESET, id_to_delete);

        remove("Book.dat");
        rename("Temp.dat", "Book.dat");
    }
    else
    {
        printf(RED "\nNo Book Record Found with ID: %d\n" RESET, id_to_delete);

        remove("Temp.dat");
    }
    printf(CYAN "Press any key to return to the menu..." RESET);
}

void lsbook()
{
    struct Book l;
    int count = 0;
    system("cls");


    printf(BOLD BRIGHT_YELLOW "\n\n\t\t*************************************** LIBRARY BOOK LIST  ***************************************\t\t\n\n" RESET);


    // Header styling
    printf(BLUE "---------------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);
    printf(BOLD BLUE "| %-5s | %-15s | %-30s | %-20s | %-6s | %-10s | %-20s | %-10s |\n" RESET,
              "ID", "ISBN", "BOOK NAME", "AUTHOR", "COPIES", "SHELF", "SECTION", "ROW");
    printf(BLUE "---------------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);


    fp = fopen("Book.dat","rb");
    if (fp == NULL) {
        printf(RED "Error: Book database ('Book.dat') not found or could not be opened.\n" RESET);
        printf(YELLOW "Please ensure you have added books using option 1.\n" RESET);
        return;
    }


    while(fread(&l , sizeof(struct Book), 1, fp) == 1)
    {
        count++;


        printf(WHITE "| %-5d | %-15s | %-30s | %-20s | %-6d | %-10s | %-20s | %-10s |\n" RESET ,
                 l.id,
                 l.ISBN,
                 l.NAME,
                 l.AUTHOR_NAME,
                 l.Available_copies,
                 l.Shelf,
                 l.section,
                 l.row);
    }

    printf(BLUE "-------------------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);

    if (count == 0) {
        printf(YELLOW "\n\t\t\t\t\t--- No Records Found in the Library. ---\n" RESET);
    } else {
        printf(BRIGHT_GREEN "\n\t\t\t\t\tTotal Books Listed: %d\n" RESET, count);
    }

    fclose(fp);

    printf(CYAN "Press any key to return to the menu.\n" RESET);
}

void search_book()
{
    struct Book b;
    int fu;
    fp = fopen("Book.dat" , "rb");

    system("cls");
    printf(BOLD MAGENTA "\n\t\t*************** Search Book ***************\t\t\n" RESET);

    printf("Enter Book ID to Find: ");
    if(scanf("%d" , &fu) != 1)
    {
        printf(RED "Invalid input! Please enter a numerical Book ID.\n" RESET);
        clear_input_buffer();
        printf(CYAN "Press any key to continue...." RESET);
        return;
    }

    clear_input_buffer();

    if (fp == NULL) {
        printf(RED "Error: Book database ('Book.dat') not found.\n" RESET);
        printf(CYAN "Press any key to continue...." RESET);
        return;
    }

    int found = 0;
    while(fread(&b , sizeof(b), 1, fp) == 1)
    {
        if(b.id == fu)
        {
            found = 1;
            printf(BRIGHT_GREEN "\nBook Found With Id %d: '%s'\n" RESET, b.id, b.NAME);
            printf(WHITE "Author: %s\n" RESET, b.AUTHOR_NAME);
            printf(WHITE "ISBN: %s\n" RESET, b.ISBN);
            printf(WHITE "Present in Section %s, Shelf %s, Row %s.\n" RESET, b.section , b.Shelf , b.row);
            printf(WHITE "Available Copies: %d\n" RESET, b.Available_copies);
            break;
        }
    }

    fclose(fp);

    if (found == 0)
    {
        printf(RED "No Book Found with this ID: %d\n" RESET, fu);
    }

    printf(CYAN "Press any key to continue.." RESET);
}

void modify_book()
{
    struct Book b;
    int id_to_modify;
    int found = 0;
    long book_record_size = sizeof(struct Book);

    system("cls");
    printf(BOLD MAGENTA "\n\t\t*************** Modify Book Details ***************\t\t\n" RESET);

    printf("Enter Book ID to Modify: ");
    if (scanf("%d", &id_to_modify) != 1) {
        printf(RED "Invalid ID input. Returning to menu.\n" RESET);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    fp = fopen("Book.dat", "r+b");
    if (fp == NULL) {
        printf(RED "Error: Book database ('Book.dat') not found or could not be opened.\n" RESET);
        return;
    }

    while (fread(&b, book_record_size, 1, fp) == 1) {
        if (b.id == id_to_modify) {
            found = 1;
            printf(BRIGHT_GREEN "\nBook Found: ID %d - '%s' by %s\n" RESET, b.id, b.NAME, b.AUTHOR_NAME);



            printf(YELLOW "\nEnter NEW Book Name (Current: %s): " RESET, b.NAME);
            fgets(b.NAME, sizeof(b.NAME), stdin);
            b.NAME[strcspn(b.NAME, "\n")] = 0;

            printf(YELLOW "Enter NEW Author Name (Current: %s): " RESET, b.AUTHOR_NAME);
            fgets(b.AUTHOR_NAME, sizeof(b.AUTHOR_NAME), stdin);
            b.AUTHOR_NAME[strcspn(b.AUTHOR_NAME, "\n")] = 0;

            printf(YELLOW "Enter NEW ISBN Number (Current: %s): " RESET, b.ISBN);
            fgets(b.ISBN, sizeof(b.ISBN), stdin);
            b.ISBN[strcspn(b.ISBN, "\n")] = 0;

            printf(YELLOW "Enter NEW Available Copies (Current: %d): " RESET, b.Available_copies);
            if (scanf("%d", &b.Available_copies) != 1) {
                printf(RED "Invalid copies input. Modification failed.\n" RESET);
                clear_input_buffer();
                fclose(fp);
                return;
            }
            clear_input_buffer();

            printf(YELLOW "Enter NEW Shelf No. (Current: %s): " RESET, b.Shelf);
            fgets(b.Shelf, sizeof(b.Shelf), stdin);
            b.Shelf[strcspn(b.Shelf, "\n")] = 0;

            printf(YELLOW "Enter NEW Section Name (Current: %s): " RESET, b.section);
            fgets(b.section, sizeof(b.section), stdin);
            b.section[strcspn(b.section, "\n")] = 0;

            printf(YELLOW "Enter NEW Row No. (Current: %s): " RESET, b.row);
            fgets(b.row, sizeof(b.row), stdin);
            b.row[strcspn(b.row, "\n")] = 0;
            fseek(fp, -book_record_size, SEEK_CUR);


            fwrite(&b, book_record_size, 1, fp);
            fflush(fp);

            printf(BRIGHT_GREEN "\nBook (ID: %d) Details Modified Successfully!\n" RESET, id_to_modify);
            break;
        }
    }

    fclose(fp);

    if (found == 0) {
        printf(RED "\nNo Book Record Found with ID: %d\n" RESET, id_to_modify);
    }

    printf(CYAN "Press any key to return to the menu..." RESET);
}



void issue_book()
{
    struct Book b;
    struct student s;
    int fun = 0;
    long book_record_size = sizeof(struct Book);

    system("cls");
    printf(BOLD MAGENTA "\t\t**************************ISSUE BOOK**************************\t\t\n" RESET);
    printf("Enter Book ID to issue: ");

    if(scanf("%d" , &s.ID)!= 1)
    {
        printf(RED "Invalid ID! Returning to menu\n" RESET);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    fp = fopen("Book.dat" , "r+b");
    if (fp == NULL) {
        printf(RED "Error opening book database. Cannot issue book.\n" RESET);
        return;
    }

    while(fread(&b , book_record_size , 1 , fp) == 1){
        if(b.id == s.ID)
        {
            if (b.Available_copies > 0) {
                strcpy(s.BOOKNAME , b.NAME);
                fun = 1;
            } else {
                fun = 2;
            }
            break;
        }
    }

    if(fun == 0){
        printf(RED "NO BOOK FOUND WITH THIS ID! Returning To Menu\n" RESET);
        fclose(fp);
        return;
    }

    if(fun == 2){
        printf(YELLOW "Book is currently OUT OF STOCK (0 copies available)! Returning To Menu\n" RESET);
        fclose(fp);
        return;
    }


    b.Available_copies--;

    fseek(fp, -book_record_size, SEEK_CUR);

    fwrite(&b, book_record_size, 1, fp);
    fclose(fp);


    fp = fopen("Issue.dat" , "ab");
    if (fp == NULL) {
        printf(RED "Error: Cannot open Issue log file.\n" RESET);
        return;
    }

    printf("Enter Student Name: ");
    fgets(s.NAME , sizeof(s.NAME) , stdin);
    s.NAME[strcspn(s.NAME, "\n")] = 0;

    printf("Enter Student Roll: ");
    if(scanf("%d" , &s.roll) != 1)
    {
        printf(RED "Invalid roll number. Please Try Again...\n" RESET);
        clear_input_buffer();
        fclose(fp);
        return;
    }
    printf("Enter Student Class: ");
    if(scanf("%d" , &s.Class) != 1)
    {
        printf(RED "Invalid class number. Please Try Again...\n" RESET);
        clear_input_buffer();
        fclose(fp);
        return;
    }
    clear_input_buffer();
    printf("Enter Student Section: ");
    fgets(s.SECTION , sizeof(s.SECTION) , stdin);
    s.SECTION[strcspn(s.SECTION, "\n")] = 0;


    printf("Enter Issue Date: ");
    fgets(s.issue_date , sizeof(s.issue_date) , stdin);
    s.issue_date[strcspn(s.issue_date, "\n")] = 0;

    printf("Enter Return Date: ");
    fgets(s.return_date , sizeof(s.return_date), stdin);
    s.return_date[strcspn(s.return_date, "\n")] = 0;

    fwrite(&s , sizeof(s) , 1, fp);
    fclose(fp);

    printf(BRIGHT_GREEN "Book Issued Sucessfully! Remaining copies of '%s': %d.\n" RESET, b.NAME, b.Available_copies);
    printf(CYAN "Press any key to return menu..." RESET);
}
void return_book()
{
    struct student s;
    struct Book b;
    FILE *fp_issue_temp, *fp_book;
    int book_id_to_return;
    int found_issued_record = 0;
    long book_record_size = sizeof(struct Book);

    char separator[] = " | ";

    system("cls");
    printf(BOLD MAGENTA "\n\n\t\t***************************** RETURN BOOK *****************************\n" RESET);

    printf("Enter Book ID to Return: ");
    if (scanf("%d", &book_id_to_return) != 1) {
        printf(RED "Invalid ID input. Returning to menu.\n" RESET);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    fp = fopen("Issue.dat", "rb");
    if (fp == NULL) {
        printf(RED "Error: Issue log ('Issue.dat') not found. No books are currently recorded as issued.\n" RESET);
        return;
    }

    fp_issue_temp = fopen("Issue_temp.dat", "wb");
    if (fp_issue_temp == NULL) {
        perror(RED "Error creating temporary file for issue log" RESET);
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(struct student), 1, fp) == 1) {
        if (s.ID == book_id_to_return) {
            found_issued_record = 1;

            printf(YELLOW "\n--- Issued Record Found ---\n" RESET);
            printf(CYAN "| %-10s%s", "BOOK ID", separator);
            printf("%-10s%s", "ROLL", separator);
            printf("%-10s%s", "CLASS", separator);
            printf("%-30s%s", "STUDENT NAME", separator);
            printf("%-30s%s", "BOOK NAME", separator);
            printf("%-15s%s", "ISSUE DATE", separator);
            printf("%-15s |\n" RESET, "RETURN DATE");
            printf(WHITE "| %-10d%s", s.ID, separator);
            printf("%-10d%s", s.roll, separator);
            printf("%-10d%s", s.Class, separator);
            printf("%-30s%s", s.NAME, separator);
            printf("%-30s%s", s.BOOKNAME, separator);
            printf("%-15s%s", s.issue_date, separator);
            printf("%-15s |\n" RESET, s.return_date);
            printf(YELLOW "--------------------------\n" RESET);

        } else {
            fwrite(&s, sizeof(struct student), 1, fp_issue_temp);
        }
    }

    fclose(fp);
    fclose(fp_issue_temp);

    if (found_issued_record == 0) {
        printf(RED "\nError: No outstanding issue record found for Book ID: %d.\n" RESET, book_id_to_return);
        remove("Issue_temp.dat");
        return;
    }


    remove("Issue.dat");
    rename("Issue_temp.dat", "Issue.dat");
    printf(BRIGHT_GREEN "Issue record removed successfully.\n" RESET);


    fp_book = fopen("Book.dat", "r+b");
    if (fp_book == NULL) {
        printf(RED "Warning: Could not open Book database to increment copies. Inventory count may be inaccurate.\n" RESET);
        printf(CYAN "Press any key to return to the menu.\n" RESET);
        return;
    }

    int found_book_record = 0;

    while (fread(&b, book_record_size, 1, fp_book) == 1) {
        if (b.id == book_id_to_return) {
            found_book_record = 1;

            b.Available_copies++;

            fseek(fp_book, -book_record_size, SEEK_CUR);

            fwrite(&b, book_record_size, 1, fp_book);
            printf(BRIGHT_GREEN "Book inventory updated: '%s' now has %d copies.\n" RESET, b.NAME, b.Available_copies);
            break;
        }
    }

    fclose(fp_book);

    if (found_book_record == 0) {
        printf(YELLOW "Warning: Book ID %d not found in the main inventory ('Book.dat'). Inventory count not updated.\n" RESET, book_id_to_return);
    }

    printf(CYAN "\nBook Returned Successfully! Press any key to return to the menu.\n" RESET);
}
void issue_list()
{
    struct student s;
    int count = 0;

    char separator[] = " | ";

    system("cls");
    printf(BOLD BRIGHT_YELLOW "\n\n***************************************** ISSUED BOOK LIST *****************************************\n" RESET);

    fp = fopen("Issue.dat" , "rb");
    if (fp == NULL) {
        printf(RED "\nError: Issued book database ('Issue.dat') not found or could not be opened.\n" RESET);
        printf(CYAN "Press any key to return to the menu.\n" RESET);
        return;
    }

    printf(BLUE "--------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);

    printf(BOLD BLUE "| %-10s%s", "BOOK ID", separator);
    printf("%-10s%s", "ROLL", separator);
    printf("%-10s%s", "CLASS", separator);
    printf("%-30s%s", "STUDENT NAME", separator);
    printf("%-30s%s", "BOOK NAME", separator);
    printf("%-15s%s", "ISSUE DATE", separator);
    printf("%-15s |\n" RESET, "RETURN DATE");

    printf(BLUE "--------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);

    while(fread(&s, sizeof(s), 1, fp) == 1){
        count++;

        printf(WHITE "| %-10d%s", s.ID, separator);
        printf("%-10d%s", s.roll, separator);
        printf("%-10d%s", s.Class, separator);
        printf("%-30s%s", s.NAME, separator);
        printf("%-30s%s", s.BOOKNAME, separator);
        printf("%-15s%s", s.issue_date, separator);
        printf("%-15s |\n" RESET, s.return_date);
    }

    printf(BLUE "--------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);

    if (count == 0) {
        printf(YELLOW "\n\t\t\t\t\t--- No Books Currently Issued. ---\n" RESET);
    } else {
        printf(BRIGHT_GREEN "\n\t\t\t\t\tTotal Issued Records: %d\n" RESET, count);
    }

    fclose(fp);
    printf(CYAN "Press any key to return menu..." RESET);
}
