#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Dog.h"
#include "list.h"
#include "queue.h"

// Function declarations
void parseInput(char *programArguments[], int *dogNumber, int *cageNumber, int *maxArrivalTime, int *maxServiceTime);
List createDogList(int numberOfDogs, int maxArrivalTime, int maxServiceTime); // unused
int* initialiseSimulator(Queue* dogQueue, int cageNumber);
void newDog(Dog* dogData, Queue dogQueue);
void serveDog(Dog* dogData, int* cages, int cageNumber);
void reportStatistics(List dogsDataList, int numberOfCages, int numberOfDogs, int clockTime);
void exitFromTheSimulation(List dogList, Queue dogQueue, int *cageData);

int main(int argc, char *argv[])
{
    printf("program baslatildi.\n");

    srand(time(NULL));
    int x = 0;
    int CLOCK = 0;

    // Check if user input is valid
    if (argc!=5){
        printf("Usage: %s <numberOfDogs> <numberOfCages> <maxArrivalTime> <maxServiceTime>\n", argv[0]);
        return 1;
    }

    // Parse arguments
    int dogNum, cageNum, maxArr, maxServ;
    parseInput(argv, &dogNum, &cageNum, &maxArr, &maxServ);

    List dogList = CreateList();
    for (int i = 0; i <= dogNum - 1; i++) {
        Dog* d = createRandomDog(maxArr, maxServ);
        InsertListOrderedByArrivalTime(dogList, d);
    }

    Queue dogQueue;
    int* cages = initialiseSimulator(&dogQueue, cageNum);
    int served = 0;

    // Start simulation
    while (served != dogNum) {
        struct ListNode* c = dogList->head->next;
        while (c) {
            Dog* dog = c->item;
            if (dog->arrivalTime == CLOCK && dog->serviceStartTime == -1) {
                newDog(dog, dogQueue);
            }
            c = c->next;
        }
// check if its empty or not
        while (!IsEmptyQueue(dogQueue)) {
            Dog* d = FrontOfQueue(dogQueue);
            int assigned = 0;
            for (int j = 0; j < cageNum; j++) {
                if (cages[j]==0) {
                    serveDog(d, cages, cageNum);
                    d->serviceStartTime = CLOCK;
                    cages[j] = d->serviceTime;
                    Dequeue(dogQueue);
                    assigned = 1;
                    break;
                }
            }
            if (assigned == 0) {
                break;
            }

        }

        // Cage countdown
        for (int i=0;i<cageNum;i++){
            if (cages[i]>0){
                cages[i]=cages[i]-1;
                if (cages[i]==0){
                    served += 1;
                }
            }
        }

        CLOCK++;
    }

    reportStatistics(dogList, cageNum, dogNum, CLOCK);
    exitFromTheSimulation(dogList, dogQueue, cages);
    return 0;
}

// Converts string inputs to integers
void parseInput(char *programArguments[], int *dogNumber, int *cageNumber, int *maxArrivalTime, int *maxServiceTime){
    *dogNumber = atoi(programArguments[1]);
    *cageNumber = atoi(programArguments[2]);
    *maxArrivalTime = atoi(programArguments[3]);
    *maxServiceTime = atoi(programArguments[4]);
}

// Allocates memory for cage timers
int* initialiseSimulator(Queue* dogQueue, int cageNumber) {
    *dogQueue = CreateQueue();
    int* arr = malloc(sizeof(int) * cageNumber);
    for (int i=0; i<cageNumber; ++i){
        arr[i] = 0;
    }
    return arr;
}

// Enqueue the dog
void newDog(Dog* dogData, Queue dogQueue){
    Enqueue(dogData, dogQueue);
}

// Assigns a dog to the first available cage
void serveDog(Dog* dogData, int* cages, int cageNumber) {
    for (int i = 0; i < cageNumber; i++) {
        if (cages[i] == 0) {
            dogData->cageNumber = i+1;
            cages[i] = dogData->serviceTime;
            return;
        }
    }
}

// outputs simulation results
void reportStatistics(List dogList, int numberOfCages, int numberOfDogs, int clockTime) {
    printf("\n***** REPORT *****\n");
    printf("Cages: %d\n", numberOfCages);
    printf("Dogs: %d\n", numberOfDogs);

    int d=0,u=0,w=0;
    int* usage = calloc(numberOfCages, sizeof(int));
    int total = 0, max = 0, male = 0, female = 0, neut = 0, notneut = 0;

    struct ListNode* p = dogList->head->next;
    while (p) {
        Dog* dg = p->item;
        if (dg->dogType == 'D') d++;
        else if (dg->dogType == 'U') u++;
        else w++;

        if (dg->cageNumber > 0)
            usage[dg->cageNumber - 1]++;

        int wait = dg->serviceStartTime - dg->arrivalTime;
        total += wait;
        if (wait > max) max = wait;

        if (dg->dogGender == 1) male++;
        else female++;

        if (dg->isNeutered) neut++;
        else notneut++;

        p = p->next;
    }

    printf("Types -> Dangerous:%d Unwell:%d Well:%d\n", d, u, w);
    for (int i=0;i<numberOfCages;++i) {
        printf("Cage %d -> %d dogs\n", i+1, usage[i]);
    }

    printf("Finished at time: %d\n", clockTime);
    printf("Average wait: %.1f\n", (float)total / numberOfDogs);
    printf("Longest wait: %d\n", max);
    printf("Gender majority: %s\n", male >= female ? "Male" : "Female");
    printf("Neutered majority: %s\n", neut > notneut ? "Yes" : "No");

    free(usage);
}

// Clean up everything
void exitFromTheSimulation(List dogList, Queue dogQueue, int *cageData){
    deleteList(dogList);
    deleteQueue(dogQueue);
    free(cageData);
}
