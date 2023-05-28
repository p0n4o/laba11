#include "plants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define DATABASE_FILE "plants.bin"


bool is_positive_int(char *stroke) {  // проверка на то, что строка - целое положительное число
    for (int i = 0; i != strlen(stroke) - 1; i++) {
        if (strlen(stroke) > 2 && stroke[0] == '0') {
            return false;
        }
        if ((int)stroke[i] >= 48 && (int)stroke[i] <= 57) {
        }
        else return false;
    }
    return true;
}

long int make_int(bool test, char *stroke) {  // преобразование строки в целое число, если это возможно
    long n;
    if (test == true) {
        n = strtol(stroke, NULL, 10);
        return n;
    }
    else {
        return 0;
    }
}

void addPlant() {
    FILE* file = fopen(DATABASE_FILE, "ab");
    char input[20];
    struct Plant plant;

    printf(ANSI_COLOR_RESET "Введите название растения: ");
    fgets(plant.name, sizeof(plant.name), stdin);
    plant.name[strcspn(plant.name, "\n")] = '\0';

    printf(ANSI_COLOR_RESET "Введите основные регионы распространения: ");
    fgets(plant.regions, sizeof(plant.regions), stdin);
    plant.regions[strcspn(plant.regions, "\n")] = '\0';

    do {
        printf(ANSI_COLOR_RESET "Введите возраст растения: ");
        fgets(input, 20, stdin);
        plant.age = make_int(is_positive_int(input), input);
        if (is_positive_int(input) != true) {
            printf(ANSI_COLOR_RED "ERROR: Некорректное возраст растения. Повторите ввод:\n");
        }
    } while (is_positive_int(input) != true);

    do {
        printf(ANSI_COLOR_RESET "Введите информацию о цветении (1 - цветет, 0 - не цветет):");
        fgets(input, 20, stdin);
        plant.isFlowering = make_int(is_positive_int(input), input);
        if (plant.isFlowering != 0 && plant.isFlowering != 1 || is_positive_int(input) != true) {
            printf(ANSI_COLOR_RED "ERROR: Некорректное значение характера цветения. Повторите ввод:\n");
        }
    } while (plant.isFlowering != 0 && plant.isFlowering != 1 || is_positive_int(input) != true);


    fwrite(&plant, sizeof(struct Plant), 1, file);
    fclose(file);

    printf(ANSI_COLOR_GREEN "Растение добавлено в базу данных\n");
}

