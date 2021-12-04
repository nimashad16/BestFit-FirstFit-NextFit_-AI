#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TOTALSTEPS 50


#define REQUEST 0
#define RELEASE 1
#define LIST_AVAILABLE 2
#define LIST_ASSIGNED 3
#define FIND 4


#define FIRSTFIT 0
#define BESTFIT 1
#define WORSTFIT 2

typedef struct
{
    char taskID[10];
    int memoryNeeded;
    int process;

} Task;
typedef struct
{
    char taskID[10];
    int counter;
    int allocatedMemory;
} Process;

typedef struct
{
    Process tasks[TOTALSTEPS];
    int memBlock;
    int freeMemory;
    int availAddress;
    int fit;
    int next;
} Memory;


void Parsing(Task *taskArray,char *file)
{
    int counter = 0;
    char task[10];
    char nullWord[10] = "NULL";  
    int a;

    FILE *input = fopen(file, "r");

    while(fscanf(input, "%s", task) != EOF) {

        if(strcmp(task, "REQUEST") == 0) {
            taskArray[counter].process = REQUEST;
            fscanf(input, "%s ", task);

            for(int a = 0; a < 10; a++)
                taskArray[counter].taskID[a] = task[a];
            fscanf(input, "%s ", task);
            taskArray[counter].memoryNeeded = (int)strtol(task, (char **)NULL, 10);
            counter++;
        }

        else if(strcmp(task, "RELEASE") == 0) {
            taskArray[counter].process = RELEASE;
            fscanf(input, "%s ", task);
            for(a = 0; a < 10; a++) {
                taskArray[counter].memoryNeeded = 0;
                taskArray[counter].taskID[a] = task[a];
                counter++;
            }
        }

        else if(strcmp(task, "FIND") == 0) {
            taskArray[counter].process = FIND;
            fscanf(input, "%s ", task);
            for(a = 0; a < 10; a++) {
                taskArray[counter].memoryNeeded = 0;
                taskArray[counter].taskID[a] = task[a];
                counter++;
            }
        }

        else if(strcmp(task, "LIST") == 0) {
            fscanf(input, "%s ", task);

            if(strcmp(task, "ASSIGNED") == 0) {
                taskArray[counter].process = LIST_ASSIGNED;
                for(int i = 0; i < 10; i++)
                    taskArray[counter].taskID[i] = nullWord[i];
                taskArray[counter].memoryNeeded = 0;
            }
            else {
                taskArray[counter].process = LIST_AVAILABLE;
                for(int i = 0; i < 10; i++)
                    taskArray[counter].taskID[i] = nullWord[i];
                taskArray[counter].memoryNeeded = 0;
            }
            counter++;
        }
    }
    fclose(input);
}

void fillBlocks(Memory *memory);

void removeIndex(Memory *memory, int empty)
{
    Process newTasks[TOTALSTEPS];
    int count = 0;
    int a;
    for(a = 0; a < memory->next; a++)
    {
        if(a != empty)
        {
            newTasks[count] = memory->tasks[a];
            count++;
        }
    }

    memcpy(memory->tasks, &newTasks, sizeof(memory->tasks));
    memory->next = count;
    fillBlocks(memory);
}

int stringConverter(char *taskID)
{
    if(strcmp(taskID, "FIRSTFIT") == 0){
        return 0;
    }
    else if(strcmp(taskID, "BESTFIT") == 0){
        return 1;
    }
    else if(strcmp(taskID, "WORSTFIT") == 0){
        return 2;
    }
    else{
        return -1;
    }
}
void fillBlocks(Memory *memory) {
    int x;
    for(int x = 0; x < memory->next; x++){
        if(strcmp(memory->tasks[x+1].taskID, "BLOCK") == 0 && strcmp(memory->tasks[x].taskID, "BLOCK") == 0){
            memory->tasks[x].allocatedMemory = memory->tasks[x].allocatedMemory + memory->tasks[x+1].allocatedMemory;
            removeIndex(memory, x+1);
        }
    }
}
Process newBlock(int spot,int memory) {
    Process block;
    memcpy(block.taskID, "BLOCK", sizeof(block.taskID));
    block.allocatedMemory = memory;
    block.counter = spot;

    return block;
}

