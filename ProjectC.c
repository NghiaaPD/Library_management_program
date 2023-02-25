#include <stdio.h>
#include <string.h>

//Mảng lưu trữ các elements của sách
struct Book {
    char title[100];
    char author[100];
    char genre[50];
    int year_published;
    int borrowed;
};

struct Book books[100];
int num_books = 0;

//Hàm thêm sách
void add_book() {
    struct Book new_book;

    printf("Enter the book title: ");
    scanf("%s", new_book.title);


    printf("Enter the book author: ");
    scanf("%s", new_book.author);


    printf("Enter the book genre: ");
    scanf("%s", new_book.genre);


    printf("Enter the year the book was published: ");
    scanf("%d", &new_book.year_published);
    getchar(); // Consume newline character left in input buffer

    books[num_books] = new_book;
    (num_books)++;

    printf("\nBook added:\n");
    printf("Title: %s\n", books[0].title);
    printf("Author: %s\n", books[0].author);
    printf("Genre: %s\n", books[0].genre);
    printf("Year Published: %d\n", books[0].year_published);
    printf("--------------------------------------------------------------\n");
}

//Hàm hiện thị sách
void display_book() {
    if (num_books == 0) {
        printf("There are no books to display.\n");
        return;
    }

    printf("All books:\n");
    printf("  Book   |            Title            |          Author         |      Genre      |  Year Published  \n");
    printf("---------+-----------------------------+-------------------------+-----------------+------------------\n");
    for (int i = 0; i < num_books; i++) {
        printf("%8d | %-27s | %-23s | %-15s | %7d\n", i+1, books[i].title, books[i].author, books[i].genre, books[i].year_published);
    }


}

//Hàm tìm sách
void search_book() {
    char search_term[100];
    int search_year;
    int found = 0;

    printf("Enter the Title, Author or Genre of the book: ");
    scanf("%s", search_term);

    printf("Enter the year of publication to search (enter 0 to ignore year): ");
    scanf("%d", &search_year);

    printf("Results:\n");

    for (int i = 0; i < num_books; i++) {
        if (strcmp(books[i].title, search_term) == 0 ||
            strcmp(books[i].author, search_term) == 0 ||
            strcmp(books[i].genre, search_term) == 0) {
            if (search_year == 0 || books[i].year_published == search_year) {
                printf("--------------------------------------------------------------\n");
                printf("Title: %s\n", books[i].title);
                printf("Author: %s\n", books[i].author);
                printf("Genre: %s\n", books[i].genre);
                printf("Year Published: %d\n", books[i].year_published);
                printf("--------------------------------------------------------------\n");
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching books found.\n");
    }
}

// Hàm mượn sách
void borrow_book() {
    char title[100];
    char author[100];

    printf("All books:\n");
    printf("  Book   |            Title            |          Author         |      Genre      |  Year Published  \n");
    printf("---------+-----------------------------+-------------------------+-----------------+------------------\n");
    for (int i = 0; i < num_books; i++) {
        printf("%8d | %-27s | %-23s | %-15s | %7d\n", i+1, books[i].title, books[i].author, books[i].genre, books[i].year_published);
    }
    printf("---------+-----------------------------+-------------------------+-----------------+------------------\n");



    // Nhập thông tin tên sách và tên tác giả
    printf("Enter the book title: ");
    scanf("%s", title);

    printf("Enter the author name: ");
    scanf("%s", author);

    // Tìm kiếm sách trong mảng books
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (strcmp(books[i].title, title) == 0 && strcmp(books[i].author, author) == 0) {
            found = 1;
            // Kiểm tra xem sách có đang được mượn không
            if (books[i].borrowed == 1) {
                printf("This book is currently borrowed.\n");
                return;
            }
            else {
                books[i].borrowed = 1;
                printf("Book borrowed successfully.\n");
                return;
            }
        }
    }

    if (!found) {
        printf("The book you are looking for is not in the library.\n");
        return;
    }
}

//Hàm trả sách
void return_book() {
    int book_id;

    printf("Number of books you are borrowing:\n");
    printf("+---------+---------------------------+\n");
    printf("|   ID    |        Borrower Name       |\n");
    printf("+---------+---------------------------+\n");
    for (int i = 0; i < num_books; i++) {
        if (books[i].borrowed == 1) {
            printf("|%9d|%27s|\n", i+1, books[i].title);
        }
    }
    printf("+---------+---------------------------+\n");

    printf("Enter the book ID: ");
    scanf("%d", &book_id);

    if (book_id < 1 || book_id > num_books) {
        printf("Invalid book ID.\n");
        return;
    }

    if (books[book_id-1].borrowed == 0) {
        printf("This book is not currently borrowed.\n");
        return;
    }

    books[book_id-1].borrowed = 0;
    printf("Book returned successfully.\n");
}

//Hàm kiểm tra xem sách đó đã được mượn hay chưa
void find_borrowed_books() {
    printf("+---------+---------------------------+\n");
    printf("|   ID    |        Borrower Name       |\n");
    printf("+---------+---------------------------+\n");
    for (int i = 0; i < num_books; i++) {
        if (books[i].borrowed == 1) {
            printf("|%9d|%27s|\n", i+1, books[i].title);
        }
    }
    printf("+---------+---------------------------+\n");
}

//Hàm xóa sách
void delete_book() {
    int id;

    printf("All books:\n");
    printf("  Book   |            Title            |          Author         |      Genre      |  Year Published  \n");
    printf("---------+-----------------------------+-------------------------+-----------------+------------------\n");
    for (int i = 0; i < num_books; i++) {
        printf("%8d | %-27s | %-23s | %-15s | %7d\n", i+1, books[i].title, books[i].author, books[i].genre, books[i].year_published);
    }
    printf("---------+-----------------------------+-------------------------+-----------------+------------------\n");

    // Nhập thông tin id sách cần xóa
    printf("Enter the book ID to delete: ");
    scanf("%d", &id);

    // Tìm kiếm sách trong mảng books
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (i+1 == id) {
            found = 1;
            // Kiểm tra xem sách có đang được mượn không
            if (books[i].borrowed == 1) {
                printf("The book being borrowed cannot be deleted.\n");
                return;
            }
            else {
                // Di chuyển các phần tử phía sau lên 1 vị trí
                for (int j = i; j < num_books-1; j++) {
                    strcpy(books[j].title, books[j+1].title);
                    strcpy(books[j].author, books[j+1].author);
                    strcpy(books[j].genre, books[j+1].genre);
                    books[j].year_published = books[j+1].year_published;
                    books[j].borrowed = books[j+1].borrowed;
                }
                num_books--;
                printf("Book deleted successfully.\n");
                return;
            }
        }
    }

    if (!found) {
        printf("The book with ID %d is not in the library.\n", id);
        return;
    }
}




