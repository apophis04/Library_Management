#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LENGTH 256
#define MAX_BOOKS 1000

// Define the Book structure
struct Book {
    char title[MAX_FIELD_LENGTH];
    char author[MAX_FIELD_LENGTH];
    char genre[MAX_FIELD_LENGTH];
    char subGenre[MAX_FIELD_LENGTH];
    int height;
    char publisher[MAX_FIELD_LENGTH];
};

// Function to read books from CSV file
int readBooksFromCSV(const char *csvFilePath, struct Book library[], int *numBooks) {
    FILE *file = fopen(csvFilePath, "r");
    if (file == NULL) {
        printf("Error opening CSV file.\n");
        return 0;
    }

    *numBooks = 0;

    char line[MAX_FIELD_LENGTH * 6];  // Adjust buffer size as needed
    while (*numBooks < MAX_BOOKS && fgets(line, sizeof(line), file)) {
        struct Book *currentBook = &library[*numBooks];

        int result = sscanf(line, "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%d,\"%[^\"]\"\n",
                            currentBook->title, currentBook->author, currentBook->genre,
                            currentBook->subGenre, &(currentBook->height), currentBook->publisher);

        if (result == 6) {
            (*numBooks)++;
        } else {
            printf("Error parsing line: %s", line);
        }
    }

    fclose(file);
    return 1;
}

// Function to display a list of books
void displayBooks(struct Book library[], int numBooks) {
    if (numBooks == 0) {
        printf("Library is empty.\n");
        return;
    }

    printf("List of Books:\n");

    for (int i = 0; i < numBooks; i++) {
        printf("%d. Title: %s\n   Author: %s\n   Genre: %s\n   Subgenre: %s\n   Height: %d\n   Publisher: %s\n",
               i + 1, library[i].title, library[i].author, library[i].genre, library[i].subGenre,
               library[i].height, library[i].publisher);
    }
}

int main() {
    const char *csvFilePath = "D:\\APOPHIS\\Projects\\books.csv";
    struct Book library[MAX_BOOKS];
    int numBooks;

    if (readBooksFromCSV(csvFilePath, library, &numBooks)) {
        int choice;
        do {
            printf("\nMenu:\n");
            printf("1. Display Books\n");
            printf("2. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    displayBooks(library, numBooks);
                    break;
                case 2:
                    printf("Goodbye!\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
        } while (choice != 2);
    }

    return 0;
}
