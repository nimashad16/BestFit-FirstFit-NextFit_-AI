
//  main.c
//  Project2
//  Copyright © 2021 Nima $wagaram. All rights reserved.

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mem_block{
    struct mem_block* prev;
    struct mem_block* next;
    int end;        //The N variable which stores the size
    //bool is_Free;
    int ID; //Can be a string as well
}mem_Block;

typedef struct ProcessInfo{
    char *task;
    char *processID;
    int values;
}ProcessInfo;

//method for best Fit
void BestFit(){

}

//method for First fit
void FirstFit(){

}

//method for nextfit
void NextFit(){

}
//method for worst fit
void WorstFit(){


}

//Create the rules for when each process is called
//Read in the variables
//If "Request" is read in, do it with the processID read in
//If "Release" is read in
//If "list available" is read in, output a list of space separated pairs
//If "LIST ASSIGNED" Returns a list of space separated triples including of the form

//If it is "FIND A"


int main(int argc, char **argv) {
    int initial;
    FILE *fp;
    char request[254];
    char initialR[254];
    int size;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", &initialR);
    fscanf(fp, "%d", &size);               //This will store the number

    int ran = 12;
    ProcessInfo *taskArray = malloc(sizeof(ran));

    char tasks[254];
    char process[254];
    int storage = 0;
    int numSteps = 0;

    for (int a = 0; a < 12; a++) {
        fscanf(fp, "%s %s %d", tasks, process, &storage);
        taskArray[a].task = tasks;
        taskArray[a].processID = process;
        taskArray[a].values = storage;
        numSteps++;
    }

    if (initialR == "BESTFIT") {
    BestFit(taskArray,numSteps, size);
    }
    if(initialR == "NEXTFIT") {
        NextFit(taskArray,numSteps, size);
    }
    if(initialR == "FIRSTFIT") {
        FirstFit(taskArray, numSteps, size);
    }
    if(initialR == "WORSTFIT") {
        WorstFit(taskArray, numSteps, size);
    }

    printf("%s\n", "Allocated OS 0");
    printf("%s", "(");
    printf("%d", size);
    printf("%s", ", ");
    printf("%d",taskArray[0].values);
    printf("%s\n", ")");

    return 0;
}