void deletePlant() {
    FILE* file = fopen(DATABASE_FILE, "rb");
    FILE* tempFile = fopen("temp.bin", "wb");
    char name[50];
    struct Plant plant;

    printf(ANSI_COLOR_RESET "Введите название растения, которое нужно удалить: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Удаление символа перехода на новую строку из строки "name"

    int found = 0;

    while (fread(&plant, sizeof(struct Plant), 1, file)) {
        if (strcmp(plant.name, name) != 0) {
            fwrite(&plant, sizeof(struct Plant), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(DATABASE_FILE);
    rename("temp.bin", DATABASE_FILE);

    if (found) {
        printf(ANSI_COLOR_GREEN "Растение удалено из базы данных\n");
    } else {
        printf(ANSI_COLOR_RED "ERROR: Растение с указанным названием не найдено в базе данных\n");
    }
}

void searchPlant() {
    FILE* file = fopen(DATABASE_FILE, "rb");
    char name[50];
    struct Plant plant;

    printf(ANSI_COLOR_RESET "Введите название растения для поиска: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove the newline character from the "name" string

    int found = 0;

    printf(ANSI_COLOR_GREEN "\nРезультаты поиска:\n");
    printf(ANSI_COLOR_RESET " ____________________________________________________________________________________\n");
    printf("| %-37s | %-40s | %-17s | %-17s |\n", "Название", "Основные регионы", "Возраст", "Цветение");
    printf("|_______________________________|___________________________|____________|___________|\n");

    while (fread(&plant, sizeof(struct Plant), 1, file)) {
        if (strcmp(plant.name, name) == 0) {
            printf("| %-29s | %-25s | %-10li | %-15s |\n",
                   plant.name, plant.regions, plant.age, plant.isFlowering ? "цветет" : "не цветет");
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf(ANSI_COLOR_RED "| ERROR: Растение с указанным названием не найдено в базе данных                     |\n");
    }

    printf(ANSI_COLOR_RESET "|_______________________________|___________________________|____________|___________|\n");
}


void editPlant() {
    FILE* file = fopen(DATABASE_FILE, "rb+");
    char name[50];
    char input[20];
    struct Plant plant;

    printf(ANSI_COLOR_RESET "\nВведите название растения, которое нужно отредактировать: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Удаление символа перехода на новую строку из строки "name"

    int found = 0;

    while (fread(&plant, sizeof(struct Plant), 1, file)) {
        if (strcmp(plant.name, name) == 0) {
            printf(ANSI_COLOR_RESET "Введите новое название растения: ");
            fgets(plant.name, sizeof(plant.name), stdin);
            plant.name[strcspn(plant.name, "\n")] = '\0';

            printf(ANSI_COLOR_RESET "Введите новые основные регионы распространения: ");
            fgets(plant.regions, sizeof(plant.regions), stdin);
            plant.regions[strcspn(plant.regions, "\n")] = '\0';

            do {
                printf(ANSI_COLOR_RESET "Введите возраст растения: ");
                fgets(input, 20, stdin);
                plant.age = make_int(is_positive_int(input), input);
                if (is_positive_int(input) != true) {
                    printf(ANSI_COLOR_RED "ERROR: Некорректное возраст растения. Повторите ввод:\n");
                }
            } while (is_positive_int(input) != true);

            do {
                printf(ANSI_COLOR_RESET "Введите информацию о цветении (1 - цветет, 0 - не цветет):");
                fgets(input, 20, stdin);
                plant.isFlowering = make_int(is_positive_int(input), input);
                if (plant.isFlowering != 0 && plant.isFlowering != 1 || is_positive_int(input) != true) {
                    printf(ANSI_COLOR_RED "ERROR: Некорректное значение характера цветения. Повторите ввод:\n");
                }
            } while (plant.isFlowering != 0 && plant.isFlowering != 1 || is_positive_int(input) != true);

            fseek(file, -sizeof(struct Plant), SEEK_CUR);
            fwrite(&plant, sizeof(struct Plant), 1, file);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf(ANSI_COLOR_GREEN "Растение успешно отредактировано\n");
    } else {
        printf(ANSI_COLOR_RED "ERROR: Растение с указанным названием не найдено в базе данных\n");
    }
}

int compareByName(const void* a, const void* b) {
    struct Plant* plantA = (struct Plant*)a;
    struct Plant* plantB = (struct Plant*)b;
    return strcmp(plantA->name, plantB->name);
}

int compareByRegions(const void* a, const void* b) {
    struct Plant* plantA = (struct Plant*)a;
    struct Plant* plantB = (struct Plant*)b;
    return strcmp(plantA->regions, plantB->regions);
}

int compareByAge(const void* a, const void* b) {
    struct Plant* plantA = (struct Plant*)a;
    struct Plant* plantB = (struct Plant*)b;
    return plantA->age - plantB->age;
}

int compareByFlowering(const void* a, const void* b) {
    struct Plant* plantA = (struct Plant*)a;
    struct Plant* plantB = (struct Plant*)b;
    return plantA->isFlowering - plantB->isFlowering;
}

void clearDatabase() {
    FILE* file = fopen(DATABASE_FILE, "wb");
    fclose(file);
    printf(ANSI_COLOR_GREEN "База данных очищена\n");
}


void sortPlants() {
    FILE* file = fopen(DATABASE_FILE, "rb+");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    int plantCount = fileSize / sizeof(struct Plant);
    struct Plant* plants = malloc(plantCount * sizeof(struct Plant));

    if (plantCount == 0) {
        printf(ANSI_COLOR_RED "ERROR: База данных пуста\n");
        fclose(file);
        return;
    }

    fseek(file, 0, SEEK_SET);
    fread(plants, sizeof(struct Plant), plantCount, file);

    printf(ANSI_COLOR_RESET "\nВыберите поле для сортировки:\n");
    printf(ANSI_COLOR_RESET "1. Название\n");
    printf(ANSI_COLOR_RESET "2. Основные регионы распространения\n");
    printf(ANSI_COLOR_RESET "3. Возраст\n");
    printf(ANSI_COLOR_RESET "4. Цветение\n");
    printf(ANSI_COLOR_RESET "Введите номер поля: ");

    long int field;
    char input[20];

    fgets(input, 20, stdin);
    field = make_int(is_positive_int(input), input); // Преобразуем строку в целое число

    switch (field) {
        case 1:
            qsort(plants, plantCount, sizeof(struct Plant), compareByName);
            break;
        case 2:
            qsort(plants, plantCount, sizeof(struct Plant), compareByRegions);
            break;
        case 3:
            qsort(plants, plantCount, sizeof(struct Plant), compareByAge);
            break;
        case 4:
            qsort(plants, plantCount, sizeof(struct Plant), compareByFlowering);
            break;
        default:
            printf(ANSI_COLOR_RED "ERROR: Некорректный номер поля\n");
            fclose(file);
            free(plants);
            return;
    }

    fseek(file, 0, SEEK_SET);
    fwrite(plants, sizeof(struct Plant), plantCount, file);

    fclose(file);
    free(plants);

    printf(ANSI_COLOR_GREEN "База данных отсортирована по выбранному полю\n");
}

void printDatabase() {
    FILE* file = fopen(DATABASE_FILE, "rb");
    struct Plant plant;
    int count = 0;

    printf(ANSI_COLOR_RESET "Содержимое базы данных:\n\n");
    printf(ANSI_COLOR_RESET " __________________________________________________________________________________________\n");
    printf("| %-3s | %-37s | %-40s | %-17s | %-17s |\n", "No", "Название", "Основные регионы", "Возраст", "Цветение");
    printf("|_____|_______________________________|___________________________|____________|___________|\n");

    while (fread(&plant, sizeof(struct Plant), 1, file)) {
        printf("| %-3d | %-29s | %-25s | %-10li | %-15s |\n",
               ++count, plant.name, plant.regions, plant.age, plant.isFlowering ? "цветет" : "не цветет");
    }

    fclose(file);

    if (count == 0) {
        printf(ANSI_COLOR_RED "| ERROR: База данных пуста                                                                 |\n");
    }

    printf(ANSI_COLOR_RESET "|_____|_______________________________|___________________________|____________|___________|\n");
}

