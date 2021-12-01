//  main.c
//  Project2
//  Copyright © 2021 Nima $wagaram. All rights reserved.

#include <stdio.h>
#include <stdlib.h>

typedef struct mem_block{
    struct mem_block* prev;
    struct mem_block* next;
    int end;                 //The N variable which stores the size
    //bool is_Free;
    int ID; //Can be a string as well
}mem_Block;


typedef struct ProcessInfo{
    char* task;
    char* processID;
    int values;
}ProcessInfo;

typedef struct Process{
   int orderValues;
   char *processNum;
}Process;


int Request(int taskArrayValue, int total){





    /*if(){
        printf("%s","ALLOCATED A x");       //Skeleton code
    }
    else{
        printf("%s","FAILED REQUEST A n");
    }
     */
}

/*void Release(){
    if(){
        printf("%s","FREE A n x");       //Skeleton code
    }
    else{
        printf("%s","FAILED RELEASE A n");
    }
}
 */

void ListAssigned(){

}
void ListAvailable(){

}

void Find(){

}

void remove_element(struct Process *array, int index, int numSteps)
{
    int i;
    for(i = index; i < numSteps - 1; i++) {
        array[i] = array[i + 1];
    }
}


//method for best Fit
void BestFit(int initialR, int size, struct ProcessInfo *taskArray, numSteps) {

}

//method for First fit
void FirstFit(int initialR, int size, struct ProcessInfo *taskArray, numSteps){
//Create another list
    Process *newArray = malloc(sizeof(struct Process));

    int a,b,result,resultN;

    for (a = 0; a < numSteps; a++) {
        result = strcmp(taskArray[0].task, "REQUEST");
        if (result == 0) {
            newArray[a].processNum = taskArray[a].processID;
            newArray[a].orderValues = taskArray[a].values;
        }
        for(b =0; b<numSteps;b++) {
            result = strcmp(taskArray[b].task, "RELEASE");
            if (resultN == 0) {
                remove_element(newArray[b].orderValues, a, numSteps);
                Process *tmp = realloc(newArray[b].orderValues, (size - 1) * sizeof(Process));
                size = size - 1;
                newArray[b].orderValues = tmp;
            }
        }
    }
}

//method for nextfit
void NextFit(int initialR, int size, struct ProcessInfo *taskArray, numSteps){
}
//method for worst fit
void WorstFit(int initialR, int size, struct ProcessInfo *taskArray, numSteps){
}

int main(int argc, char **argv) {
    FILE *fp;
    char initialR[254];
    int size;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", &initialR);
    fscanf(fp, "%d", &size);               //This will store the number

    ProcessInfo *taskArray = malloc(sizeof(struct ProcessInfo));

    char tasks[254];
    char process[254];
    int storage;
    int numSteps = 0;
    int a;
    int request = 0;
    int release;
    int list;

    for ( a = 0; a < 13; a++) {
        fscanf(fp, "%s %s %d", tasks, process, &storage);
        request = strcmp(tasks, "REQUEST");
        release = strcmp(tasks, "RELEASE");
        list = strcmp(tasks, "LIST");

        if(request ==0 || release == 0 || list == 0){
        taskArray[a].task = tasks;
        taskArray[a].processID = process;
        taskArray[a].values = storage;
        numSteps++;
        }
    }
    taskArray[a].values = storage;

    printf("%s\n", "Allocated OS 0");
    printf("%s", "(");
    printf("%d", size);
    printf("%s", ", ");
    printf("%d",taskArray[0].values);
    printf("%s\n", ")");

    int result;
    result = strcmp(initialR,"BESTFIT");

    if (result == 0) {
   // BestFit(initialR, size, taskArray,numSteps);
    }
     result = strcmp(initialR,"NEXTFIT");
    if(result == 0) {
    //    NextFit(initialR, size, taskArray,numSteps);
    }
    result = strcmp(initialR,"FIRSTFIT");
    if(result == 0) {
        FirstFit(initialR, size, taskArray,numSteps);
    }
    result = strcmp(initialR,"WORSTFIT");
    if(result == 0) {
     //   WorstFit(initialR, size, taskArray,numSteps);
    }
    return 0;
}
