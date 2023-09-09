#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a book
struct Book
{
    char title[100];
    char author[100];
    char genre[50];
    char subGenre[50];
    int height;
    char publisher[100];
};

// Define a structure to represent a user profile
struct User
{
    char username[50];
    char password[50];
    char preferences[100];
    char borrowedBook[100];
    struct User *nextUser;
};

// Function to display all books in the library
void displayBooks(struct Book *library, int numBooks)
{
    printf("\nList of Books:\n");
    for (int i = 0; i < numBooks; i++)
    {
        printf("Title: %s\n", library[i].title);
        printf("Author: %s\n", library[i].author);
        printf("Genre: %s\n", library[i].genre);
        printf("Subgenre: %s\n", library[i].subGenre);
        printf("Height: %d\n", library[i].height);
        printf("Publisher: %s\n\n", library[i].publisher);
    }
}

// Function to add a user to the user database
struct User *addUser(struct User *head, char username[], char password[], char preferences[])
{
    struct User *newUser = (struct User *)malloc(sizeof(struct User));
    if (newUser == NULL)
    {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    strcpy(newUser->preferences, preferences);
    strcpy(newUser->borrowedBook, "None");
    newUser->nextUser = head;
    return newUser;
}

// Function to authenticate a user
struct User *authenticateUser(struct User *users, const char *username, const char *password)
{
    struct User *current = users;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0)
        {
            return current;
        }
        current = current->nextUser;
    }
    return NULL; // User not found or invalid credentials
}

// Function to check out a book for a user
void checkoutBook(struct User *user, const char *bookTitle)
{
    strcpy(user->borrowedBook, bookTitle);
}

int main()
{
    struct Book library[100]; // Assuming a maximum of 100 books
    int numBooks = 0;         // Track the number of books in the library

    // Read books data from a CSV file and populate the library
    FILE *csvFile = fopen("library.csv", "r");
    if (csvFile == NULL)
    {
        // CSV file does not exist, create a new one
        csvFile = fopen("library.csv", "w");
        if (csvFile == NULL)
        {
            printf("Error creating the CSV file. Exiting.\n");
            return 1;
        }
        fclose(csvFile); // Close the newly created empty CSV file
    }
    else
    {
        // CSV file exists, read data from it
        char line[256];
        while (fgets(line, sizeof(line), csvFile))
        {
            char title[100], author[100], genre[50], subGenre[50], publisher[100];
            int height;
            if (sscanf(line, "%99[^,],%99[^,],%49[^,],%49[^,],%d,%99[^,]",
                       title, author, genre, subGenre, &height, publisher) == 6)
            {
                if (numBooks < 100)
                {
                    strcpy(library[numBooks].title, title);
                    strcpy(library[numBooks].author, author);
                    strcpy(library[numBooks].genre, genre);
                    strcpy(library[numBooks].subGenre, subGenre);
                    library[numBooks].height = height;
                    strcpy(library[numBooks].publisher, publisher);
                    numBooks++;
                }
                else
                {
                    printf("Library is full. Cannot add more books.\n");
                }
            }
        }
        fclose(csvFile);
    }

    // Initialize user database with predefined users
    struct User *users = NULL;
    users = addUser(users, "alice", "password123", "Mystery, Science Fiction");
    users = addUser(users, "bob", "bobpass", "Fantasy, History");

    // Add admin account
    struct User *admin = (struct User *)malloc(sizeof(struct User));
    if (admin == NULL)
    {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }
    strcpy(admin->username, "admin");
    strcpy(admin->password, "adminpass");
    strcpy(admin->preferences, "Admin");
    strcpy(admin->borrowedBook, "None");
    admin->nextUser = users;
    users = admin;

    // Simulate user login
    char enteredUsername[50];
    char enteredPassword[50];
    struct User *currentUser = NULL;

    do
    {
        printf("\nEnter your username (or 'exit' to quit): ");
        scanf("%s", enteredUsername);

        if (strcmp(enteredUsername, "exit") == 0)
        {
            break;
        }

        printf("Enter your password: ");
        scanf("%s", enteredPassword);

        currentUser = authenticateUser(users, enteredUsername, enteredPassword);

        if (currentUser == NULL)
        {
            printf("Authentication failed. Please try again or enter 'exit' to quit.\n");
        }
    } while (currentUser == NULL);

    if (currentUser != NULL)
    {
        // User login successful
        printf("\nWelcome, %s!\n", currentUser->username);
        printf("Your Reading Preferences: %s\n", currentUser->preferences);
        if (strcmp(currentUser->borrowedBook, "None") != 0)
        {
            printf("You have borrowed the book: %s\n", currentUser->borrowedBook);
        }
        else
        {
            printf("You haven't borrowed any books yet.\n");
        }

        // Allow the user to check out a book
        if (strcmp(currentUser->borrowedBook, "None") == 0)
        {
            char bookToCheckout[100];
            printf("Enter the title of the book you want to borrow: ");
            scanf("%s", bookToCheckout);

            // Check if the book is available in the library
            int bookIndex = -1;
            for (int i = 0; i < numBooks; i++)
            {
                if (strcmp(library[i].title, bookToCheckout) == 0)
                {
                    bookIndex = i;
                    break;
                }
            }

            if (bookIndex != -1)
            {
                // Book found in the library, check it out
                checkoutBook(currentUser, bookToCheckout);
                printf("You have borrowed the book: %s\n", bookToCheckout);
            }
            else
            {
                printf("Sorry, the book '%s' is not available in the library.\n", bookToCheckout);
            }
        }

        // Admin functionality
        if (strcmp(currentUser->username, "admin") == 0)
        {
            printf("\nAdmin Options:\n");
            printf("1. View list of books\n");
            printf("2. View who borrowed which book\n");
            int adminChoice;
            printf("Enter your choice (1 or 2): ");
            scanf("%d", &adminChoice);

            if (adminChoice == 1)
            {
                // Admin option to view list of books
                displayBooks(library, numBooks);
            }
            else if (adminChoice == 2)
            {
                // Admin option to view who borrowed which book
                printf("\nList of Users and Their Borrowed Books:\n");
                struct User *current = users;
                while (current != NULL)
                {
                    printf("User: %s, Borrowed Book: %s\n", current->username, current->borrowedBook);
                    current = current->nextUser;
                }
            }
            else
            {
                printf("Invalid choice.\n");
            }
        }
    }

    return 0;
}
