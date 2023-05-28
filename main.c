#include "plants.h"
#include <stdio.h>
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"


void printMenu() {
    printf(ANSI_COLOR_RESET "Меню:\n");
    printf("1. Добавить запись в базу\n");
    printf("2. Удалить запись из базы\n");
    printf("3. Поиск записей в базе\n");
    printf("4. Редактировать запись в базе\n");
    printf("5. Сортировка данных в базе\n");
    printf("6. Вывести базу данных на экран\n");
    printf("7. Очистить базу данных\n");
    printf("8. Выйти из программы\n");
    printf("Выберите действие: ");
}

int main() {
    long int choice;
    char input[20];

    while (1) {
        printMenu();
        fgets(input, 20, stdin);
        choice = make_int(is_positive_int(input), input); // Преобразуем строку в целое число

        switch (choice) {
            case 8:
                printf(ANSI_COLOR_RESET "Программа завершена\n");
                return 0;
            case 1:
                addPlant();
                break;
            case 2:
                deletePlant();
                break;
            case 3:
                searchPlant();
                break;
            case 4:
                editPlant();
                break;
            case 5:
                sortPlants();
                break;
            case 6:
                printDatabase();
                break;
            case 7:
                clearDatabase();
                break;
            default:
                printf(ANSI_COLOR_RED "ERROR: Некорректный выбор действия. Повторите ввод\n");
                break;
        }

        printf("\n");
    }
}
