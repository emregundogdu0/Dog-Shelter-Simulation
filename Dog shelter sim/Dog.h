#ifndef DOGSHELTERSIM_DOG_H
#define DOGSHELTERSIM_DOG_H

#include <stdio.h>
#include <stdlib.h>

// A structure to reference the dogs in the simulation.
typedef struct {
    char dogType;
    int arrivalTime, serviceTime, serviceStartTime, cageNumber, dogGender, isNeutered;
}Dog;

//A function to return a dynamically allocated  random dogs address.
Dog* createRandomDog(int maxArrivalTime, int maxServiceTime);

//A function to print a single dogs information.
void printDogInformation(Dog* dog);

#endif //DOGSHELTERSIM_DOG_H
