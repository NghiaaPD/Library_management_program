#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai báo cấu trúc sách
struct book {
    char book_id[10];
    char book_name[50];
    char book_author[50];
    char book_publisher[50];
    int book_quantity;
};

// Khai báo cấu trúc ngày
struct date {
    int day;
    int month;
    int year;
};

struct Student {
    char student_id[15]; // Mã sinh viên
    char name[30]; // Họ tên
    char department[20]; // Khoa
    int books_issued; // Số lượng sách đang mượn
};

typedef struct {
    char book_id[10];
    char title[30];
    char author[20];
    char student_id[10];
    char issue_date[15];
    int issued;
} Book;

// Khai báo cấu trúc phiếu mượn
struct issue {
    char book_id[10];
    char student_id[10];
    struct date issue_date;
    struct date due_date;
};

// Khai báo hàm
void add_book();
void display_book();
void search_book();
void issue_book();
void return_book();
void display_issued_books();
void display_students();

int main() {
    int choice;
    do {
        printf("\n\n***MENU***\n");
        printf("1. Add book\n");
        printf("2. Display book\n");
        printf("3. find book\n");
        printf("4. borrow book\n");
        printf("5. Find sách\n");
        printf("6. Hiển thị sách đang được mượn\n");
        printf("7. Hiển thị thông tin sinh viên\n");
        printf("0. Thoát\n");
        printf("Vui lòng chọn một lựa chọn: ");
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
                issue_book();
                break;
            case 5:
                return_book();
                break;
            case 6:
                display_issued_books();
                break;
            case 7:
                display_students();
                break;
            case 0:
                printf("\nChương trình kết thúc.");
                exit(0);
            default:
                printf("\nLựa chọn không hợp lệ. Vui lòng thử lại.");
        }
    } while (choice != 0);
}

void add_book() {
    struct book b;
    printf("\nThêm sách mới\n");
    printf("Mã sách: ");
    scanf("%s", b.book_id);
    printf("Tên sách: ");
    scanf("%s", b.book_name);
    printf("Tác giả: ");
    scanf("%s", b.book_author);
    printf("Nhà xuất bản: ");
    scanf("%s", b.book_publisher);
    printf("Số lượng: ");
    scanf("%d", &b.book_quantity);

    FILE *fptr;
    fptr = fopen("books.dat", "ab");
    if (fptr == NULL) {
        printf("Không thể mở file.");
        return;
    }
    fwrite(&b, sizeof(b), 1, fptr);
    fclose(fptr);
    printf("Sách đã được thêm vào thành công.\n");
}

void display_book() {
    struct book b;
    FILE *fptr;
    fptr = fopen("books.dat", "rb");
    if (fptr == NULL) {
        printf("Không thể mở file.");
        return;
    }
    printf("\nDanh sách các sách có trong thư viện:\n");
    printf("%-15s%-50s%-25s%-25s%-10s\n", "Mã sách", "Tên sách", "Tác giả", "Nhà xuất bản", "Số lượng");
    while (fread(&b, sizeof(b), 1, fptr) == 1) {
        printf("%-15s%-50s%-25s%-25s%-10d\n", b.book_id, b.book_name, b.book_author, b.book_publisher, b.book_quantity);
    }
    fclose(fptr);
}

