# Library Management System

This simple library management system is designed in C and includes basic functionalities for managing books and user accounts. Below is a brief overview of the key features and structures in the program:

## Structures

### Book Structure
```c
struct Book
{
    char title[100];
    char author[100];
    char genre[50];
    char subGenre[50];
    int height;
    char publisher[100];
};
```

### User Structure
```c
struct User
{
    char username[50];
    char password[50];
    char preferences[100];
    char borrowedBook[100];
    struct User *nextUser;
};
```

## Functions

### `displayBooks`
Displays a list of all books in the library.

### `addUser`
Adds a new user to the user database.

### `authenticateUser`
Authenticates a user based on provided username and password.

### `checkoutBook`
Allows a user to check out a book from the library.

## Main Functionality

1. Reads book data from a CSV file and populates the library.
2. Initializes a user database with predefined users, including an admin account.
3. Simulates user login with authentication.
4. Displays user information, reading preferences, and borrowed books.
5. Allows users to check out books if they haven't borrowed any yet.
6. Provides admin options to view the list of books or see who borrowed which book.

## Usage

1. Compile the program.
2. Run the executable.
3. Enter your username and password to simulate user login.
4. Follow the prompts to interact with the system.

Feel free to customize the code according to your specific requirements. Enjoy managing your library!

**Note:** Ensure that the "library.csv" file is present or created in the same directory as the executable for proper functionality.

---

Feel free to modify and improve the readme according to your preferences. Let me know if you need any specific modifications or additional features in the program!
