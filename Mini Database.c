#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int id;
    char name[50];
    int age;
};

void createTable() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error creating table.\n");
        return;
    }
    printf("Table created successfully (students.dat)\n");
    fclose(file);
}

void insertRecord() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Table does not exist. Create table first.\n");
        return;
    }

    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    fwrite(&s, sizeof(s), 1, file);
    fclose(file);

    printf("Record inserted successfully.\n");
}

void selectAll() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Table does not exist.\n");
        return;
    }

    struct Student s;

    printf("\nID\tName\tAge\n");
    printf("----------------------\n");

    while (fread(&s, sizeof(s), 1, file)) {
        printf("%d\t%s\t%d\n", s.id, s.name, s.age);
    }

    fclose(file);
}

void selectWhere() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Table does not exist.\n");
        return;
    }

    int searchId;
    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    struct Student s;
    int found = 0;

    while (fread(&s, sizeof(s), 1, file)) {
        if (s.id == searchId) {
            printf("Found: %d %s %d\n", s.id, s.name, s.age);
            found = 1;
        }
    }

    if (!found) {
        printf("No record found.\n");
    }

    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Mini Database Engine ---\n");
        printf("1. Create Table\n");
        printf("2. Insert Record\n");
        printf("3. Select All\n");
        printf("4. Select WHERE (ID)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createTable(); break;
            case 2: insertRecord(); break;
            case 3: selectAll(); break;
            case 4: selectWhere(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}