void search_book() {
    char id[10];
    printf("\nTìm kiếm sách\n");
    printf("Mã sách: ");
    scanf("%s", id);

    struct book b;
    FILE *fptr;
    fptr = fopen("books.dat", "rb");
    if (fptr == NULL) {
        printf("Không thể mở file.");
        return;
    }
    int found = 0;
    while (fread(&b, sizeof(b), 1, fptr) == 1) {
        if (strcmp(b.book_id, id) == 0) {
            printf("\nSách được tìm thấy.\n");
            printf("%-15s%-50s%-25s%-25s%-10s\n", "Mã sách", "Tên sách", "Tác giả", "Nhà xuất bản", "Số lượng");
            printf("%-15s%-50s%-25s%-25s%-10d\n", b.book_id, b.book_name, b.book_author, b.book_publisher, b.book_quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Sách không tồn tại trong thư viện.\n");
    }
    fclose(fptr);
}

void issue_book() {
    int student_id, book_id;
    // Nhập thông tin sinh viên và sách cần trả
    printf("\nNhập mã sinh viên: ");
    scanf("%d", &student_id);

    printf("\nNhập mã sách: ");
    scanf("%d", &book_id);

    struct issue i;
    FILE *fptr;
    fptr = fopen("issue.dat", "rb+");
    if (fptr == NULL) {
        printf("Không thể mở file.");
        return;
    }
    int found = 0;
    while (fread(&i, sizeof(i), 1, fptr) == 1) {
        if (i.book_id == book_id && i.student_id == student_id) {
            printf("\nTìm thấy phiếu mượn.\n");
            printf("%-15s%-15s%-15s%-15s\n", "Mã sách", "Mã sinh viên", "Ngày mượn", "Ngày trả");
            printf("%-15s%-15s%-15d/%-d/%-d%-15d/%-d/%-d\n", i.book_id, i.student_id, i.issue_date.day,
                   i.issue_date.month, i.issue_date.year, i.due_date.day, i.due_date.month, i.due_date.year);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Không tìm thấy phiếu mượn.\n");
        fclose(fptr);
        return;
    }

// Tính số ngày trễ hạn
    struct date return_date;
    printf("Nhập ngày trả (dd mm yyyy): ");
    scanf("%d %d %d", &return_date.day, &return_date.month, &return_date.year);
    int late_days = 0;
    if (return_date.year > i.due_date.year) {
        late_days = (return_date.year - i.due_date.year) * 365;
    }
    if (return_date.month > i.due_date.month) {
        late_days += (return_date.month - i.due_date.month) * 30;
    }
    late_days += return_date.day - i.due_date.day;

// Tính phí trễ hạn
    float late_fee = 0;
    if (late_days > 0) {
        late_fee = late_days * 0.5;
    }

// Cập nhật lại số lượng sách và xóa phiếu mượn khỏi file
    struct book b;
    FILE *fptr2;
    fptr2 = fopen("books.dat", "rb+");
    if (fptr2 == NULL) {
        printf("Không thể mở file.");
        return;
    }
    while (fread(&b, sizeof(b), 1, fptr2) == 1) {
        if (strcmp(b.book_id, i.book_id) == 0) {
            b.book_quantity++;
            fseek(fptr2, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fptr2);
            break;
        }
    }
    fclose(fptr2);
    fseek(fptr, -sizeof(i), SEEK_CUR);
    memset(&i, 0, sizeof(i));
    fwrite(&i, sizeof(i), 1, fptr);
    printf("Sách đã được trả lại thành công.\n");
    printf("Phí trễ hạn: %.2f\n", late_fee);
    fclose;
}

void return_book() {
    char st_id[6];
    int flag = 0;
    printf("\n\n\tNhập ID sinh viên: ");
    scanf("%s", st_id);
    struct issue i;
    FILE *fptr1;
    fptr1 = fopen("issue.dat", "rb+");
    if (fptr1 == NULL) {
        printf("Không thể mở file.");
        return;
    }

    FILE *fptr2;
    fptr2 = fopen("books.dat", "rb+");
    if (fptr2 == NULL) {
        printf("Không thể mở file.");
        return;
    }

    while (fread(&i, sizeof(i), 1, fptr1) == 1) {
        if (strcmp(i.student_id, st_id) == 0) {
            flag = 1;
            fseek(fptr1, -sizeof(i), SEEK_CUR);
            fwrite(&i, sizeof(i), 1, fptr2);
            break;
        }
    }

    if (flag == 0) {
        printf("Không có sách được cho mượn dưới tên sinh viên này!");
        return;
    }

    char book_id[10];
    printf("\n\n\tNhập mã sách: ");
    scanf("%s", book_id);

    while (fread(&i, sizeof(i), 1, fptr2) == 1) {
        if (strcmp(i.book_id, book_id) == 0) {
            fseek(fptr2, -sizeof(i), SEEK_CUR);
            i.issue_date.day = 0;
            i.issue_date.month = 0;
            i.issue_date.year = 0;
            i.due_date.day = 0;
            i.due_date.month = 0;
            i.due_date.year = 0;
            fwrite(&i, sizeof(i), 1, fptr2);
            printf("\n\tSách đã được trả!");
            break;
        }
    }

    fclose(fptr1);
    fclose(fptr2);
}

void display_issued_books() {
    int count = 0;
    #define MAX_BOOKS 100 // Số lượng sách tối đa
    Book books[MAX_BOOKS]; // Mảng lưu trữ thông tin sách
    printf("\n========== Danh sách sách đã mượn ==========\n");
    printf("\n%-10s%-30s%-20s%-20s%-15s\n", "Mã sách", "Tên sách", "Tác giả", "Người mượn", "Ngày mượn");
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (books[i].issued == 1) {
            printf("%-10s%-30s%-20s%-20s%-15s\n", books[i].book_id, books[i].title, books[i].author, books[i].student_id, books[i].issue_date);
            count++;
        }
    }
    if (count == 0) {
        printf("\nKhông có sách nào được mượn.\n");
    }
}

#define MAX_STUDENTS 100 // Số lượng sinh viên tối đa


struct Student students[MAX_STUDENTS];

void display_students() {
    int count = 0;
    printf("\n========== Danh sách sinh viên ==========\n");
    printf("\n%-10s%-30s%-20s%-15s\n", "Mã SV", "Họ và tên", "Khoa", "Số lượng sách đang mượn");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].student_id[0] != '\0') {
            printf("%-10s%-30s%-20s%-15d\n", students[i].student_id, students[i].name, students[i].department, students[i].books_issued);
            count++;
        }
    }
    if (count == 0) {
        printf("\nKhông có sinh viên nào trong thư viện.\n");
    }
}







