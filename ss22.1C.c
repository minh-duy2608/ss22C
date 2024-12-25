#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
};

void loadStudents(struct Student students[], int *count);
void saveStudents(struct Student students[], int count);
void printStudents(struct Student students[], int count);
void addStudent(struct Student students[], int *count);
void editStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);
void searchStudent(struct Student students[], int count);
void sortStudents(struct Student students[], int count);

int main() {
    struct Student students[100];
    int count = 0;
    int choice;

    loadStudents(students, &count);

    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printStudents(students, count);
                break;
            case 2:
                addStudent(students, &count);
                saveStudents(students, count);
                break;
            case 3:
                editStudent(students, count);
                saveStudents(students, count);
                break;
            case 4:
                deleteStudent(students, &count);
                saveStudents(students, count);
                break;
            case 5:
                searchStudent(students, count);
                break;
            case 6:
                sortStudents(students, count);
                saveStudents(students, count);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 7);

    return 0;
}

void loadStudents(struct Student students[], int *count) {
    FILE *file = fopen("students.bin", "rb");
    if (file) {
        fread(count, sizeof(int), 1, file);
        fread(students, sizeof(struct Student), *count, file);
        fclose(file);
    } else {
        *count = 0;
    }
}

void saveStudents(struct Student students[], int count) {
    FILE *file = fopen("students.bin", "wb");
    if (file) {
        fwrite(&count, sizeof(int), 1, file);
        fwrite(students, sizeof(struct Student), count, file);
        fclose(file);
    }
}

void printStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("Danh sach sinh vien trong.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent(struct Student students[], int *count) {
    if (*count >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    printf("Nhap ID: ");
    scanf("%d", &students[*count].id);
    getchar();
    printf("Nhap ten: ");
    fgets(students[*count].name, sizeof(students[*count].name), stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';
    printf("Nhap tuoi: ");
    scanf("%d", &students[*count].age);
    (*count)++;
}

void editStudent(struct Student students[], int count) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void deleteStudent(struct Student students[], int *count) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Da xoa sinh vien co ID: %d\n", id);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void searchStudent(struct Student students[], int count) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void sortStudents(struct Student students[], int count) {
    struct Student temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].id > students[j].id) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep theo ID.\n");
}