//Cái này là hàm chính :3
int main(int argc, char *argv[]) {
    int is_logged_in = 0;
    do {
        if (is_logged_in) {
            printf("logged out\n");
            printf("-----------------------------------------------------\n");
        }
        is_logged_in = 0;

        // Yêu cầu người dùng nhập tên đăng nhập và mật khẩu
        char username[20];
        char password[20];
        printf("Login\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        // Kiểm tra thông tin đăng nhập
        // Tài khoản admin
        if (strcmp(username, "nghiapda") == 0 && strcmp(password, "123") == 0) {
            printf("Login successful!\n");
            is_logged_in = 1;
            int choice;
            printf("Option:\n");
            do {
                printf("1. Add book\n");
                printf("2. Display books\n");
                printf("3. Search book\n");
                printf("4. Find borrowed books\n");
                printf("5. Delete book\n");
                printf("0. Logout\n");
                printf("Choose your option:");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        add_book();
                        break;
                    case 2:
                        display_book();
                        break;
                    case 3:
                        search_book();
                        break;
                    case 4:
                        find_borrowed_books();
                        break;
                    case 5:
                        delete_book();
                        break;
                    case 0:
                        printf("Logging out...\n");
                        break;
                    default:
                        printf("Invalid choice. Try again.\n");
                        break;
                }
            } while (choice != 0);

        //tài khoản user
        } else if (strcmp(username, "nghiapdb") == 0 && strcmp(password, "123") == 0) {
            printf("Login successful!\n");
            is_logged_in = 1;
            int choice;
            printf("Option:\n");
            do {
                printf("1. Display books\n");
                printf("2. Search book\n");
                printf("3. Find borrowed books\n");
                printf("4. Borrow book\n");
                printf("5. Return book\n");
                printf("0. Logout\n");
                printf("Choose your option:");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        display_book();
                        break;
                    case 2:
                        search_book();
                        break;
                    case 3:
                        find_borrowed_books();
                        break;
                    case 4:
                        borrow_book();
                        break;
                    case 5:
                        return_book();
                        break;
                    case 0:
                        printf("Logging out...\n");
                        break;
                    default:
                        printf("Invalid choice. Try again.\n");
                        break;
                }
            } while (choice != 0);
        } else {
            printf("Login information is incorrect!\n");
        }
    } while (1);
    return 0;
}