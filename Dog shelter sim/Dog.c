#include "Dog.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Creates a random dog with randomized personalities
Dog* createRandomDog(int maxArrivalTime, int maxServiceTime) {
    Dog* newDog = (Dog*)malloc(sizeof(Dog));
    //check if the memory is full or not
    if (newDog == NULL) {
        printf("Memory allocation failed for dog.\n");
        exit(1);
    }

    // roandomly make the dog dangerous unwell or well
    int type = rand() % 3;
    if (type == 0)
        newDog->dogType = 'D';
    else if (type == 1)
        newDog->dogType = 'U';
    else
        newDog->dogType = 'W';

    // randomly make arrival time for dog less than max arrival time
    newDog->arrivalTime = rand() % (maxArrivalTime+1);

    // randomly make service time
    newDog->serviceTime = (rand() % maxServiceTime)+1;

    // service start time begin in -1 because of when we do 0 it can not go inside the loop
    newDog->serviceStartTime = -1;
    newDog->cageNumber = 0;

    //gender generate for dog 0 female 1 male
    newDog->dogGender = rand()%2;

    // randomly generate neutrated for dog 0 no 1 yes
    newDog->isNeutered = rand() % 2;
// assign this for new dog
    return newDog;
}

// print dogs detail
void printDogInformation(Dog* dog) {

    printf("Dog Information:\n");
    printf("-----------------\n");
    printf("Type: %c\n", dog->dogType);
    printf("Arrival Time: %d\n", dog->arrivalTime);
    printf("Service Time: %d\n", dog->serviceTime);
    printf("Service Start Time: %d\n", dog->serviceStartTime);
    printf("Cage Number: %d\n", dog->cageNumber);

    if (dog->dogGender==1)
        printf("Gender: Male\n");
    else
        printf("Gender: Female\n");

    if (dog->isNeutered==1)
        printf("Neutered: Yes\n");
    else
        printf("Neutered: No\n");

}

