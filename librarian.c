#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 50
#define CSV_FILE "books.csv"

typedef struct Book {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int year;
} Book;


void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int is_numeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void search_books(const char *query) {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) {
        printf("Error: Could not open file '%s'.\n", CSV_FILE);
        return;
    }

    char line[256];
    int found = 0;
    char query_lower[100];
    strncpy(query_lower, query, 100);
    to_lowercase(query_lower);

  
    if (is_numeric(query_lower)) {
        int search_year = atoi(query_lower);
        while (fgets(line, sizeof(line), file)) {
            Book book;
            strncpy(book.title, strtok(line, ","), MAX_TITLE);
            strncpy(book.author, strtok(NULL, ","), MAX_AUTHOR);
            book.year = atoi(strtok(NULL, ","));

            if (book.year == search_year) {
                printf("Title: %s\nAuthor: %s\nYear: %d\n\n", book.title, book.author, book.year);
                found = 1;
            }
        }
    }
  
    else {
        while (fgets(line, sizeof(line), file)) {
            Book book;
            strncpy(book.title, strtok(line, ","), MAX_TITLE);
            strncpy(book.author, strtok(NULL, ","), MAX_AUTHOR);
            book.year = atoi(strtok(NULL, ","));

            char title_lower[MAX_TITLE], author_lower[MAX_AUTHOR];
            strncpy(title_lower, book.title, MAX_TITLE);
            strncpy(author_lower, book.author, MAX_AUTHOR);
            to_lowercase(title_lower);
            to_lowercase(author_lower);

            // Search if query matches title or author
            if (strstr(title_lower, query_lower) || strstr(author_lower, query_lower)) {
                printf("Title: %s\nAuthor: %s\nYear: %d\n\n", book.title, book.author, book.year);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching books found. Maybe you should add it!\n");
    }

    fclose(file);
}


void sort_books_by_title() {
    Book books[100];
    int count = 0;

    FILE *file = fopen(CSV_FILE, "r");
    if (!file) {
        printf("Error: Could not open file '%s'.\n", CSV_FILE);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Book book;
        strncpy(book.title, strtok(line, ","), MAX_TITLE);
        strncpy(book.author, strtok(NULL, ","), MAX_AUTHOR);
        book.year = atoi(strtok(NULL, ","));
        books[count++] = book;
    }
    fclose(file);

    // Bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(books[i].title, books[j].title) > 0) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("Title: %s\nAuthor: %s\nYear: %d\n\n", books[i].title, books[i].author, books[i].year);
    }
}

// Sort books by year in ascending order
void sort_books_by_year() {
    Book books[100];
    int count = 0;

    FILE *file = fopen(CSV_FILE, "r");
    if (!file) {
        printf("Error: Could not open file '%s'.\n", CSV_FILE);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Book book;
        strncpy(book.title, strtok(line, ","), MAX_TITLE);
        strncpy(book.author, strtok(NULL, ","), MAX_AUTHOR);
        book.year = atoi(strtok(NULL, ","));
        books[count++] = book;
    }
    fclose(file);

    // Bubble sort by year
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].year > books[j].year) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("Title: %s\nAuthor: %s\nYear: %d\n\n", books[i].title, books[i].author, books[i].year);
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./librarian <command> [arguments]\n");
        return 1;
    }

    char *command = argv[1];

    if (strcmp(command, "search") == 0) {
        if (argc < 3) {
            printf("Usage: ./librarian search <query>\n");
            return 1;
        }
        search_books(argv[2]);
    } else if (strcmp(command, "sort") == 0) {
        if (argc < 3) {
            printf("Usage: ./librarian sort <title|year>\n");
            return 1;
        }
        if (strcmp(argv[2], "title") == 0) {
            sort_books_by_title();
        } else if (strcmp(argv[2], "year") == 0) {
            sort_books_by_year();
        } else {
            printf("Unknown sort option. Use 'title' or 'year'.\n");
        }
    } else {
        printf("Unknown command. Available commands are 'search' and 'sort'.\n");
    }

    return 0;
}
