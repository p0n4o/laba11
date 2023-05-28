#ifndef PLANTS_H
#define PLANTS_H

typedef enum { false, true } bool; // объявляем новый тип "bool" для более удобной реализации функции

struct Plant {
    char name[50];
    char regions[100];
    long int age;
    long int isFlowering;
};

void addPlant();
void deletePlant();
void searchPlant();
void editPlant();
void sortPlants();
void printDatabase();
void clearDatabase();
bool is_positive_int();
long int make_int();

#endif  // PLANTS_H