void swap(Process *first, Process *second) {
    Process temp = *first;
    *first = *second;
    *second = temp;
}

void sort(Memory *memory) {
    int a,x;
    for(a = 0; a < memory->next-1; a++){
        for( x = 0; x < memory->next - a -1; x++){
            if(memory->tasks[x].counter > memory->tasks[x+1].counter){
                swap(&memory->tasks[x], &memory->tasks[x+1]);
            }
        }
    }
}

void blockToProcess(char newProcess[], int memoryNeeded, Memory *memory, int i)
{
    int diffMemory;
     diffMemory = memory->tasks[i].allocatedMemory - memoryNeeded;

    memcpy(memory->tasks[i].taskID, newProcess, sizeof(memory->tasks[i].taskID));
    memory->tasks[i].allocatedMemory = memoryNeeded;

    if(diffMemory == 0)
    {
        return;
    }
   
    memory->tasks[memory->next] = newBlock(memory->tasks[i].counter + memoryNeeded,diffMemory);
    memory->next++;
    memory->freeMemory = memory->freeMemory - memoryNeeded;
}

void firstfit(int memoryNeeded, Memory *memory, char taskID[])
{
    int x;
    for(x = 0; x < memory->next; x++)
    {
        if(strcmp(memory->tasks[x].taskID, "BLOCK") == 0)
        {
            if(memory->tasks[x].allocatedMemory >= memoryNeeded)
            {
                blockToProcess(taskID, memoryNeeded, memory, x);
                printf("ALLOCATED %s %d\n", taskID, memory->tasks[x].counter);
                return;
            }
        }
    }

    printf("FAIL REQUEST %s %d\n", taskID, memoryNeeded);
}


void bestfit(int memoryNeeded,char taskID[], Memory *memory)
{
    int smallestBlock;
    int firstCounter;
    int x;

    smallestBlock = memory->memBlock+1; 
    firstCounter = -1;

    for(x = 0; x < memory->next; x++)
    {
        if(strcmp(memory->tasks[x].taskID, "BLOCK") == 0)
        {
            if((memory->tasks[x].allocatedMemory >= memoryNeeded) && (memory->tasks[x].allocatedMemory < smallestBlock))
            {
                smallestBlock = memory->tasks[x].allocatedMemory;
                firstCounter = x;
            }
        }
    }

    if(firstCounter > -1)
    {
        blockToProcess(taskID, memoryNeeded, memory, firstCounter);
        printf("ALLOCATED %s %d\n", taskID, memory->tasks[firstCounter].counter);
        return;
    }

    printf("FAIL REQUEST %s %d\n", taskID, memoryNeeded);
    return;
}

void worstfit( int memoryNeeded, char taskID[],Memory *memory)
{
    int LastIndex = -1;
    int biggestBlock = -1;

    int x;
    for(x = 0; x < memory->next; x++)
    {
        if(strcmp(memory->tasks[x].taskID, "BLOCK") == 0)
        {
            if((memory->tasks[x].allocatedMemory >= memoryNeeded) && (memory->tasks[x].allocatedMemory > biggestBlock))
            {
                biggestBlock = memory->tasks[x].allocatedMemory;
                LastIndex = x;
            }
        }
    }

    if(LastIndex > -1)
    {
        blockToProcess(taskID, memoryNeeded, memory, LastIndex);
        printf("ALLOCATED %s %d\n", taskID, memory->tasks[LastIndex].counter);
        return;
    }

    printf("FAIL REQUEST %s %d\n", taskID, memoryNeeded);
    return;
}


void request(int memoryNeeded,char taskID[],  Memory *memory)
{
    if(memory->freeMemory < memoryNeeded)
    {
        printf("FAIL REQUEST %s %d\n", taskID, memoryNeeded);
        return;
    }

    switch(memory->fit)
    {
        case FIRSTFIT:
            firstfit(memoryNeeded, memory,taskID);
            break;
        case BESTFIT:
            bestfit(memoryNeeded,taskID,memory);
            break;
        case WORSTFIT:
            worstfit(memoryNeeded, taskID, memory);
            break;
    }
}


