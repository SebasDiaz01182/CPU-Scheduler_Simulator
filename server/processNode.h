#ifndef PROCESSLIST_H
#define PROCESSLIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct ProcessNode {
    int burst; //burst values of a process
    int arrive; //moment when the process is ready
    int priority; //level of priority of the process
    int pid;//pid of the process
    struct ProcessNode *next; //program counter
    int exit; //time when the process finished


}ProcessNode;

typedef struct ProcessList {

    ProcessNode *first; //program counter

}ProcessList;

void addProcess(ProcessList *list);
void addProcess(ProcessList *list, int burst, int arrive,int priority,int pid);
void printList(ProcessList *list);
ProcessNode * removeProcess(ProcessList *list,int pid);
ProcessNode * getFirstProcess(ProcessList *list);
ProcessNode * getSJFProcess(ProcessList *list);
ProcessNode * getHPFProcess(ProcessList *list);
ProcessNode * getNextProcess(ProcessList *list,ProcessNode *node);
#endif