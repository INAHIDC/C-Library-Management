#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 50
#define CSV_FILE "books.csv"

typedef struct Book
{
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int year;
} Book;

void add_book(const char *title, const char *author, int year);
void delete_book(const char *title);
void list_books();
void save_book_to_csv(const Book *book);
void load_books_from_csv();
void rewrite_csv_without(const char *title);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./book_manager <command> [arguments]\n");
        return 1;
    }

    char *command = argv[1];

    if (strcmp(command, "add") == 0)
    {
        if (argc < 5)
        {
            printf("Usage: ./book_manager add <title> <author> <year>\n");
            return 1;
        }
        char *title = argv[2];
        char *author = argv[3];
        int year = atoi(argv[4]);
        add_book(title, author, year);
        printf("Book added: %s by %s (%d)\n", title, author, year);
    }
    else if (strcmp(command, "list") == 0)
    {
        list_books();
    }
    else if (strcmp(command, "delete") == 0)
    {
        if (argc < 3)
        {
            printf("Usage: ./book_manager delete <title>\n");
            return 1;
        }
        delete_book(argv[2]);
        printf("Book deleted: %s\n", argv[2]);
    }
    else
    {
        printf("Unknown command.\n");
    }

    return 0;
}

// CSV
void add_book(const char *title, const char *author, int year)
{
    Book book;
    strncpy(book.title, title, MAX_TITLE);
    strncpy(book.author, author, MAX_AUTHOR);
    book.year = year;

    save_book_to_csv(&book);
}

void delete_book(const char *title)
{
    rewrite_csv_without(title);
}

void list_books()
{
    load_books_from_csv();
}

void save_book_to_csv(const Book *book)
{
    FILE *file = fopen(CSV_FILE, "a");
    if (!file)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s,%s,%d\n", book->title, book->author, book->year);
    fclose(file);
}

void load_books_from_csv()
{
    FILE *file = fopen(CSV_FILE, "r");
    if (!file)
    {
        printf("No books available.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *title = strtok(line, ",");
        char *author = strtok(NULL, ",");
        int year = atoi(strtok(NULL, ","));

        printf("Title: %s\nAuthor: %s\nYear: %d\n\n", title, author, year);
    }
    fclose(file);
}

void rewrite_csv_without(const char *title)
{
    FILE *file = fopen(CSV_FILE, "r");
    if (!file)
    {
        printf("No books to delete.\n");
        return;
    }

    FILE *temp_file = fopen("temp.csv", "w");
    if (!temp_file)
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        char *book_title = strtok(line, ",");
        if (strcmp(book_title, title) != 0)
        {
            fputs(line, temp_file);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(CSV_FILE);
    rename("temp.csv", CSV_FILE);

    if (!found)
    {
        printf("Book not found.\n");
    }
}