void release( Memory *memory,char taskID[])
{
    for(int i = 0; i < memory->next; i++)
    {
        if(strcmp(memory->tasks[i].taskID, taskID) == 0)
        {
            memcpy(memory->tasks[i].taskID, "BLOCK", sizeof(memory->tasks[i].taskID));
            memory->freeMemory = memory->freeMemory + memory->tasks[i].allocatedMemory;
            printf("FREE %s %d %d\n", taskID, memory->tasks[i].allocatedMemory, memory->tasks[i].counter);
            return;
        }
    }
    printf("FAIL RELEASE %s\n", taskID);
}


void listAvailable(Memory *memory)
{
    int counter = 0;
    for(int x = 0; x < memory->next; x++){
        if(strcmp(memory->tasks[x].taskID, "BLOCK") == 0){
            printf("(%d, %d) ", memory->tasks[x].allocatedMemory, memory->tasks[x].counter);
            counter++;
        }
    }

    if(counter > 0){
        printf("\n");
        return;
    }
    else{
        printf("FULL\n");

    }
}

void listAssigned(Memory *memory)
{
    int counter = 0;
    int x;
    for(x = 0; x < memory->next; x++)
    {
        if(!(strcmp(memory->tasks[x].taskID, "BLOCK") == 0))
        {
            printf("(%s, %d, %d) ", memory->tasks[x].taskID,
                   memory->tasks[x].allocatedMemory, memory->tasks[x].counter);
            counter = counter +1;
        }
    }

    if(counter > 0)
    {
        printf("\n");
    }
    else
    {
        printf("NONE\n");
    }
}


void find( Memory *memory,char taskID[])
{
    int x;
    for(x = 0; x < memory->next; x++)
    {
        if(strcmp(memory->tasks[x].taskID, taskID) == 0)
        {
            printf("(%s, %d, %d)\n", taskID, memory->tasks[x].allocatedMemory, memory->tasks[x].counter);
            return;
        }
    }

    printf("FAULT\n");
}


void run( Memory *memory,Task process)
{
    switch(process.process)
    {
        case REQUEST:
            request(process.memoryNeeded,process.taskID, memory);
            break;
        case RELEASE:
            release(memory,process.taskID);
            break;
        case LIST_AVAILABLE:
            listAvailable(memory);
            break;
        case LIST_ASSIGNED:
            listAssigned(memory);
            break;
        case FIND:
            find(memory, process.taskID);
            break;
        default:
            printf("NOT FOUND\n");
            break;
    }
    sort(memory);
    fillBlocks(memory);
}

void initialMemory(Memory *memory)
{
    memory->tasks[0] = newBlock(0,memory->memBlock);
    memory->next = 1;
    memory->freeMemory = memory->memBlock;
    memory->availAddress = 0;
}


int getNumProcesses(char *fileName)
{
    int processCount = 0;

    FILE *file = fopen(fileName, "r");
    char word[10];

    while(fscanf(file, "%s ", word) != EOF)
    {
        if(strcmp(word, "REQUEST") == 0)
        {
            processCount++;
            /* skips next 2 words */
            fscanf(file, "%s ", word);
            fscanf(file, "%s ", word);
        }
        else if(strcmp(word, "RELEASE") == 0 || strcmp(word, "LIST") == 0 || strcmp(word, "FIND") == 0)
        {
            processCount++;

            /* skips next word */
            fscanf(file, "%s ", word);
        }
    }

    fclose(file);
    return processCount;
}

int main(int argc, char **argv)
{
    Memory memory;

    if (argc != 4)
    {
        printf("Not enough arguments.\n");
    }
    memory.fit = stringConverter(argv[1]);
    memory.memBlock = (int)strtol(argv[2], (char **)NULL, 10);
    initialMemory(&memory);

    char *fileName = argv[3];
    int numTasks;
    numTasks = getNumProcesses(fileName);

    Task processArray[numTasks];
    Parsing(processArray,fileName);
    int x;
    for(x = 0; x < numTasks; x++)
    {
        run(&memory,processArray[x]);
    }
    return 0;
}

